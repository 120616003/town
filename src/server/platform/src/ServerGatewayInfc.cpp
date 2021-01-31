#include "ServerGatewayInfc.h"
#include "ServerGateway.h"

namespace town {

ServerGatewayInfcPtr ServerGatewayInfc::GetInstance()
{
	static ServerGatewayPtr impl = std::make_shared<ServerGateway>();
	return impl;
}

ServerGatewayInfc::ServerGatewayInfc()
{
}

ServerGatewayInfc::~ServerGatewayInfc()
{
}

void ServerGatewayInfc::Initialization(MysqlOptHandleInfcPtr pMysqlOptHandleInfc)
{
	ServerGateway* impl = reinterpret_cast<ServerGateway*>(this);
	impl->Initialization(pMysqlOptHandleInfc);
}

void ServerGatewayInfc::MsgGate(std::unique_ptr<MSG_DATA>& pMsgData)
{
	ServerGateway* impl = reinterpret_cast<ServerGateway*>(this);
	impl->MsgGate(pMsgData);
}

void ServerGatewayInfc::RegisterServerHandle(ServerEventPtr pServerEvent)
{
	ServerGateway* impl = reinterpret_cast<ServerGateway*>(this);
	impl->RegisterServerHandle(pServerEvent);
}

} /* town */