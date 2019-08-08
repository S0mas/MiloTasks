import QtQuick 2.11
import QtQuick.Controls 2.4
import QtMultimedia 5.11

Column {
    signal clickedNewGame()
    signal clickedUndo()
    signal clickedReset()
    signal clickedToggleAiCircle()
    signal clickedToggleAiCross()

    RoundButton {
        width: parent.width
        height: parent.height/5
        text: "New game"
        onClicked: {
            clickedNewGame()
            clickMenuButtonSoundId.play()
        }
    }

    RoundButton {
        width:parent.width
        height: parent.height/5
        text: "Undo"
        onClicked: {
            clickedUndo()
            clickMenuButtonSoundId.play()
        }
    }

    RoundButton {
        width:parent.width
        height: parent.height/5
        text: "Reset"
        onClicked: {
            clickedReset()
            clickMenuButtonSoundId.play()
        }
    }

    RoundButton {
        id:circleAiToggleButton
        width:parent.width
        height: parent.height/5
        text: "Circle AI off"
        onClicked: {
            clickedToggleAiCircle()
            clickMenuButtonSoundId.play()
        }
    }


    RoundButton {
        id: crossAiToggleButton
        width:parent.width
        height: parent.height/5
        text: "Cross AI off"
        onClicked: {
            clickedToggleAiCross()
            clickMenuButtonSoundId.play()
        }
    }

    SoundEffect {
        id: clickMenuButtonSoundId
        source: "sounds/clickMenuButton.wav"
    }

    Connections {
        target: game
        onToggleAiResponseSig: {
            if(player == 1)
                circleAiToggleButton.text = isOn ? "Circle AI on" : "Circle AI off"
            else
                crossAiToggleButton.text = isOn ? "Cross AI on" : "Cross AI off"
        }
    }
}
