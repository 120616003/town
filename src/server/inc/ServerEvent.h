#ifndef SERVER_EVENT_H
#define SERVER_EVENT_H

#include <memory>
#include <unordered_map>
#include <vector>
#include <event2/util.h> // evutil_socket_t

struct event_config;
struct event_base;
struct evconnlistener;
struct bufferevent;

namespace town {

class ClientHandle;
typedef std::shared_ptr<town::ClientHandle> CliHanPtr;
typedef std::unordered_map<std::string, CliHanPtr> UMCliHanPtr;
typedef std::vector<UMCliHanPtr> VUMCliHanPtr;

class ServerEvent
{
public:
	~ServerEvent();

	int32_t ServerInit(int32_t iPort);
	void ServerStart();

private:
	void Disconnect();
	void ClearMap(size_t index);

private:
	static void Accept(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sock, int32_t socklen, void* arg);
	static void ReadData(bufferevent *bev, void *arg);
	static void ServerEventCb(bufferevent *bev, short events, void *arg);

private:
	struct event_config* ev_c = nullptr;
	struct event_base* ev_b = nullptr;
	evconnlistener* ev_l = nullptr;
	uint8_t clear_index = 0;
	static VUMCliHanPtr m_vumCliHanPtr;
};

}

#endif /* SERVER_EVENT_H */