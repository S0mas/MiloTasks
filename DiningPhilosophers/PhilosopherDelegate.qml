import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle {
    id:philosopherDelegatId
    property alias indexText: textId.text
    property alias neededResource: neededResourcesTextId.text
    property alias handledResource: handledResourcesTextId.text
    property alias imageSource: imageId.source
    signal clicked
    Column {
        width: parent.width
        height: parent.height
        Row {
            width: parent.width
            height: parent.height/8

            RoundButton {
                width: height
                height: parent.height
                onClicked: {
                    philosopherDelegatId.clicked()
                }
                Image {
                    anchors.fill : parent
                    source: "images/cancel.png"
                }
            }

            Text {
                id:textId
                width: implicitWidth
                height: implicitHeight
            }
        }

        Image {
            id: imageId
            width: parent.width
            height: parent.height * 6/10
        }

        Label {
            width: implicitWidth
            height: implicitHeight
            text: "Needed Resources:"
        }

        Text {
            id:neededResourcesTextId
            width: implicitWidth
            height: implicitHeight
        }

        Label {
            width: implicitWidth
            height: implicitHeight
            text: "Handled Resources:"
        }

        Text {
            id:handledResourcesTextId
            width: implicitWidth
            height: implicitHeight
        }
    }
}
