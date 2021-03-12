#include "QmlRegister.h"
#include "QmlCommon.h"
#include "GlobalTcpClient.h"


namespace town {

QmlRegister::QmlRegister()
{
//    connect(this, SIGNAL(signal_register()), GlobalTcpClient::GetInstance(), SLOT(SendData()));
}

QmlRegister::~QmlRegister()
{
}

void QmlRegister::registerData()
{
    emit signal_register();
}

} /* town */
