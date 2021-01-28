#ifndef SERVER_GATEWAY_H
#define SERVER_GATEWAY_H

#include "ServerCommon.h"

namespace town {

class MsgDeal;
class ServerGateway
{
public:
	ServerGateway();
	~ServerGateway();
	void Initialization();
	void MsgGate(std::unique_ptr<MSG_DATA>& pMsgData);

private:
	void MsgFactory();
	void RunFactoryMsg();

private:
	std::map<MSG_TYPE, std::shared_ptr<MsgDeal>> m_eMsgDeal;
};

} /* town */

#endif /* SERVER_GATEWAY_H */