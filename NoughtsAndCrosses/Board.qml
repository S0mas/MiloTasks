import QtQuick 2.11
import QtQuick.Controls 2.4
import QtMultimedia 5.11

Item {
    property alias repeater: repeaterId
    property int activePlayerSign: 1
    width: 280
    height: 280
    Rectangle {
        color: "black"
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
                delegate: BoardSquare {
                    id: rectId
                    width:90
                    height:90
                    onSquareClicked: {
                        game.move(index, activePlayerSign)
                    }
                }

            }
        }

        SoundEffect {
            id: goodMoveSoundId
            source: "sounds/goodMove.wav"
        }

        SoundEffect {
            id: badMoveSoundId
            source: "sounds/badMove.wav"
        }

        SoundEffect {
            id: drawSoundId
            source: "sounds/draw.wav"
        }

        SoundEffect {
            id: winSoundId
            source: "sounds/win.wav"
        }

        Connections {
            target: game
            onUpdateSquareSig: {
                repeater.itemAt(index).playerSign = player
                if(player != 0)
                    goodMoveSoundId.play()
            }
            onPlayerChangedSig: {
                activePlayerSign = player
            }
            onGameEndedSig: {
                if(player == 0)
                    drawSoundId.play()
                else
                    winSoundId.play()
                for(var i = 0; i < squares.length; ++i)
                   repeater.itemAt(squares[i]).animation.start()
            }

            onBadMoveSig: {
                badMoveSoundId.play()
            }
        }
    }
}
