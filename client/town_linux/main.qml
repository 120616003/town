import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QmlRegister 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {

        text: "Qt Quick"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 24
    }

    QmlRegister
    {
        id:register
    }


    Button{
        x:320  //设置按钮的横坐标
        y:240  //设置纵坐标
        text:"注冊"

        //信号槽连接
        onClicked: {
            register.registerData()
            return true;
        }
    }
}
