
#include <errno.h>
#include <assert.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>
#include <event2/listener.h>


#include "ServerEvent.h"
#include "ServerCommon.h"
#include "ClientHandle.h"
#include "user.pb.h"

namespace town {

VUMCliHanPtr ServerEvent::m_vumCliHanPtr = VUMCliHanPtr(4);
uint64_t ServerEvent::clear_index = 0;
uint64_t ServerEvent::record_index = 2;

ServerEvent::~ServerEvent()
{
	if (ev_b) {
		event_base_free(ev_b);
	}
	if (ev_c) {
		event_config_free(ev_c);
	}
}

int32_t ServerEvent::ServerInit(int32_t iPort)
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

	ev_l = evconnlistener_new_bind(ev_b, Accept, ev_b, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, 10, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
	if (!ev_l) {
		LOG_WARN("evconnlistener_new_bind failed, ev_l is nullptr");
		return FAILED;
	}

	std::thread(&ServerEvent::Disconnect, this).detach(); // 启动超时断开线程

	return SUCCESS;
}

void ServerEvent::ServerStart()
{
	std::thread(event_base_dispatch, ev_b).detach();
}

void ServerEvent::Accept(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sock, int32_t socklen, void* arg)
{
	LOG_INFO("accept a client:{}", fd);

	event_base *base = (event_base*)arg;
	bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

	bufferevent_setcb(bev, ReadData, nullptr, ServerEventCb, nullptr);
	bufferevent_enable(bev, EV_READ | EV_PERSIST);

	CliHanPtr cli_han = std::make_shared<ClientHandle>();
	if (!cli_han) {
		bufferevent_free(bev);
		return;
	}
	cli_han->SetEvutilSocket(fd);
	cli_han->SetBufferevent(bev);
	m_vumCliHanPtr[record_index  % 4][fd] = cli_han;
}

void ServerEvent::ReadData(bufferevent* bev, void *arg)
{
	m_vumCliHanPtr[record_index % 4][bev->ev_read.ev_fd] = m_vumCliHanPtr[(record_index % 4 - 1) < 0 ? 3 : (record_index % 4 - 1)][bev->ev_read.ev_fd];

	char buf[1024 * 10 + 1] = {};
	uint32_t data_len = 0;
	uint32_t ret = 0;
	uint32_t save_len = 0;
	
	std::string msg;
	do {
		if (!data_len) {
			bufferevent_read(bev, &data_len, sizeof(uint32_t));
			if (data_len == 0) {
				return;
			}
			if (data_len > 1024 * 10) {
				LOG_INFO("data size out of range, data_len:{}", data_len);
				return;
			}
		}
		// LOG_INFO("len:{}, save_len:{}", len, save_len);
		ret = bufferevent_read(bev, buf + save_len, data_len - save_len);

		if (ret <= 0) {
			LOG_INFO("data error, ret:{}", ret);
			return;
		}

		save_len += ret;
		if (save_len == data_len) {
			msg.reserve(save_len);
			msg.insert(msg.end(), buf, buf + save_len);
			message ma;
			ma.ParseFromString(msg);
			LOG_INFO("type:{}", ma.mess_type());
			acc_register ar;
			ar.ParseFromString(ma.mess_data());
			LOG_INFO("type:{}", ar.type());
			LOG_INFO("email:{}", ar.email());
			LOG_INFO("passwd:{}", ar.passwd());
			// // if (!lg.ParseFromString(msg))
			// if (!lg.ParseFromArray(buf, save_len))
			// {
			// 	LOG_INFO("ParseFromString failed");
			// 	return;
			// }
			// LOG_INFO("type:{}", lg.type());
			// LOG_INFO("name:{}", lg.name());
			// LOG_INFO("email:{}", lg.email());
			// LOG_INFO("phone:{}", lg.phone());
			// LOG_INFO("passwd:{}", lg.passwd());
			// len = 0;
			// save_len = 0;
			// break;
		}
	} while (true);
}

void ServerEvent::ServerEventCb(bufferevent *bev, short events, void *arg)
{
	if (events & BEV_EVENT_EOF) {
		LOG_INFO("client actively disconnect");
	}
	else if (events & BEV_EVENT_ERROR) {
		LOG_WARN("unknown error, the server will be passively disconnected");
	}
	bufferevent_free(bev);
}

void ServerEvent::Disconnect()
{
	while(true) {
		Booster::Timer(10, 0, 0);
		ClearMap(clear_index++ % 4);
		++record_index;
	}
}

void ServerEvent::ClearMap(size_t index)
{
	m_vumCliHanPtr[index].clear();
}

} /* town */