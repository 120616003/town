#include "ComCommon.h"
#include "Booster.hpp"
#include "GlobalTcpClient.h"

namespace town {

GlobalTcpClient* GlobalTcpClient::GetInstance()
{
    static GlobalTcpClient impl;
    return &impl;
}

void GlobalTcpClient::Initialization(QString strIp, int iPort)
{
    m_socket = std::make_unique<QTcpSocket>();
    m_strIp = strIp;
    m_iPort = iPort;
    connect(m_socket.get(), SIGNAL(readyRead()), this, SLOT(RecvDate()));
    connect(m_socket.get(), SIGNAL(connected()), this, SLOT(Connected()));
    connect(m_socket.get(), SIGNAL(disconnected()), this, SLOT(DisConnected()));
    ConnectServer();
}

bool GlobalTcpClient::GetNetworkStatus()
{
    return m_bNetworkStatus;
}

GlobalTcpClient::GlobalTcpClient()
{
}

GlobalTcpClient::~GlobalTcpClient()
{
}

void GlobalTcpClient::SendData(const char* pMsg, std::size_t iLen)
{
    m_socket->write(pMsg, iLen);
    m_socket->flush();
}

void GlobalTcpClient::RecvDate()
{
}

void GlobalTcpClient::SetNetworkStatus(bool bNetworkStatus)
{
    m_bNetworkStatus = bNetworkStatus;
}

void GlobalTcpClient::ConnectServer()
{
    m_socket->connectToHost(m_strIp, m_iPort);
}

void GlobalTcpClient::Connected()
{
    SetNetworkStatus(true);
    emit NetworkStatus(true);
}

void GlobalTcpClient::DisConnected()
{
    SetNetworkStatus(false);
    emit NetworkStatus(false);
}

}
