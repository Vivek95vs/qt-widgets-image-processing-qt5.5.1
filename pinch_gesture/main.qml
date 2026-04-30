import QtQuick 2.3
import QtQuick.Window 2.2

//Window {
//    visible: true

    Flickable
    {
        id:flick
        width: 400;height: 400
        contentWidth: 2000
        contentHeight: 2000

        PinchArea
        {
            anchors.fill:parent
            pinch.target: flickimg
            pinch.maximumScale: 1.0
            pinch.minimumScale: 0.1
            pinch.dragAxis: Pinch.XAndYAxis

        }

        Image
        {
            id:flickimg
            width: flick.contentWidth
            height: flick.contentHeight
            source: "../icons/icons/Logo PNG.PNG"
        }
    }
//}

