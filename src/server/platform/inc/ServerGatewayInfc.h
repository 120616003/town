#ifndef SERVER_GATEWAY_INFC_H
#define SERVER_GATEWAY_INFC_H

#include "MysqlOptHandleInfc.h"

namespace town {

struct MSG_DATA;
class ServerGatewayInfc;
using ServerGatewayInfcPtr = std::shared_ptr<ServerGatewayInfc>;

class ServerEvent;
using ServerEventPtr = std::shared_ptr<ServerEvent>;

class ServerGatewayInfc
{
public:
	static ServerGatewayInfcPtr GetInstance();
	void Initialization(MysqlOptHandleInfcPtr pMysqlOptHandleInfc);
	void MsgGate(std::unique_ptr<MSG_DATA>& pMsgData);
	void RegisterServerHandle(ServerEventPtr pServerEvent);

protected:
	ServerGatewayInfc();
	~ServerGatewayInfc();
};

} /* town */

#endif /* SERVER_GATEWAY_INFC_H */