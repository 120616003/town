#ifndef COMMON_MSG_DEAL_H
#define COMMON_MSG_DEAL_H

#include "ServerCommon.h"
#include "MsgDeal.h"

namespace town {

class CommonMsgDeal : public MsgDeal
{
public:
	CommonMsgDeal();
	~CommonMsgDeal();
	void MsgDealCenter(std::unique_ptr<MSG_DATA>& pMsgData) override;
};

} /* town */

#endif /* COMMON_MSG_DEAL_H */