#ifndef SERVER_MASSEGE_H
#define SERVER_MASSEGE_H

#include <event2/bufferevent.h>
#include <string>
#include "ServerCommon.h"

namespace town {

class ServerMessage
{
public:
	ServerMessage();
	~ServerMessage();

public:
	void SetEvutilSocket(evutil_socket_t fd);
	evutil_socket_t GetEvutilSocket();

	void SetBufferevent(bufferevent* ev);
	bufferevent* GetBufferevent();

	void SetUUID(const std::string& strUuid);
	std::string GetUUID();

private:
	evutil_socket_t m_fd = -1;
	bufferevent* m_ev = nullptr;
	std::string m_uuid;
};

}

#endif /* SERVER_MASSEGE_H */