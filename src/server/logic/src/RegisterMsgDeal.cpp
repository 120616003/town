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
    MSG_INFO msg_info {};
    msg_info.msg_len = msg.size();
    msg_info.msg_type = MESS_REGISTER;
    msg_info.msg_crc = Booster::Crc(reinterpret_cast<uint8_t*>(const_cast<char*>(msg.data())), msg_info.msg_len);
    char buf[1024] = {};
    memcpy(buf, &msg_info, sizeof(MSG_INFO));
    memcpy(buf + sizeof(MSG_INFO), msg.data(), msg_info.msg_len);
    int ret = bufferevent_write(pMsgData->bev, buf, sizeof(MSG_INFO) + msg_info.msg_len);
    bufferevent_flush(pMsgData->bev, 0, BEV_FLUSH);
    LOG_DEBUG("ret:{}", ret);
}

} /* town */