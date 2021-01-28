#ifndef LOGIN_MSG_DEAL_H
#define LOGIN_MSG_DEAL_H

#include "ServerCommon.h"
#include "MsgDeal.h"

namespace town {

class LoginMsgDeal : public MsgDeal
{
public:
	LoginMsgDeal();
	~LoginMsgDeal();
	void MsgDealCenter(std::unique_ptr<MSG_DATA>& pMsgData) override;
};

} /* town */

#endif /* LOGIN_MSG_DEAL_H */