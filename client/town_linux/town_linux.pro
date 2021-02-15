QT += quick
QT += network
QT += core

CONFIG += c++14

build_type =
CONFIG(debug, debug | release) {
    build_type = debug
} else {
    build_type = release
}

DESTDIR     = $$build_type/bin
OBJECTS_DIR = $$build_type/obj
MOC_DIR     = $$build_type/moc
RCC_DIR     = $$build_type/rcc
UI_DIR      = $$build_type/ui

system(ln -s `pwd`/config $$PWD/../build*/$$DESTDIR 2> /dev/null)
system(ln -s `pwd`/config $$PWD/build/$$DESTDIR 2> /dev/null)

# DEFINES += FILELOG  #LOG OUT FILE

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../../deps/protobuf/include/                # protobuf include
INCLUDEPATH += $$PWD/../../deps/protobuf/protofile/              # protobuf include
unix:!macx: LIBS += -L$$PWD/../../build/lib/ -lproto             # protobuf lib
unix:!macx: LIBS += -L$$PWD/../../deps/protobuf/lib/ -lprotobuf  # protobuf lib

INCLUDEPATH += $$PWD/../../third_party/boost_1_75_0              # boost include
INCLUDEPATH += $$PWD/../../third_party/spdlog-1.8.1/include      # spdlog include

INCLUDEPATH += $$PWD/common
INCLUDEPATH += $$PWD/communication
INCLUDEPATH += $$PWD/qml

HEADERS += \
        communication/ComCommon.h \
        communication/GlobalTcpClient.h \
        common/Booster.hpp \
        common/Logger.hpp \
        common/TownJson.hpp \
        qml/QmlCommon.h \
        qml/QmlRegister.h \

SOURCES += \
        main.cpp \
        communication/GlobalTcpClient.cpp \
        qml/QmlRegister.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
