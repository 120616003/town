#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

#include <event2/bufferevent.h>
#include <string>
#include "ServerCommon.h"

namespace town {

class ClientHandle
{
public:
	ClientHandle();
	~ClientHandle();

public:
	void SetEvutilSocket(evutil_socket_t fd);
	evutil_socket_t GetEvutilSocket();

	void SetBufferevent(bufferevent* ev);
	bufferevent* GetBufferevent();

	void SetUUID(const std::string& strUuid);
	std::string GetUUID();

	void SetStatus(bool status);
	bool GetStatus();

private:
	evutil_socket_t m_fd = -1;
	bufferevent* m_ev = nullptr;
	std::string m_uuid;
	bool m_status = false;
};

}

#endif /* CLIENT_HANDLE_H */