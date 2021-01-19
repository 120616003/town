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

void ServerGateway::MsgForwardCenter()
{
	MsgFactory();
	RunFactoryMsg();

	while (true) {
		std::tuple<bufferevent*, MSG_INFO::MSG_TYPE, std::string> bev_msg;
		{
			std::unique_lock<std::mutex> lk(m_lock);
			while (m_read_index == m_write_index) {
				m_cv.wait_for(lk, 1s);
			}
			PopMsg(bev_msg);
		}

		if (m_eMsgDeal.find(std::get<1>(bev_msg)) != m_eMsgDeal.end()) {
			std::pair<bufferevent*, std::string> bmsg{std::get<0>(bev_msg), std::move(std::get<2>(bev_msg))};
			m_eMsgDeal[std::get<1>(bev_msg)]->PushMsg(bmsg);
		}
	}
}

void ServerGateway::PushMsg(std::tuple<bufferevent*, MSG_INFO::MSG_TYPE, std::string>& bev_msg)
{
	{
		std::unique_lock<std::mutex> lk(m_lock);
		m_queue.push(std::move(bev_msg));
	}
	++m_write_index;
	m_cv.notify_one();
}

void ServerGateway::PopMsg(std::tuple<bufferevent*, MSG_INFO::MSG_TYPE, std::string>& bev_msg)
{
	bev_msg = std::move(m_queue.front());
	m_queue.pop();
	++m_read_index;
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

} /* town */