#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>
#include <event2/listener.h>
#include <errno.h>
#include <cstring>
#include <thread>

#include "ServerEvent.h"
#include "ClientHandle.h"
#include "ServerGateway.h"

namespace town {

#define INDEX_BEFORE(x) ((x % 4) == 0) ? 3 : ((x % 4) - 1)
#define INDEX_CURREN(x) (x % 4)

VUMCliHanPtr ServerEvent::m_vumCliHanPtr = VUMCliHanPtr(4);
uint64_t ServerEvent::m_clear_index = 0;
uint64_t ServerEvent::m_record_index = 2;
std::unique_ptr<ServerGateway> ServerEvent::m_pServerGateway = nullptr;

SerEvnPtr ServerEvent::GetInstance()
{
	static PRIVATE_KEY key;
	static SerEvnPtr se = std::make_shared<ServerEvent>(key);
	return se;
}

ServerEvent::ServerEvent(PRIVATE_KEY key)
{
	m_pServerGateway = std::make_unique<ServerGateway>();
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

int32_t ServerEvent::Initialization(int32_t iPort)
{
	struct sockaddr_in sin {};
	sin.sin_family = AF_INET;
	sin.sin_port = htons(iPort);

	ev_c = event_config_new();
	if (!ev_c) {
		LOG_WARN("event_config_new failed, ev_c is nullptr");
		return FAILED;
	}

	event_config_avoid_method(ev_c, "select");
	event_config_avoid_method(ev_c, "poll");
	event_config_require_features(ev_c, EV_FEATURE_ET);
	event_config_set_flag(ev_c, EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST);

	ev_b = event_base_new_with_config(ev_c);
	if (!ev_b) {
		LOG_WARN("event_base_new_with_config failed, ev_b is nullptr");
		return FAILED;
	}

	ev_l = evconnlistener_new_bind(ev_b, AcceptConnectCb, ev_b, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, 10, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
	if (!ev_l) {
		LOG_WARN("evconnlistener_new_bind failed, ev_l is nullptr");
		return FAILED;
	}

	LOG_DEBUG("initialization success");

	return SUCCESS;
}

void ServerEvent::StartServer()
{
	std::thread(&ServerGateway::MsgForwardCenter, m_pServerGateway.get()).detach(); // 数据处理线程
	std::thread(event_base_dispatch, ev_b).detach(); // 消息监听线程
	std::thread(&ServerEvent::DeleteClient, this).detach(); // 超时断开线程
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
	LOG_INFO("accept a client:{}, index:{}", fd, INDEX_CURREN(m_record_index));
}

void ServerEvent::ReadDataCb(bufferevent* bev, void* arg)
{
	if (!GetClientHandle(bev)->GetStatus()) return;
	RecordClient(bev);

	uint8_t data_buf[1024 * 10] = {};
	uint16_t ret_len = 0;
	uint16_t read_len = 0;
	Msg_Info msg_info{};
	
	std::string msg;
	do {
		if (!msg_info.msg_len) {
			bufferevent_read(bev, &msg_info, sizeof(msg_info));
			if (msg_info.msg_len == 0) {
				return;
			}

			if (msg_info.msg_len > 1024 * 10) {
				LOG_INFO("data size out of range, data len:{}", msg_info.msg_len);
				return;
			}
			msg.reserve(msg_info.msg_len);
		}

		ret_len = bufferevent_read(bev, data_buf + read_len, msg_info.msg_len - read_len);

		if (0 == ret_len) {
			if (EAGAIN == errno) {
				continue;
			}
			else {
				LOG_WARN("data read error:{}", strerror(errno));
			}
		}

		read_len += ret_len;
		if (read_len == msg_info.msg_len) {

			if (Booster::Crc(data_buf, msg_info.msg_len) != msg_info.msg_crc) {
				GetClientHandle(bev)->SetStatus(false);
			}

			msg.insert(msg.end(), data_buf, data_buf + read_len);
			read_len = msg_info.msg_len = 0;
			std::pair<bufferevent*, std::string> bev_msg{bev, std::move(msg)};
			m_pServerGateway->PushMsg(bev_msg);
		}
	} while (true);
}

void ServerEvent::ClientEventCb(bufferevent* bev, short events, void* arg)
{
	if (events & BEV_EVENT_EOF) {
		LOG_INFO("client actively disconnect");
	}
	else if (events & BEV_EVENT_ERROR) {
		LOG_WARN("unknown error, the server will be passively disconnected");
	}

	CliHanPtr chptr = GetClientHandle(bev);
	if (nullptr != chptr) {
		chptr->SetStatus(false);
	}
}

void ServerEvent::RecordClient(bufferevent* bev)
{
	if (m_vumCliHanPtr[INDEX_CURREN(m_record_index)][GetStringFd(bev)] == nullptr) {
		m_vumCliHanPtr[INDEX_CURREN(m_record_index)][GetStringFd(bev)] = m_vumCliHanPtr[INDEX_BEFORE(m_record_index)][GetStringFd(bev)];
	}
}

void ServerEvent::DeleteClient()
{
	while(true) {
		Booster::Timer(10, 0, 0);
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