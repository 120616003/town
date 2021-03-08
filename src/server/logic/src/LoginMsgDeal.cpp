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
    std::string strUuid;
    std::string msg = GetMysqlOpt()->GetOptHandle(ADD)->LoginAcc(pMsgData->data.get(), pMsgData->info.msg_len, strUuid);
    if (strUuid.size()) {
        GetServerHandle()->GetClientHandle(pMsgData->bev)->SetUUID(strUuid);
        GetServerHandle()->GetClientHandle(pMsgData->bev)->SetStatus(true);
        GetServerHandle()->RecordClient(strUuid, pMsgData->bev); // 通过uuid记录登录用户
    }
    WriteData(pMsgData->bev, msg, MESS_LOGIN);
}

} /* town */