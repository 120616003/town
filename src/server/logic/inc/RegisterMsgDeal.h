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
	void MsgDealCenter(std::unique_ptr<MSG_DATA>& pMsgData) override;
};

} /* town */

#endif /* REGISTER_MSG_DEAL_H */