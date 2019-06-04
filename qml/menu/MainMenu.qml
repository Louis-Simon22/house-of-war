import QtQuick 2.11

import "components/"

BaseMenu {
    id: menuScene

    signal newGamePressed
    signal loadGamePressed
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
            text: "New Game"
            onClicked: newGamePressed()
        }
        MenuButton {
            text: "Load Game"
            onClicked: loadGamePressed()
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
