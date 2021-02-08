#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <string>

namespace town {

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient();
    ~TcpClient();

public:
    Q_INVOKABLE void writeData();

private slots:
    void ReadData();

private:
    QScopedPointer<QTcpSocket> m_pTcpClient;
}; /* TcpClient */

} /* town */

#endif /* TCP_CLIENT_H */
