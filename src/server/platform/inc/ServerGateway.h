#ifndef SERVER_GATEWAY_H
#define SERVER_GATEWAY_H

#include "ServerGatewayInfc.h"
#include "ServerCommon.h"
#include "ServerEvent.h"

namespace town {

class MsgDeal;
class ServerGateway;
using ServerGatewayPtr = std::shared_ptr<ServerGateway>;

class ServerGateway : public ServerGatewayInfc
{
public:
	ServerGateway();
	~ServerGateway();
	void Initialization(MysqlOptHandleInfcPtr pMysqlOptHandleInfc);
	void MsgGate(std::unique_ptr<MSG_DATA>& pMsgData);
	void RegisterServerHandle(ServerEventPtr pServerEvent);

private:
	void MsgFactory(MysqlOptHandleInfcPtr pMysqlOptHandleInfc);
	void RunFactoryMsg();

private:
	std::map<MSG_TYPE, std::shared_ptr<MsgDeal>> m_eMsgDeal;
	ServerEventPtr m_pServerEvent;
};

} /* town */

#endif /* SERVER_GATEWAY_H */