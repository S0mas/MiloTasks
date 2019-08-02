import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Connections {
        target: game
        onGameEnded: {

        }
        onPlayerChanged: {

        }
        onBadMove: {

        }
        onUpdateSquare {

        }
    }

    Grid {
           columns: 5;
           rows: 3;
           spacing: 5
           Repeater {
               model: 9
               delegate: Rectangle {
                   MouseArea {
                     anchors.fill: parent
                     onClicked: {
                       game.move()
                     }
                   }
               }
           }
    }
}
