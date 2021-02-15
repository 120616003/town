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

void ServerGateway::Initialization(MysqlOptHandleInfcPtr pMysqlOptHandleInfc)
{
	MsgFactory(pMysqlOptHandleInfc);
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

void ServerGateway::RegisterServerHandle(ServerEventPtr pServerEvent)
{
	m_pServerEvent = pServerEvent;
	for (auto& eMsgDeal : m_eMsgDeal) {
		eMsgDeal.second->RegisterServerHandle(pServerEvent);
	}
}

void ServerGateway::MsgFactory(MysqlOptHandleInfcPtr pMysqlOptHandleInfc)
{
	m_eMsgDeal[MESS_REGISTER] = std::make_shared<RegisterMsgDeal>();
	m_eMsgDeal[MESS_REGISTER]->RegisterDBLogicHandle(pMysqlOptHandleInfc);
	m_eMsgDeal[MESS_LOGIN] = std::make_shared<LoginMsgDeal>();
	m_eMsgDeal[MESS_LOGIN]->RegisterDBLogicHandle(pMysqlOptHandleInfc);
}

void ServerGateway::RunFactoryMsg()
{
	for (auto& eMsgDeal : m_eMsgDeal) {
		auto msgdeal = std::thread(&MsgDeal::MsgForward, eMsgDeal.second.get());
		pthread_setname_np(msgdeal.native_handle(), convert_msg_type.find(eMsgDeal.first)->second.c_str());
		msgdeal.detach();
	}
}

} /* town */