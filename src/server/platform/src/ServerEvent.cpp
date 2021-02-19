#include "ServerEvent.h"
#include "ClientHandle.h"
#include <errno.h>
#include <cstring>
#include <event2/thread.h>

namespace town {

#define INDEX_BEFORE(x) ((x % 4) == 0) ? 3 : ((x % 4) - 1)
#define INDEX_CURREN(x) (x % 4)

VUMCliHanPtr ServerEvent::m_vumCliHanPtr = VUMCliHanPtr(4);
uint64_t ServerEvent::m_clear_index = 0;
uint64_t ServerEvent::m_record_index = 2;
ServerGatewayInfcPtr ServerEvent::m_pServerGatewayInfc = nullptr;

ServerEvent::ServerEvent()
{
}

ServerEvent::~ServerEvent()
{
	m_vumCliHanPtr.clear();
	if (ev_b) {
		event_base_free(ev_b);
	}
	if (ev_c) {
		event_config_free(ev_c);
	}
}

int32_t ServerEvent::Initialization(int32_t iPort, ServerGatewayInfcPtr pServerGatewayInfc)
{
	struct sockaddr_in sin {};
	sin.sin_family = AF_INET;
	sin.sin_port = htons(iPort);

	ev_c = event_config_new();
	if (!ev_c) {
		LOG_WARN("event_config_new failed, ev_c is nullptr");
		return FAILED;
	}
	evthread_use_pthreads();
	event_config_avoid_method(ev_c, "select");
	event_config_avoid_method(ev_c, "poll");
	event_config_require_features(ev_c, EV_FEATURE_ET);
	event_config_set_flag(ev_c, EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST);

	ev_b = event_base_new_with_config(ev_c);
	if (!ev_b) {
		LOG_WARN("event_base_new_with_config failed, ev_b is nullptr");
		return FAILED;
	}

	ev_l = evconnlistener_new_bind(ev_b, AcceptConnectCb, ev_b, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE, 10, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
	if (!ev_l) {
		LOG_WARN("evconnlistener_new_bind failed, ev_l is nullptr, error msg:{}", strerror(errno));
		return FAILED;
	}

	m_pServerGatewayInfc = pServerGatewayInfc;
	m_pServerGatewayInfc->RegisterServerHandle(ServerEventPtr(this));

	LOG_DEBUG("initialization success");

	return SUCCESS;
}

void ServerEvent::StartServer()
{
	auto bufferevent = std::thread(event_base_dispatch, ev_b); // 消息监听线程
	pthread_setname_np(bufferevent.native_handle(), "bufferevent");
	bufferevent.detach();

	auto serverevent = std::thread(&ServerEvent::ClearClient, this); // 超时断开线程
	pthread_setname_np(serverevent.native_handle(), "clearclient");
	serverevent.detach();
}

CliHanPtr ServerEvent::GetClientHandle(bufferevent* bev)
{
	if (m_vumCliHanPtr[INDEX_CURREN(m_record_index)][GetStringFd(bev)] != nullptr) {
		return m_vumCliHanPtr[INDEX_CURREN(m_record_index)][GetStringFd(bev)];
	}
	return m_vumCliHanPtr[INDEX_BEFORE(m_record_index)][GetStringFd(bev)];
}

CliHanPtr ServerEvent::GetClientHandle(const std::string& uuid)
{
	if (m_vumCliHanPtr[INDEX_CURREN(m_record_index)][uuid] != nullptr) {
		return m_vumCliHanPtr[INDEX_CURREN(m_record_index)][uuid];
	}
	return m_vumCliHanPtr[INDEX_BEFORE(m_record_index)][uuid];
}

void ServerEvent::DeleteClient(bufferevent* bev)
{
	m_vumCliHanPtr[INDEX_CURREN(m_record_index)][GetStringFd(bev)] = nullptr;
	m_vumCliHanPtr[INDEX_BEFORE(m_record_index)][GetStringFd(bev)] = nullptr;
}

void ServerEvent::AcceptConnectCb(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sock, int32_t socklen, void* arg)
{
	event_base *base = reinterpret_cast<event_base*>(arg);
	bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

	bufferevent_setcb(bev, ReadDataCb, nullptr, ClientEventCb, nullptr);
	bufferevent_enable(bev, EV_READ | EV_PERSIST);

	CliHanPtr cli_han = std::make_shared<ClientHandle>();
	if (!cli_han) {
		bufferevent_free(bev);
		LOG_ERROR("CliHanPtr create failed");
		return;
	}
	cli_han->SetEvutilSocket(fd);
	cli_han->SetBufferevent(bev);
	cli_han->SetStatus(true);
	m_vumCliHanPtr[INDEX_CURREN(m_record_index)][GetStringFd(fd)] = cli_han;
	LOG_DEBUG("accept a client:{}, index:{}", fd, INDEX_CURREN(m_record_index));
}

void ServerEvent::ReadDataCb(bufferevent* bev, void* arg)
{
	uint16_t read_len = 0;
	MSG_INFO msg_info{};
	do {
		if (!read_len) {
			bufferevent_read(bev, &msg_info, sizeof(MSG_INFO));
			if (msg_info.msg_len == 0) {
				return;
			}

			if (msg_info.msg_len > 1024 * 10) {
				LOG_INFO("data size out of range, data len:{}", msg_info.msg_len);
				return;
			}
		}

		std::unique_ptr<uint8_t[]> data_buf(new uint8_t[msg_info.msg_len]());
		uint16_t ret_len = bufferevent_read(bev, data_buf.get() + read_len, msg_info.msg_len - read_len);

		if (0 == ret_len) {
			LOG_DEBUG("data read err num:{}, err msg:{}", errno, strerror(errno));
			return;
		}

		read_len += ret_len;
		if (read_len == msg_info.msg_len) {
			if (Booster::Crc(data_buf.get(), msg_info.msg_len) != msg_info.msg_crc) {
				GetClientHandle(bev)->SetStatus(false);
				DeleteClient(bev);
				LOG_ERROR("msg crc error, msg_type:{}", static_cast<uint32_t>(msg_info.msg_type));
				return;
			}

			RecordClient(bev);

			std::unique_ptr<MSG_DATA> pMsgData = std::make_unique<MSG_DATA>();
			pMsgData->bev = bev;
			pMsgData->info = msg_info;
			pMsgData->data = std::move(data_buf);

			m_pServerGatewayInfc->MsgGate(pMsgData);
			read_len = msg_info.msg_len = 0;
		}
	} while (true);
}

void ServerEvent::WriteData(bufferevent* bev, const std::string& msg, MSG_TYPE eType)
{
    MSG_INFO msg_info {};
    msg_info.msg_len = msg.size();
    msg_info.msg_type = eType;
    msg_info.msg_crc = Booster::Crc(reinterpret_cast<uint8_t*>(const_cast<char*>(msg.data())), msg_info.msg_len);
    char buf[1024] = {};
    memcpy(buf, &msg_info, sizeof(MSG_INFO));
    memcpy(buf + sizeof(MSG_INFO), msg.data(), msg_info.msg_len);
    int data_size = sizeof(MSG_INFO) + msg_info.msg_len;
    bufferevent_write(bev, buf, data_size);
    bufferevent_flush(bev, 0, BEV_FINISHED);
}

void ServerEvent::ClientEventCb(bufferevent* bev, short events, void* arg)
{
	if (events & BEV_EVENT_EOF) {
		LOG_DEBUG("client actively disconnect");
	}
	else if (events & BEV_EVENT_ERROR) {
		LOG_WARN("unknown error, the server will be passively disconnected");
	}

	auto client = GetClientHandle(bev);
	if (client) {
		client->SetStatus(false);
		DeleteClient(bev);
	}
}

void ServerEvent::RecordClient(bufferevent* bev)
{
	if (m_vumCliHanPtr[INDEX_CURREN(m_record_index)][GetStringFd(bev)] == nullptr) {
		m_vumCliHanPtr[INDEX_CURREN(m_record_index)][GetStringFd(bev)] = m_vumCliHanPtr[INDEX_BEFORE(m_record_index)][GetStringFd(bev)];
	}
}

void ServerEvent::ClearClient()
{
	while(true) {
		Booster::Timer(10000, 0, 0);
		ClearMap(m_clear_index++ % 4);
		++m_record_index;
	}
}

void ServerEvent::ClearMap(size_t index)
{
	m_vumCliHanPtr[index].clear();
}

std::string ServerEvent::GetStringFd(bufferevent* bev)
{
	return std::move(std::to_string(bufferevent_getfd(bev)));
}

std::string ServerEvent::GetStringFd(const evutil_socket_t fd)
{
	return std::move(std::to_string(fd));
}

} /* town */