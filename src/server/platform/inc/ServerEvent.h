#ifndef SERVER_EVENT_H
#define SERVER_EVENT_H

#include "ServerGatewayInfc.h"
#include "ServerEventInfc.h"
#include "ClientHandle.h"

namespace town {

class ServerEvent;
using ServerEventPtr = std::shared_ptr<ServerEvent>;

class ServerEvent : public ServerEventInfc, std::enable_shared_from_this<ServerEvent> 
{
public:
	ServerEvent();
	~ServerEvent();
	int32_t Initialization(int32_t iPort, ServerGatewayInfcPtr pServerGatewayInfc);
	void StartServer();

	static CliHanPtr GetClientHandle(bufferevent* bev);
	static CliHanPtr GetClientHandle(const std::string& uuid);
	static void DeleteClient(bufferevent* bev);

private:
	static void AcceptConnectCb(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sock, int32_t socklen, void* arg);
	static void ReadDataCb(bufferevent* bev, void* arg);
	static void ClientEventCb(bufferevent* bev, short events, void* arg);

private:
	static void RecordClient(bufferevent* bev);
	void ClearClient();
	void ClearMap(size_t index);
	static std::string GetStringFd(bufferevent* bev);
	static std::string GetStringFd(const evutil_socket_t fd);

private: // 消息网关对象
	static ServerGatewayInfcPtr m_pServerGatewayInfc;

private: // libevent事件库
	event_config* ev_c = nullptr;
	event_base* ev_b = nullptr;
	evconnlistener* ev_l = nullptr;

private: // 维护客户端句柄
	static uint64_t m_record_index;
	static uint64_t m_clear_index;
	static VUMCliHanPtr m_vumCliHanPtr;
};

} /* town */

#endif /* SERVER_EVENT_H */