import QtQuick 2.11

import "components/"

BaseMenu {
    id: loadScene

    Text {
        text: "Load Game Menu"
        color: "blue"

        anchors.centerIn: parent
    }

    MenuButton {
        text: "Back"
        anchors.right: loadScene.right
        anchors.rightMargin: 10
        anchors.top: loadScene.top
        anchors.topMargin: 10
        onClicked: back()
    }
}
