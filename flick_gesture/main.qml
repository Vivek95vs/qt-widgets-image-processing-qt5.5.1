import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true

    Flickable
    {
        id:flick
        width: 400;height: 400
        contentWidth: 1000
        contentHeight: 1000

        Image
        {
            width: flick.contentWidth
            height: flick.contentHeight
            source: "../icons/icons/Logo PNG.PNG"
        }

    }
}

