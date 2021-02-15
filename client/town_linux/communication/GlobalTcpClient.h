#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QString>
#include <memory>

namespace town {

class GlobalTcpClient : public QObject
{
    Q_OBJECT
public:
    static GlobalTcpClient* GetInstance();
    void Initialization(QString strIp, int iPort);
    bool GetNetworkStatus(); // 获取网络状态（主动获取）

public slots:
    void SendData(const char* pMsg, std::size_t iLen); // 发送数据

signals:
    void NetworkStatus(bool flag); // 获取网络状态（被动获取）

private:
    GlobalTcpClient();
    ~GlobalTcpClient();
    void SetNetworkStatus(bool bNetworkStatus);
    void ConnectServer();

private slots:
    void RecvDate(); // 接受数据
    void Connected();
    void DisConnected();

private:
    std::unique_ptr<QTcpSocket> m_socket = nullptr;
    bool m_bNetworkStatus = false;
    QString m_strIp;
    int m_iPort = 0;
};

}

#endif // TCPSOCKET_H
