import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: boardId.width
    height: boardId.height + scoreRowId.height + buttonsColumnId.height
    title: qsTr("Hello World")
    property int activePlayerSign: 1
    property int startX: 0
    property int startY: 0
    property int stopX: 0
    property int stopY: 0
    property bool endLineVisible: false
    property int scoreCross: 0
    property int scoreCircle: 0
    Connections {
        target: game
        onGameEnded: {
            if(player == 1)
                ++scoreCircle
            else if(player == 2)
                ++scoreCross
            endLineVisible = true
            startX = boardId.repeater.itemAt(startIndex).x + 45
            startY = boardId.repeater.itemAt(startIndex).y + 115
            stopX = boardId.repeater.itemAt(stopIndex).x + 45
            stopY = boardId.repeater.itemAt(stopIndex).y + 115
            canvasId.requestPaint()
        }
        onPlayerChanged: {
            activePlayerSign = player
        }
        onBadMove: {
            console.log("onBadMove");
        }
        onUpdateSquare: {
            boardId.repeater.itemAt(index).playerSign = player
        }
    }

    Row {
        height: boardId.width/4
        width: boardId.width
        id: scoreRowId

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
                anchors.centerIn: parent
                text: scoreCross
                font.pointSize: 30
            }
        }

        Rectangle {
            height: parent.height
            width: height
            Text {
                anchors.centerIn: parent
                text: scoreCircle
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
    }

    Rectangle {
        id: boardId
        y: scoreRowId.height
        width: 280
        height: 280
        color: "black"
        property alias repeater: repeaterId
        Grid {
            id:gridId
            anchors.fill:parent
            anchors.centerIn: parent
            columns: 3
            rows: 3
            spacing: 5
            Repeater {
                id:repeaterId
                model: 9
                delegate: Rectangle {
                    id: rectId
                    width:90
                    height:90
                    property int playerSign: 0
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            game.move(index, activePlayerSign)
                        }
                    }

                    Image {
                        id: imageId
                        anchors.fill: parent
                        source: getImage(playerSign)
                        onSourceChanged: {
                            scaleAnimationId.start()
                            rotationAnimationId.start()
                        }
                    }

                    ScaleAnimator {
                        id: scaleAnimationId
                        target: imageId
                        from: 0.5
                        to: 1
                        easing.type: Easing.OutQuart
                        duration: 1000
                    }

                    RotationAnimator {
                        id:rotationAnimationId
                        target: imageId;
                        from: 0;
                        to: 360;
                        easing.type: Easing.OutQuart
                        duration: 1000
                    }
                }
            }
        }
    }

    function getImage(number) {
        switch (number) {
        case 0:
            return "";
        case 1:
            return "images/circle.png";
        case 2:
            return "images/cross.png";
        }
    }

    Canvas {
        id: canvasId
        anchors.fill: parent
        onPaint: {
            if(endLineVisible)
                drawLine()
            else
                clear()
        }

        function drawLine() {
            var ctx = getContext('2d')
            ctx.lineWidth = 5
            ctx.strokeStyle = "black"
            ctx.beginPath()
            ctx.moveTo(startX, startY)
            ctx.lineTo(stopX, stopY)
            ctx.stroke()
        }

        function clear() {
            var ctx = getContext('2d')
            ctx.reset()
            ctx.stroke()
        }

    }
    Column {
        id: buttonsColumnId
        y : boardId.height + boardId.y
        width: boardId.width
        height: newGameButton.height + undoButton.height + resetButton.height + circleAiToggleButton.height + crossAiToggleButton.height
        Rectangle {
            width:parent.width
            height: 40
            id: newGameButton
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    endLineVisible = false
                    canvasId.requestPaint()
                    game.newGame()
                }
            }

            Text {
                anchors.centerIn: parent
                text: "New game"
            }
        }

        Rectangle {
            width:parent.width
            height: 40
            id: undoButton
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    game.undo()
                }
            }
            Text {
                anchors.centerIn: parent
                text: "Undo"
            }
        }

        Rectangle {
            width:parent.width
            height: 40
            id: resetButton
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    game.reset()
                }
            }

            Text {
                anchors.centerIn: parent
                text: "Reset"
            }
        }

        Connections {
            target: game
            onToggleAiSig: {
                if(player == 1) {
                    circleAiToggleButton.color = isOn ? "greenyellow" : "white"
                }
                else {
                    crossAiToggleButton.color = isOn ? "greenyellow" : "white"
                }
            }
        }

        Rectangle {
            width:parent.width
            height: 40
            id: circleAiToggleButton
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    game.toggleAi(1)
                }
            }

            Text {
                anchors.centerIn: parent
                text: "ToggleAi for circle"
            }
        }

        Rectangle {
            width:parent.width
            height: 40
            id: crossAiToggleButton

            MouseArea {
                id:mouseAreaId
                anchors.fill: parent
                anchors.centerIn: parent
                onClicked: {
                    game.toggleAi(2)
                }
            }
            Text {
                anchors.centerIn: parent
                text: "ToggleAi for cross"
            }
        }
    }

    Component.onCompleted: {
        game.newGame()
    }
}


