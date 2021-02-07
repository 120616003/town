#include "TcpClient.h"

TcpClient::TcpClient()
{
    m_pTcpClient.reset(new QTcpSocket());
    m_pTcpClient->connectToHost("127.0.0.1", 20000, QTcpSocket::ReadWrite);
    connect(m_pTcpClient.get(), SIGNAL(readyRead()), this, SLOT(ReadData()));
}

TcpClient::~TcpClient()
{
}

void TcpClient::ReadData()
{

}
