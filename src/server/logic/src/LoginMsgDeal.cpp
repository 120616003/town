#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>

#include "LoginMsgDeal.h"
#include "user.pb.h"
#include "ServerEvent.h"
#include "ClientHandle.h"

namespace town {

LoginMsgDeal::LoginMsgDeal()
{
}

LoginMsgDeal::~LoginMsgDeal()
{
}

void LoginMsgDeal::MsgDealCenter(std::pair<bufferevent*, std::string>& bev_msg)
{
	acc_login al;
	al.ParseFromString(bev_msg.second);
	LOG_INFO("fd:{}", ServerEvent::GetInstance()->GetClientHandle(bev_msg.first)->GetEvutilSocket());
	LOG_INFO("type:{}", al.type());
	LOG_INFO("email:{}", al.email());
	LOG_INFO("passwd:{}", al.passwd());
}

} /* town */