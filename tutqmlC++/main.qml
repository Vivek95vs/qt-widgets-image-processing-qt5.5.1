import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 400
    height: 300
    title: "PushButton Example"

    Button {
        id: pushButton
        text: "Click Me!"
        anchors.centerIn: parent
        onClicked: mycontrol.buttonClicked()
    }
}

