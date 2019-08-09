import QtQuick 2.11
import QtQuick.Controls 2.4
import Philosophers 1.0

PathView {
    width: 400
    height: 400
    anchors.centerIn: parent
    model: PhilosophersModel {
        id: philosophersModelId
        list: philosopherList
    }

    delegate: PhilosopherDelegate {
        width: 120
        height: 120
        indexText: model.display.index + " " + (model.display.eating ? "Eating.." : "Thinking..")
        neededResource: model.display.neededResources[0] + " " + model.display.neededResources[1]
        handledResource: model.display.eating ? model.display.handledResources[0] + " " + model.display.handledResources[1] : ""
        imageSource: getImage(index)
        animationRunning: model.display.eating
        onClicked: {
            philosopherList.removeItem(index);
        }
    }
    path: Path {
        id: myPath
        startX: 0; startY: 0
        PathSvg { path: "M 200 200 m -200 0 a 200 200 0 1 0 400 0 a 200 200 0 1 0 -400 0" }
    }

    function getImage(index) {
        switch (index%5) {
        case 0:
            return "images/philosopher2.png"
        case 1:
            return "images/philosopher3.png"
        case 2:
            return "images/philosopher4.png"
        case 3:
            return "images/philosopher5.png"
        default:
            return "images/philosopher6.png"
        }
    }
}

