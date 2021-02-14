#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>

#include "RegisterMsgDeal.h"
#include "ServerEvent.h"
#include "ClientHandle.h"
#include "MysqlOptHandleInfc.h"

namespace town {

RegisterMsgDeal::RegisterMsgDeal()
{
}

RegisterMsgDeal::~RegisterMsgDeal()
{
}

void RegisterMsgDeal::MsgDealCenter(std::unique_ptr<MSG_DATA>& pMsgData)
{   
    std::string strUuid = Booster::GetUUID();
    std::string msg = GetMysqlOpt()->GetOptHandle(ADD)->RegisterUser(pMsgData->data.get(), pMsgData->info.msg_len, strUuid);
    WriteData(pMsgData->bev, msg, MESS_REGISTER);
}

} /* town */