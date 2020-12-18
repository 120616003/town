#include "ServerEvent.h"
#include "ServerCommon.h"

namespace town {

ServerEvent::ServerEvent()
{
	ev_c = nullptr;
	ev_b = nullptr;
	ev_l = nullptr;
}

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
		LOG_WARN("ev_c is nullptr");
		return FAILED;
	}

	event_config_avoid_method(ev_c, "select");
	event_config_avoid_method(ev_c, "poll");
	event_config_require_features(ev_c, EV_FEATURE_ET);
	event_config_set_flag(ev_c, EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST);

	ev_b = event_base_new_with_config(ev_c);
	if (!ev_b) {
		LOG_WARN("ev_b is nullptr");
		return FAILED;
	}

	ev_l = evconnlistener_new_bind(ev_b, ServerEvent::ServerListenerCb, ev_b, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, 10, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
	if (!ev_l) {
		LOG_WARN("ev_l is nullptr");
		return FAILED;
	}

	return SUCCESS;
}

void ServerEvent::ServerStart()
{
	event_base_dispatch(ev_b);
}

void ServerEvent::ServerListenerCb(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sock, int socklen, void* arg)
{
	LOG_INFO("accept a client:{}", fd);
  
	event_base *base = (event_base*)arg;  
	bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
  
	bufferevent_setcb(bev, ServerReadCb, nullptr, ServerEventCb, nullptr);
	bufferevent_enable(bev, EV_READ | EV_PERSIST);  
}

void ServerEvent::ServerReadCb(bufferevent *bev, void *arg)
{
	char msg[4096] = {};
	size_t len = bufferevent_read(bev, msg, sizeof(msg) - 1);
	LOG_INFO("server read the data:{}", msg);
	char reply[] = "I has read your data";  
	bufferevent_write(bev, reply, strlen(reply));  
}

void ServerEvent::ServerEventCb(bufferevent *bev, short events, void *arg)
{
	if (events & BEV_EVENT_EOF) {
		LOG_WARN("connection closed");
	}
	else if (events & BEV_EVENT_ERROR) {
		LOG_WARN("some other error");
	}

	bufferevent_free(bev);  
}

} /* town */