import QtQuick 2.11
import QtQuick.Controls 2.4

Canvas {
    anchors.fill: parent
    property int startX: 0
    property int startY: 0
    property int stopX: 0
    property int stopY: 0
    property bool endLineVisible: false

    onPaint: {
        if(endLineVisible)
            drawLine()
        else
            clear()
    }

    function drawLine() {
        var ctx = getContext('2d')
        ctx.lineWidth = 5
        ctx.strokeStyle = "black"
        ctx.beginPath()
        ctx.moveTo(startX, startY)
        ctx.lineTo(stopX, stopY)
        ctx.stroke()
    }

    function clear() {
        var ctx = getContext('2d')
        ctx.reset()
        ctx.stroke()
    }
}
