import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle {
    id: rectId
    signal clickedLoad()
    signal clickedSave()
    property alias textArea : textAreaId
    Column {
        width:parent.width
        height:parent.height
        MyButton {
            id: buttonLoadId
            width:parent.width
            height:20
            onClicked: {
                rectId.clickedLoad()
            }
            text: "Load from file"
        }

        MyButton {
            id: buttonSaveId
            width:parent.width
            height:20
            onClicked: {
                rectId.clickedSave()
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
