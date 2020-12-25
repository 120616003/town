#include "ServerEvent.h"
#include "user.pb.h"

namespace town {

VUMPSerMessPtr ServerEvent::m_vumpSerMessPtr = VUMPSerMessPtr(4);

ServerEvent::~ServerEvent()
{
	if (ev_b) {
		event_base_free(ev_b);
	}
	if (ev_c) {
		event_config_free(ev_c);
	}
}

int ServerEvent::ServerInit(int iPort)
{
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(struct sockaddr_in));
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

	ev_l = evconnlistener_new_bind(ev_b, ServerListenerCb, ev_b, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, 10, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
	if (!ev_l) {
		LOG_WARN("evconnlistener_new_bind failed, ev_l is nullptr");
		return FAILED;
	}

	return SUCCESS;
}

void ServerEvent::ServerStart()
{
	std::thread(event_base_dispatch, ev_b).detach();
}

void ServerEvent::ServerListenerCb(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sock, int socklen, void* arg)
{
	LOG_INFO("accept a client:{}", fd);
  
	event_base *base = (event_base*)arg;
	bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
  
	bufferevent_setcb(bev, ServerReadCb, nullptr, ServerEventCb, nullptr);
	bufferevent_enable(bev, EV_READ | EV_PERSIST);

	SerMessPtr ser_mess = std::make_shared<ServerMessage>();
	if (ser_mess) {
		ser_mess->SetEvutilSocket(fd);
		ser_mess->SetBufferevent(bev);
		ser_mess->SetUUID(Booster::GetUUID());
	}
	m_vumpSerMessPtr[0][ser_mess->GetUUID()] = ser_mess;
}

void ServerEvent::ServerReadCb(bufferevent *bev, void *arg)
{
	char buf[1024 * 10 + 1] = {};
	uint32_t len = 0;
	uint32_t ret = 0;
	uint32_t save_len = 0;
	std::string msg;
	do {
		if (!len) {
			bufferevent_read(bev, &len, sizeof(uint32_t));
			if (len == 0) {
				return;
			}
			if (len > 1024 * 10) {
				LOG_INFO("data size out of range, len:{}", len);
				return;
			}
		}
		// LOG_INFO("len:{}, save_len:{}", len, save_len);
		ret = bufferevent_read(bev, buf + save_len, len - save_len);

		if (ret <= 0) {
			LOG_INFO("data error, ret:{}", ret);
			return;
		}

		save_len += ret;
		if (save_len == len) {
			// msg.reserve(save_len);
			// msg.insert(msg.end(), buf, buf + save_len);
			// login lg;
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

void ServerEvent::ClearMap(size_t index)
{
	m_vumpSerMessPtr[index].clear();
}

} /* town */