import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import Philosophers 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    PathView {
        width: 400
        height: 400
        anchors.centerIn: parent
        model: PhilosophersModel {
            id: philosophersModelId
            list: philosopherList
        }

        delegate: RoundButton {
            width: 40
            height: 40
            radius: 20
            background: Rectangle {
                        color: model.display.eating ? "yellow" : "brown"
                    }
            Text {
                anchors.centerIn: parent
                font.pointSize: 20
                text: model.display.index
                transform: [
                    Translate {y: -30}
                ]
            }
            onClicked: {
                philosopherList.removeItem(index);
            }
        }
        path: Path {
            id: myPath
            startX: 0; startY: 0
            PathSvg { path: "M 200 200 m -200 0 a 200 200 0 1 0 400 0 a 200 200 0 1 0 -400 0" }
        }

        Component.onCompleted: {
            philosopherList.start()
        }
    }
    Button {
        width: parent.width
        height: 20
        onClicked: {
            philosopherList.appendItem();
        }
        text:"add philosopher"
    }
}
