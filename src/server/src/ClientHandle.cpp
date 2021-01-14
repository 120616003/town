#include "ClientHandle.h"
#include <unistd.h>

namespace town {

ClientHandle::ClientHandle()
{
}

ClientHandle::~ClientHandle()
{
	if (m_ev) {
		close(m_fd);
		bufferevent_free(m_ev);
	}
}

void ClientHandle::SetEvutilSocket(evutil_socket_t fd)
{
	m_fd = fd;
}

evutil_socket_t ClientHandle::GetEvutilSocket()
{
	return m_fd;
}

void ClientHandle::SetBufferevent(bufferevent* ev)
{
	m_ev = ev;
}

bufferevent* ClientHandle::GetBufferevent()
{
	return m_ev;
}

void ClientHandle::SetUUID(const std::string& uuid)
{
	m_uuid = uuid;
}

std::string ClientHandle::GetUUID()
{
	return m_uuid;
}

} /* town */