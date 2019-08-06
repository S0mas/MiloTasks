import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 480
    height: 640
    title: qsTr("Hello World")



    Column {
        spacing: 0
        anchors.fill:parent

        MyTextArea {
            id: normalTextAreaId
            width: parent.width
            height: parent.height / 2 - buttonsRowId.height/2
            textArea.text: "Normal text"
        }

        Row{
           id: buttonsRowId
           width: parent.width
           height: 20

           MyButton {
               id: buttonTranslateToNormal
               width: parent.width/2
               height: parent.height
               text:"Translate to normal text"
               onClicked: {
                   normalTextAreaId.textArea.text = translator.translateToNormalText(morseTextAreaId.textArea.text)
               }
           }

           MyButton {
               id: buttonTranslateToMorse
               width: parent.width/2
               height: parent.height
               text:"Translate to morse"
               onClicked: {
                   morseTextAreaId.textArea.text = translator.translateToMorseCode(normalTextAreaId.textArea.text)
               }
           }
        }

        MyTextArea {
            id: morseTextAreaId
            width: parent.width
            height: parent.height / 2 - buttonsRowId.height/2
            textArea.text: "Morse code"
        }
    }
}
