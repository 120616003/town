#ifndef REGISTER_MSG_DEAL_H
#define REGISTER_MSG_DEAL_H

#include "ServerCommon.h"
#include "MsgDeal.h"

namespace town {

class RegisterMsgDeal : public MsgDeal
{
public:
	RegisterMsgDeal();
	~RegisterMsgDeal();
	void MsgDealCenter(std::pair<bufferevent*, std::string>& bev_msg) override;
};

} /* town */

#endif /* REGISTER_MSG_DEAL_H */