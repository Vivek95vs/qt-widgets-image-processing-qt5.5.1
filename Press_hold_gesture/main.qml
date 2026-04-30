import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true

    Rectangle
    {
        width: 500;height: 200;color: "red"

        Text
        {
            anchors.centerIn: parent
            text: "press and hold me"; font.pixelSize: 48

            property bool isActive: false
            color: isActive? "green" : "black"

            MouseArea{
                anchors.fill: parent
                onPressAndHold: parent.isActive = !parent.isActive
            }
        }
    }
}

