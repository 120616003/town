#include <chrono>
#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>

#include "ServerCommon.h"
#include "ServerGateway.h"
#include "ServerEvent.h"
#include "ClientHandle.h"
#include "user.pb.h"

using namespace std::chrono_literals;

namespace town {

ServerGateway::ServerGateway()
{
}

ServerGateway::~ServerGateway()
{
}

void ServerGateway::DataDealCenter()
{
	while (true) {
		std::pair<bufferevent*, std::string> bev_msg;
		{
			std::unique_lock<std::mutex> lk(m_lock);
			while (m_read_index == m_write_index) {
				m_cv.wait_for(lk, 1s);
			}
			PopMsg(bev_msg);
		}

		DataForward(bev_msg);
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

void ServerGateway::DataForward(std::pair<bufferevent*, std::string>& bev_msg)
{
	message m;
	m.ParseFromString(bev_msg.second);

	switch (m.mess_type()) {
		case common_enum::MESS_REGISTER: {
			RegisterMsg(bev_msg.first, m.mess_data());
			break;
		}
		case common_enum::MESS_LOGIN: {
			LoginMsg(bev_msg.first, m.mess_data());
			break;
		}
		default:
		LOG_ERROR("message type unknow:{}", m.mess_type());
		break;
	}
}

void ServerGateway::RegisterMsg(bufferevent* bev, const std::string& msg)
{
	acc_register ar;
	ar.ParseFromString(msg);
	// LOG_INFO("fd:{}", ServerEvent::GetInstance()->GetClientHandle(bev)->GetEvutilSocket());
	// LOG_INFO("type:{}", ar.type());
	// LOG_INFO("email:{}", ar.email());
	// LOG_INFO("passwd:{}", ar.passwd());
}

void ServerGateway::LoginMsg(bufferevent* bev, const std::string& msg)
{
}

} /* town */