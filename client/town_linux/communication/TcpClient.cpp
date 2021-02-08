#include "TcpClient.h"
#include "user.pb.h"
#include "Booster.hpp"
#include <QDebug>

enum MSG_TYPE : uint32_t {
    MESS_REGISTER = 0,
    MESS_LOGIN = 1
};

struct MSG_INFO {
    std::size_t msg_len = 0;
    MSG_TYPE msg_type = MESS_REGISTER;
    std::size_t msg_crc = 0;
};

namespace town {

TcpClient::TcpClient()
{
    m_pTcpClient.reset(new QTcpSocket());
    m_pTcpClient->connectToHost("127.0.0.1", 20000, QTcpSocket::ReadWrite);
    connect(m_pTcpClient.get(), SIGNAL(readyRead()), this, SLOT(ReadData()));
}

TcpClient::~TcpClient()
{
}

void TcpClient::writeData()
{
    qDebug() << "writeData";
//    static int count = 0;

    char buf[1024] = {};
    std::string msg;
    MSG_INFO msg_info{};
//    if (count++ % 2) {
//        acc_login al;
//        al.set_type(common_enum::ACC_PHONE);
//        al.set_email("1249152106@qq.com");
//        al.set_passwd("000000");
//        msg = al.SerializeAsString();
//        msg_info.msg_type = MSG_TYPE::MESS_LOGIN;
//    }
//    else {
        acc_register ar;
        ar.set_type(common_enum::ACC_EMAIL);
        ar.set_email("120616003@qq.com");
        ar.set_passwd("123456");
        msg = ar.SerializeAsString();
        msg_info.msg_type = MSG_TYPE::MESS_REGISTER;
//    }

    msg_info.msg_len = msg.size();
    msg_info.msg_crc = town::Booster::Crc(reinterpret_cast<uint8_t*>(const_cast<char*>(msg.data())), msg_info.msg_len);

    memcpy(buf, &msg_info, sizeof(MSG_INFO));
    memcpy(buf + sizeof(MSG_INFO), msg.data(), msg_info.msg_len);
    m_pTcpClient->write(buf, msg_info.msg_len + sizeof(MSG_INFO));
    m_pTcpClient->waitForReadyRead();
}

void TcpClient::ReadData()
{
    MSG_INFO msg_info{};
    m_pTcpClient->read((char*)&msg_info, sizeof(MSG_INFO));
    std::unique_ptr<uint8_t[]> data_buf(new uint8_t[msg_info.msg_len]());
    m_pTcpClient->read((char*)data_buf.get(), msg_info.msg_len);
    if (town::Booster::Crc(data_buf.get(), msg_info.msg_len) != msg_info.msg_crc) {
        qDebug() << "crc error";
    }
    acc_register ar;
    ar.ParseFromArray(data_buf.get(), msg_info.msg_len);
    qDebug() << "type:" << ar.err_type();
}

} /* town */


