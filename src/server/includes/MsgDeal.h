#ifndef MSG_DEAL_H
#define MSG_DEAL_H

#include "ServerCommon.h"

namespace town {

class MsgDeal
{
public:
	MsgDeal() {}
	virtual ~MsgDeal() {}
	virtual void MsgDealCenter(std::pair<bufferevent*, std::string>& bev_msg) = 0;

	void MsgForward()
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
			MsgDealCenter(bev_msg);
		}
	}

	void PushMsg(std::pair<bufferevent*, std::string>& bev_msg)
	{	
		m_queue.push(std::move(bev_msg));
		++m_write_index;
		m_cv.notify_one();
	}

private:
	void PopMsg(std::pair<bufferevent*, std::string>& bev_msg)
	{
		bev_msg = std::move(m_queue.front());
		m_queue.pop();
		++m_read_index;
	}

private:
	std::queue<std::pair<bufferevent*, std::string>> m_queue;
	uint64_t m_write_index = 0;
	uint64_t m_read_index = 0;
	std::mutex m_lock;
	std::condition_variable m_cv;
};

} /* town */

#endif /* MSG_DEAL_H */