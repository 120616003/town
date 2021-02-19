#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>

#include "CommonMsgDeal.h"
#include "user.pb.h"
#include "ServerEvent.h"
#include "ClientHandle.h"

namespace town {

CommonMsgDeal::CommonMsgDeal()
{
}

CommonMsgDeal::~CommonMsgDeal()
{
}

void CommonMsgDeal::MsgDealCenter(std::unique_ptr<MSG_DATA>& pMsgData)
{
    // std::string strUuid;
    // std::string msg = GetMysqlOpt()->GetOptHandle(ADD)->LoginAcc(pMsgData->data.get(), pMsgData->info.msg_len, strUuid);
    // if (strUuid.size()) {
    //     GetServerHandle()->GetClientHandle(pMsgData->bev)->SetUUID(strUuid);
    // }
    // WriteData(pMsgData->bev, msg, MESS_LOGIN);
}

} /* town */