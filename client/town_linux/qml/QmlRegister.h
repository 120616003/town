#ifndef QML_REGISTER_H
#define QML_REGISTER_H

#include <QObject>

namespace town {

class QmlRegister : public QObject
{
public:
    QmlRegister();
    ~QmlRegister();

public:
    Q_INVOKABLE void registerData();

}; /* QmlRegister */

} /* town */

#endif /* QML_REGISTER_H */
