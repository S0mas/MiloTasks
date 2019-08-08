import QtQuick 2.11
import QtQuick.Controls 2.4
Item {
    Column{
        height:parent.height
        width:parent.width
        ScoreRow {
            id: scoreRowId
            height: parent.width/4
            width: parent.width
        }

        Board {
            id: boardId
            width: 280
            height: 280
        }

        MenuButtons{
            id:menuButtonsId
            width: boardId.width
            height: 200

            onClickedNewGame: {
                canvasId.endLineVisible = false
                canvasId.requestPaint()
                game.newGame()
            }

            onClickedUndo: {
                game.undo()
            }

            onClickedReset: {
                game.reset()
            }

            onClickedToggleAiCircle: {
                game.toggleAi(1)
            }

            onClickedToggleAiCross: {
                game.toggleAi(2)
            }
        }

        Component.onCompleted: {
            game.newGame()
        }
    }

    CanvasItem {
        id: canvasId
        Connections {
            target: game
            onGameEndedSig: {
                if(squares.length !== 0){
                    canvasId.endLineVisible = true
                    canvasId.startX = boardId.repeater.itemAt(squares[0]).x + 45
                    canvasId.startY = boardId.repeater.itemAt(squares[0]).y + 115
                    canvasId.stopX = boardId.repeater.itemAt(squares[2]).x + 45
                    canvasId.stopY = boardId.repeater.itemAt(squares[2]).y + 115
                    canvasId.requestPaint()
                }
            }
        }
    }
}
