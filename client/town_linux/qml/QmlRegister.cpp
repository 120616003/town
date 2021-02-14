#include "QmlRegister.h"
#include "QmlCommon.h"
#include "TcpClient.h"


namespace town {

QmlRegister::QmlRegister()
{
    connect(this, SIGNAL(signal_register()), TcpClient::GetInstance(), SLOT(WriteData()));
}

QmlRegister::~QmlRegister()
{
}

void QmlRegister::registerData()
{
    emit signal_register();
}

} /* town */
