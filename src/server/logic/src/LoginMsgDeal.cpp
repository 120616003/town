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
    std::string msg = GetMysqlOpt()->GetOptHandle(ADD)->LoginAcc(pMsgData->data.get(), pMsgData->info.msg_len);
    WriteData(pMsgData->bev, msg, MESS_LOGIN);
}

} /* town */