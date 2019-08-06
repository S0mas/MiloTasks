import QtQuick 2.11
import QtQuick.Controls 2.4
import Philosophers 1.0

    ListView {
        height: 250
        width: 250
        model: PhilosophersModel {
            id: philosophersModelId
            list: philosopherList
        }

        delegate: Rectangle {
            width: parent.width
            height: 30
            color: "green"
            Text {
                anchors.centerIn: parent
                font.pointSize: 20
                text: model.display.eating
            }
        }

        Component.onCompleted: {
            philosopherList.start()
        }
    }

