import QtQuick 2.11
import QtQuick.Controls 2.4
    ListView {
        implicitHeight: 250
        implicitWidth: 250
        clip: true
        model: modelFull.list

        delegate: Rectangle {
            width: parent.width
            height: 60
            color: "green"
            Text {
                anchors.centerIn: parent
                font.pointSize: 20
                text: modelData.eating
            }
        }
    }

