import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
//import QmlRegister 1.0

Window {
    visible: true
    width: 540
    height: 960

    Page {
        anchors.fill: parent
        header: Label {
            padding: 10
            text: qsTr("Contacts")
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        topMargin: 48
        leftMargin: 48
        bottomMargin: 48
        rightMargin: 48
        spacing: 20
        model: ["Albert Einstein", "Ernest Hemingway", "Hans Gude"]
        delegate: ItemDelegate {
            text: modelData
            width: listView.width - listView.leftMargin - listView.rightMargin
            height: avatar.implicitHeight
            leftPadding: avatar.implicitWidth + 32

            Image {
                id: avatar
                source: "qrc:/ui/images/" + modelData.replace(" ", "_") + ".png"
            }
        }
    }


//    title: qsTr("Hello World")

//    Text {

//        text: "Qt Quick"
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.verticalCenter: parent.verticalCenter
//        font.pointSize: 24
//    }

//    QmlRegister
//    {
//        id:register
//    }


//    Button{
//        x:320  //设置按钮的横坐标
//        y:240  //设置纵坐标
//        text:"注冊"

//        //信号槽连接
//        onClicked: {
//            register.registerData()
//            return true;
//        }
//    }
}
