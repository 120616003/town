#include "ComCommon.h"
#include "Booster.hpp"
#include "TcpClient.h"
#include "user.pb.h"

namespace town {

TcpClient* TcpClient::GetInstance()
{
    static TcpClient impl;
    return &impl;
}

TcpClient::TcpClient()
{
    m_socket = new QTcpSocket;
    m_socket->connectToHost("127.0.0.1", 20000);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(ReadDate()));
}

TcpClient::~TcpClient()
{
}

void TcpClient::WriteData()
{
    std::string msg;
    MSG_INFO msg_info{};
    acc_register ar;
    ar.set_type(common_enum::ACC_EMAIL);
    ar.set_email("120616003@qq.com");
    ar.set_passwd("123456");
    msg = ar.SerializeAsString();
    msg_info.msg_type = MESS_REGISTER;

    msg_info.msg_len = msg.size();
    msg_info.msg_crc = Booster::Crc(reinterpret_cast<uint8_t*>(const_cast<char*>(msg.data())), msg_info.msg_len);
    m_socket->write(reinterpret_cast<const char*>(&msg_info), sizeof (MSG_INFO));
    m_socket->write(msg.data(), msg.length());
    m_socket->flush();
    LOG_INFO("WriteData");
}

void TcpClient::ReadDate()
{
    LOG_INFO("ReadDate");
}

}
