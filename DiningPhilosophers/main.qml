import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 1080
    height: 640
    title: qsTr("Dining Philosophers")

    Philosophers{}
    Button {
        width: parent.width
        height: 20
        onClicked: {
            philosopherList.appendItem();
        }
        text:"add philosopher"
    }

    Component.onCompleted: {
        philosopherList.start()
    }
}
