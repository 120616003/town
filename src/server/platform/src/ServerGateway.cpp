#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>

#include "ServerCommon.h"
#include "ServerGateway.h"
#include "ServerEvent.h"
#include "ClientHandle.h"

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

void ServerGateway::MsgForwardCenter()
{
	MsgFactory();
	RunFactoryMsg();
	message m;
	while (true) {
		std::pair<bufferevent*, std::string> bev_msg;
		{
			std::unique_lock<std::mutex> lk(m_lock);
			while (m_read_index == m_write_index) {
				m_cv.wait_for(lk, 1s);
			}
			PopMsg(bev_msg);
		}
		m.ParseFromString(bev_msg.second);
		if (m_eMsgDeal.find(m.mess_type()) != m_eMsgDeal.end()) {
			m_eMsgDeal[m.mess_type()]->PushMsg(bev_msg);
		}
	}
}

void ServerGateway::PushMsg(std::pair<bufferevent*, std::string>& bev_msg)
{
	{
		std::unique_lock<std::mutex> lk(m_lock);
		m_queue.push(std::move(bev_msg));
	}
	++m_write_index;
	m_cv.notify_one();
}

void ServerGateway::PopMsg(std::pair<bufferevent*, std::string>& bev_msg)
{
	bev_msg = std::move(m_queue.front());
	m_queue.pop();
	++m_read_index;
}

void ServerGateway::MsgFactory()
{
	m_eMsgDeal[common_enum::MESS_REGISTER] = std::make_shared<RegisterMsgDeal>();
	m_eMsgDeal[common_enum::MESS_LOGIN] = std::make_shared<LoginMsgDeal>();
}

void ServerGateway::RunFactoryMsg()
{
	for (auto& eMsgDeal : m_eMsgDeal) {
		std::thread(&MsgDeal::MsgDealCenter, eMsgDeal.second.get()).detach();
	}
}

} /* town */