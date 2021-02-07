import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

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


    Button{
        x:320  //设置按钮的横坐标
        y:240  //设置纵坐标
        text:"注冊"

        //信号槽连接
        onClicked: {
            console.log("我被点击了")
            Qt.quit()
        }
    }
}
