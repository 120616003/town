#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient();
    ~TcpClient();

private slots:
    void ReadData();

private:
    QScopedPointer<QTcpSocket> m_pTcpClient;
};

#endif /* TCP_CLIENT_H */
