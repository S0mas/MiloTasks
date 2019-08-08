import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: app.width
    height:app.height
    title: qsTr("Nought and Crosses")

    NoughtAndCrosses{
        id:app
        width: 280
        height: 570
        anchors.centerIn: parent
    }
}
