import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle {
    height: 30
    Text {
        anchors.centerIn: parent
        font.pointSize: 20
        text: model.display.eating ? "Eating" : "Thinking"
    }
    RoundButton {
        onClicked: {
            philosopherList.removeItem(index);
        }
    }
}
