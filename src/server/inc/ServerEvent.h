#ifndef SERVER_EVENT_H
#define SERVER_EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>

namespace town {

class ServerEvent
{
public:
	ServerEvent();
	~ServerEvent();

	int ServerInit(int iPort);
	void ServerStart();

private:
	static void ServerListenerCb(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sock, int socklen, void* arg);
	static void ServerReadCb(bufferevent *bev, void *arg);
	static void ServerEventCb(bufferevent *bev, short events, void *arg);

private:
	struct event_config* ev_c;
	struct event_base* ev_b;
	evconnlistener* ev_l;
};

}

#endif /* SERVER_EVENT_H */