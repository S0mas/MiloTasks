import QtQuick 2.0
import QtQuick.Controls 2.4
import Philosophers.model 1.0

Frame {
    ListView {
        implicitHeight: 250
        implicitWidth: 250
        clip: true
        model: PhilosophersModel {
            list: philosophersList
        }

        delegate: Rectangle {
            width: parent.width
            height: 60
            color: model.isEating ? "green" : "red"
            Text {
                anchors.centerIn: parent
                font.pointSize: 20
                text: model.id
            }
        }
    }
}
