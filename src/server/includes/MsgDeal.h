#ifndef MSG_DEAL_H
#define MSG_DEAL_H

#include "ServerCommon.h"

namespace town {

class MsgDeal
{
public:
	MsgDeal() {}
	virtual ~MsgDeal() {}
	virtual void MsgDealCenter() = 0;
	virtual void PushMsg(std::pair<bufferevent*, std::string>& bev_msg) = 0;
};

} /* town */

#endif /* MSG_DEAL_H */