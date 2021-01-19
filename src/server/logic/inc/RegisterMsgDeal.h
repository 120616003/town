#ifndef REGISTER_MSG_DEAL_H
#define REGISTER_MSG_DEAL_H

#include "MsgDeal.h"

namespace town {

class RegisterMsgDeal : public MsgDeal
{
public:
	RegisterMsgDeal();
	~RegisterMsgDeal();
	
	void MsgDealCenter() override;
	void PushMsg(std::pair<bufferevent*, std::string>& bev_msg) override;

private:
	void PopMsg(std::pair<bufferevent*, std::string>& bev_msg);

private:
	std::queue<std::pair<bufferevent*, std::string>> m_queue;
	uint64_t m_write_index = 0;
	uint64_t m_read_index = 0;
	std::mutex m_lock;
	std::condition_variable m_cv;
};

} /* town */

#endif /* REGISTER_MSG_DEAL_H */