#ifndef SERVER_MASSAGE_H
#define SERVER_MASSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <event2/event.h>
#include <event2/bufferevent.h>

namespace town {

class ServerMassage
{
public:
	ServerMassage();
	~ServerMassage();

	int CreateServer();
	// void error_cb(struct bufferevent *bev, short event, void *arg);
	// void write_cb(struct bufferevent *bev, void *arg);
	// static void read_cb(struct bufferevent *bev, void *arg);
	// void do_accept(evutil_socket_t listener, short event, void *arg);
};

}

#endif /* SERVER_MASSAGE_H */