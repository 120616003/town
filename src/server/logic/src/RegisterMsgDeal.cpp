#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>

#include "RegisterMsgDeal.h"
#include "user.pb.h"
#include "ServerEvent.h"
#include "ClientHandle.h"

namespace town {

RegisterMsgDeal::RegisterMsgDeal()
{
}

RegisterMsgDeal::~RegisterMsgDeal()
{
}

void RegisterMsgDeal::MsgDealCenter()
{
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

		acc_register ar;
		ar.ParseFromString(m.mess_data());
		LOG_INFO("fd:{}", ServerEvent::GetInstance()->GetClientHandle(bev_msg.first)->GetEvutilSocket());
		LOG_INFO("type:{}", ar.type());
		LOG_INFO("email:{}", ar.email());
		LOG_INFO("passwd:{}", ar.passwd());
	}
}

void RegisterMsgDeal::PushMsg(std::pair<bufferevent*, std::string>& bev_msg)
{
	m_queue.push(std::move(bev_msg));
	++m_write_index;
	m_cv.notify_one();
}


void RegisterMsgDeal::PopMsg(std::pair<bufferevent*, std::string>& bev_msg)
{
	bev_msg = std::move(m_queue.front());
	m_queue.pop();
	++m_read_index;
}

} /* town */