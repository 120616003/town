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

void LoginMsgDeal::MsgDealCenter(std::unique_ptr<MSG_DATA>& pMsgData)
{
	acc_login al;
	al.ParseFromArray(pMsgData->data.get(), pMsgData->info.msg_len);
	LOG_INFO("fd:{}", ServerEvent::GetInstance()->GetClientHandle(pMsgData->bev)->GetEvutilSocket());
	LOG_INFO("type:{}", al.type());
	LOG_INFO("email:{}", al.email());
	LOG_INFO("passwd:{}", al.passwd());
}

} /* town */