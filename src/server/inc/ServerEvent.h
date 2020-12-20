#ifndef SERVER_EVENT_H
#define SERVER_EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <memory>
#include <unordered_map>
#include <vector>

#include "ServerCommon.h"
#include "ServerMessage.h"

namespace town {

typedef std::shared_ptr<ServerMessage> SerMessPtr;
typedef std::unordered_map<std::string, SerMessPtr> UMSerMessPtr;
typedef std::vector<UMSerMessPtr> VUMPSerMessPtr;

class ServerEvent
{
public:
	~ServerEvent();

	int ServerInit(int iPort);
	void ServerStart();
	void ClearMap(size_t index);

private:
	static void ServerListenerCb(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sock, int socklen, void* arg);
	static void ServerReadCb(bufferevent *bev, void *arg);
	static void ServerEventCb(bufferevent *bev, short events, void *arg);

private:
	struct event_config* ev_c = nullptr;
	struct event_base* ev_b = nullptr;
	evconnlistener* ev_l = nullptr;
	static VUMPSerMessPtr m_vumpSerMessPtr;
};

}

#endif /* SERVER_EVENT_H */