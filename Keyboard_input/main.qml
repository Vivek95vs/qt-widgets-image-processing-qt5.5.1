import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    width:600
    height: 600

    Rectangle
    {
        width: 400;
        height: 200;
        color: "lightblue"

        Rectangle
        {
            id:leftRect
            anchors
            {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 25
            }

            width: 150;height: 150
            color: activeFocus ? "red" : "darkred"
            KeyNavigation.right: rightRect
            focus: true

        }
        Rectangle
        {
            id:rightRect
            anchors
            {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 25
            }

            width: 150;height: 150
            color: activeFocus ? "green" : "darkgreen"
            KeyNavigation.left: leftRect
//            focus: true

        }

//        TextInput
//        {
//            anchors.left: parent.left;y: 16
//            anchors.right: parent.right
//            text: "Field 1"; font.pixelSize: 16
//            color: activeFocus ? "black" : "grey"
//            focus: true
//            activeFocusOnTab: true
//        }
//        TextInput
//        {
//            anchors.left: parent.left;y: 32
//            anchors.right: parent.right
//            text: "Field 2"; font.pixelSize: 16
//            color: activeFocus ? "black" : "grey"
//            focus: true
//            activeFocusOnTab: true
//        }
//        TextInput
//        {
//            anchors.left: parent.left;y: 48
//            anchors.right: parent.right
//            text: "Field 3"; font.pixelSize: 16
//            color: activeFocus ? "black" : "grey"
//            focus: true
//            activeFocusOnTab: true
//        }

    }
}

