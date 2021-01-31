#include "ServerEventInfc.h"
#include "ServerEvent.h"

namespace town {

ServerEventInfc::ServerEventInfc()
{
}

ServerEventInfc::~ServerEventInfc()
{
}

ServerEventInfcPtr ServerEventInfc::GetInstance()
{
	static ServerEventPtr impl = std::make_shared<ServerEvent>();
	return impl;
}

int32_t ServerEventInfc::Initialization(int32_t iPort, ServerGatewayInfcPtr pServerGatewayInfc)
{
	ServerEvent* impl = reinterpret_cast<ServerEvent*>(this);
	return impl->Initialization(iPort, pServerGatewayInfc);
}

void ServerEventInfc::StartServer()
{
	ServerEvent* impl = reinterpret_cast<ServerEvent*>(this);
	impl->StartServer();
}

} /* town */