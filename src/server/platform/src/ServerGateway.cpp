#include "ServerGateway.h"

#include "MsgDeal.h"
#include "RegisterMsgDeal.h"
#include "LoginMsgDeal.h"

namespace town {

ServerGateway::ServerGateway()
{
}

ServerGateway::~ServerGateway()
{
}

void ServerGateway::Initialization()
{
	MsgFactory();
	RunFactoryMsg();
}

void ServerGateway::MsgGate(std::unique_ptr<MSG_DATA>& pMsgData)
{
	switch (pMsgData->info.msg_type) {
		case MESS_REGISTER :
		case MESS_LOGIN : {
			m_eMsgDeal[pMsgData->info.msg_type]->PushMsg(pMsgData);
			break;
		}
		default:
			break;
	}
}

void ServerGateway::MsgFactory()
{
	m_eMsgDeal[MESS_REGISTER] = std::make_shared<RegisterMsgDeal>();
	m_eMsgDeal[MESS_LOGIN] = std::make_shared<LoginMsgDeal>();
}

void ServerGateway::RunFactoryMsg()
{
	for (auto& eMsgDeal : m_eMsgDeal) {
		auto msgdeal = std::thread(&MsgDeal::MsgForward, eMsgDeal.second.get());
		pthread_setname_np(msgdeal.native_handle(), convert_msg_type[static_cast<uint32_t>(eMsgDeal.first)].c_str());
		msgdeal.detach();
	}
}

} /* town */