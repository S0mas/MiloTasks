import QtQuick 2.11
import QtQuick.Window 2.11
import MyEnums 1.0
//JS function for calculating start and stops coords for line drawing
//Animations of X's and 0's
//Buttons for new game, undo etc.
//Scoring counter
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property int activePlayerSign: 1
    property int startX: 0
    property int startY: 0
    property int stopX: 0
    property int stopY: 0
    Connections {
        target: game
        onGameEnded: {
            console.log("onGameEnded");
            var sq = squares
            startX = 0
            stopX = 280
            startY = 140
            stopY = 140
            var ctx = canvasX.getContext('2d')
            canvasX.requestPaint()

        }
        onPlayerChanged: {
            activePlayerSign = player
        }
        onBadMove: {
            console.log("onBadMove");
        }
        onUpdateSquare: {
            console.log("onUpdateSquare");
        }
    }
    Rectangle {
        width: 280
        height: 280
        color: "black"
        Grid {
            anchors.fill:parent
            anchors.centerIn: parent
            columns: 3
            rows: 3
            spacing: 5
            Repeater {
                model: 9
                delegate: Rectangle {
                    width:90
                    height:90
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            game.move(index%3, index/3, activePlayerSign)
                            color = activePlayerSign ? "black" : "yellow"
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        game.newGame()
    }

    Canvas {
        id: line
        anchors.fill: parent

        onPaint: {
            var ctx = getContext('2d')
            ctx.lineWidth = 5
            ctx.strokeStyle = "red"
            ctx.beginPath()
            ctx.moveTo(stopX+260, startY+20)
            ctx.lineTo(startX+20, stopY+260)
            ctx.stroke()
        }
    }

    Canvas {
        id: cross
        anchors.fill: parent

        onPaint: {
            var ctx = getContext('2d')
            ctx.lineWidth = 5
            ctx.strokeStyle = "blue"
            ctx.beginPath()
            ctx.moveTo(startX+15, startY+15)
            ctx.lineTo(stopX+75, stopY+75)
            ctx.moveTo(stopX+75, startY+15)
            ctx.lineTo(startX+15, stopY+75)
            ctx.stroke()
        }
    }

    Canvas {
        id: zero
        anchors.fill: parent

        onPaint: {
            var ctx = getContext('2d')
            var centreX = startX+45 ;
            var centreY = startY+45 ;
            ctx.lineWidth = 5
            ctx.strokeStyle = "black"
            ctx.beginPath();
            ctx.arc(centreX, centreY, 30, 0, Math.PI * 2, false);
            ctx.stroke();
        }
    }
}


