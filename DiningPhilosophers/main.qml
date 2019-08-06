import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
        Philosophers {
            width: parent.width
            height: 300
            anchors.centerIn: parent
        }

        Button {
            width:parent.width
            height: 30
            text: "add"
            onClicked: {
                modelFull.add()
            }
        }
}
