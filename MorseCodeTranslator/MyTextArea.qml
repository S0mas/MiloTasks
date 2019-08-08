import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.2

Rectangle {
    id: rectId
    property alias textArea : textAreaId
    FileDialog {
        id: fileDialogLoadId
        title: "Please choose a file to load"
        modality: Qt.ApplicationModal
        nameFilters: [ "Text files (*.txt)" ]
        onAccepted: {
            var request = new XMLHttpRequest()
            request.open('GET', fileUrls)
            request.onreadystatechange = function(event) {
                if (request.readyState == XMLHttpRequest.DONE)
                    textArea.text = request.responseText
            }
            request.send()
        }
    }

    FileDialog {
        id: fileDialogSaveId
        title: "Please choose file to save"
        modality: Qt.ApplicationModal
        nameFilters: [ "Text files (*.txt)" ]
        selectExisting: false
        onAccepted: {
            var request = new XMLHttpRequest();
            request.open("PUT", fileUrl, false);
            request.send(textArea.text);
            return request.status;
        }
    }
    Column {
        width:parent.width
        height:parent.height
        RoundButton {
            id: buttonLoadId
            width:parent.width
            height:20
            onClicked: {
                fileDialogLoadId.open()
            }
            text: "Load from file"
        }

        RoundButton {
            id: buttonSaveId
            width:parent.width
            height:20
            onClicked: {
                fileDialogSaveId.open()
            }
            text: "Save to file"
        }

        ScrollView{
            width:parent.width
            height:parent.height-buttonLoadId.height - buttonSaveId.height
            TextArea {
                id:textAreaId
                wrapMode: TextArea.Wrap
                background: Rectangle{
                    anchors.fill: parent
                    color: "black"
                }
                color: "white"
            }
        }
    }
}
