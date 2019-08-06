import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import Philosophers 1.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
        Philosophers {
            id: philos
            width: parent.width
            height: 300
            anchors.centerIn: parent
        }
        Column {
            width: parent.width
            height: 60
            anchors.top : philos.bottom
        Button {
            width:parent.width
            height: 30
            text: "add"
            onClicked: {
                philosopherList.appendItem()
            }
        }

        Button {
            width:parent.width
            height: 30
            text: "remove"
            onClicked: {
                philosopherList.removeItem()
            }
        }
        }
}
