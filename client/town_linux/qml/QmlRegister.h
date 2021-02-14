#ifndef QML_REGISTER_H
#define QML_REGISTER_H

#include <QObject>

namespace town {

class QmlRegister : public QObject
{
    Q_OBJECT
public:
    QmlRegister();
    ~QmlRegister();

public:
    Q_INVOKABLE void registerData();

signals:
    void signal_register();

}; /* QmlRegister */

} /* town */

#endif /* QML_REGISTER_H */
