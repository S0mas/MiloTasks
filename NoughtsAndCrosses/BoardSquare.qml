import QtQuick 2.11
import QtQuick.Controls 2.4
Item {
    width: 90
    height: 90
    property int playerSign: 0
    signal squareClicked
    property alias animation : scaleAnimationId
    Button {
        width: parent.height
        height: parent.height

        onClicked: {
            squareClicked()
        }

        Image {
            id: imageId
            anchors.centerIn: parent
            width: parent.width * 3/5
            height: parent.height * 3/5
            source: getImage(playerSign)
            onSourceChanged: {
                scaleAnimationId.start()
                rotationAnimationId.start()
            }

            function getImage(number) {
                switch (number) {
                case 0:
                    return "";
                case 1:
                    return "images/circle.png";
                case 2:
                    return "images/cross.png";
                }
            }
        }

        ScaleAnimator {
            id: scaleAnimationId
            target: imageId
            from: 0.2
            to: 1.4
            easing.type: Easing.OutQuart
            duration: 1000
            onStopped: scaleAnimationId2.start()
            onStarted: rotationAnimationId.start()
        }

        ScaleAnimator {
            id: scaleAnimationId2
            target: imageId
            from: 1.4
            to: 1
            easing.type: Easing.InQuart
            duration: 500
        }

        RotationAnimator {
            id:rotationAnimationId
            target: imageId;
            from: 0;
            to: 1080;
            easing.type: Easing.OutQuart
            duration: 1500
        }
    }
}

