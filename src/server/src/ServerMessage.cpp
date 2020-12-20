#include "ServerMessage.h"
#include <unistd.h>

namespace town {

ServerMessage::ServerMessage()
{
}

ServerMessage::~ServerMessage()
{
	bufferevent_free(m_ev);
}

void ServerMessage::SetEvutilSocket(evutil_socket_t fd)
{
	m_fd = fd;
}

evutil_socket_t ServerMessage::GetEvutilSocket()
{
	return m_fd;
}

void ServerMessage::SetBufferevent(bufferevent* ev)
{
	m_ev = ev;
}

bufferevent* ServerMessage::GetBufferevent()
{
	return m_ev;
}

void ServerMessage::SetUUID(const std::string& uuid)
{
	m_uuid = uuid;
}

std::string ServerMessage::GetUUID()
{
	return m_uuid;
}

} /* town */