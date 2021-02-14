#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QmlRegister.h"
#include "TcpClient.h"
#include <thread>
#include <unistd.h>
#include <QVector>
using namespace town;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    QObject obj;
//    obj.moveToThread(TcpClient::GetInstance());
//    TcpClient::GetInstance()->start();
    qmlRegisterType<QmlRegister>("QmlRegister", 1, 0, "QmlRegister");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
