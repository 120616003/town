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

void ServerGateway::MsgGate(std::tuple<bufferevent*, MSG_INFO::MSG_TYPE, std::string>& bev_msg)
{
	switch (std::get<1>(bev_msg)) {
		case MSG_INFO::MESS_REGISTER :
		case MSG_INFO::MESS_LOGIN : {
			MsgForward(bev_msg);
			break;
		}
		default:
			break;
	}
}

void ServerGateway::MsgFactory()
{
	m_eMsgDeal[MSG_INFO::MESS_REGISTER] = std::make_shared<RegisterMsgDeal>();
	m_eMsgDeal[MSG_INFO::MESS_LOGIN] = std::make_shared<LoginMsgDeal>();
}

void ServerGateway::RunFactoryMsg()
{
	for (auto& eMsgDeal : m_eMsgDeal) {
		std::thread(&MsgDeal::MsgForward, eMsgDeal.second.get()).detach();
	}
}

void ServerGateway::MsgForward(std::tuple<bufferevent*, MSG_INFO::MSG_TYPE, std::string>& bev_msg)
{
	if (m_eMsgDeal.find(std::get<1>(bev_msg)) != m_eMsgDeal.end()) {
		std::pair<bufferevent*, std::string> bmsg{std::get<0>(bev_msg), std::move(std::get<2>(bev_msg))};
		m_eMsgDeal[std::get<1>(bev_msg)]->PushMsg(bmsg);
	}
}

} /* town */