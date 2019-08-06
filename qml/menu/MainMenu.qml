import QtQuick 2.11

import "../components"

BaseMenu {
    id: menuScene

    signal playPressed
    signal editorPressed
    signal creditsPressed

    Rectangle {
        anchors.fill: parent.gameWindowAnchorItem
        color: "#47688e"
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 30
        font.pixelSize: 30
        text: "Main Menu"
    }

    Column {
        anchors.centerIn: parent
        spacing: 10
        MenuButton {
            text: "Play"
            onClicked: playPressed()
        }
        MenuButton {
            text: "Editor"
            onClicked: editorPressed()
        }
        MenuButton {
            text: "Credits"
            onClicked: creditsPressed()
        }
        MenuButton {
            text: "Quit"
            onClicked: back()
        }
    }
}
