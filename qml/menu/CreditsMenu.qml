import QtQuick 2.11
import "components/"

BaseMenu {
    id: creditsScene

    Rectangle {
        anchors.fill: parent
        color: "#49a349"
    }

    MenuButton {
        text: "Back"
        anchors.right: creditsScene.right
        anchors.rightMargin: 10
        anchors.top: creditsScene.top
        anchors.topMargin: 10
        onClicked: back()
    }

    Text {
        text: "Credits"
        color: "white"
        anchors.centerIn: parent
    }
}
