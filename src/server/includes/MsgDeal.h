#ifndef MSG_DEAL_H
#define MSG_DEAL_H

#include "ServerCommon.h"

class MsgDeal
{
public:
	MsgDeal() {}
	virtual ~MsgDeal() {}

	virtual void PushMsg(bufferevent* bev, std::string& msg) = 0;
};

#endif /* MSG_DEAL_H */