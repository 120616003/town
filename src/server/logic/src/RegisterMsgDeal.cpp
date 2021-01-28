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

void RegisterMsgDeal::MsgDealCenter(std::unique_ptr<MSG_DATA>& pMsgData)
{
	acc_register ar;
	ar.ParseFromArray(pMsgData->data.get(), pMsgData->info.msg_len);
	LOG_INFO("fd:{}", ServerEvent::GetInstance()->GetClientHandle(pMsgData->bev)->GetEvutilSocket());
	LOG_INFO("type:{}", ar.type());
	LOG_INFO("email:{}", ar.email());
	LOG_INFO("passwd:{}", ar.passwd());
}

} /* town */