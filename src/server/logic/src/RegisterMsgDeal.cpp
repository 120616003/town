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

void RegisterMsgDeal::MsgDealCenter(std::pair<bufferevent*, std::string>& bev_msg)
{
	acc_register ar;
	ar.ParseFromString(bev_msg.second);
	LOG_INFO("fd:{}", ServerEvent::GetInstance()->GetClientHandle(bev_msg.first)->GetEvutilSocket());
	LOG_INFO("type:{}", ar.type());
	LOG_INFO("email:{}", ar.email());
	LOG_INFO("passwd:{}", ar.passwd());
}

} /* town */