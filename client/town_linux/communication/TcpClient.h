#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

namespace town {

class TcpClient : public QObject
{
    Q_OBJECT
public:
    static TcpClient* GetInstance();

private:
    TcpClient();
    ~TcpClient();

public slots:
    void WriteData();
    void ReadDate();

private:
    QTcpSocket* m_socket;
};

}

#endif // TCPSOCKET_H
