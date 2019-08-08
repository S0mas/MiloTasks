import QtQuick 2.11
import QtQuick.Controls 2.4

Row {
    property int scoreCircle: 0
    property int scoreCross: 0
    height:90
    width:90
    Rectangle {
        height: parent.height
        width: height
        Image {
            anchors.fill:parent
            source: "images/cross.png"
        }
    }

    Rectangle {
        height: parent.height
        width: height
        Text {
            text:scoreCross
            anchors.centerIn: parent
            font.pointSize: 30
        }
    }

    Rectangle {
        height: parent.height
        width: height
        Text {
            text:scoreCircle
            anchors.centerIn: parent
            font.pointSize: 30
        }
    }

    Rectangle {
        height: parent.height
        width: height
        Image {
            anchors.fill:parent
            source: "images/circle.png"
        }
    }

    Connections {
        target: game
        onGameEndedSig: {
            if(player == 1)
                ++scoreCircle
            else if(player == 2)
                ++scoreCross
        }
    }
}
