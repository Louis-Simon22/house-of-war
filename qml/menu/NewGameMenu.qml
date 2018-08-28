import QtQuick 2.11
import QtQuick.Layouts 1.1
import gamemanager 1.0
import "components/"

BaseMenu {
    id: newGameScene

    property GameManager gameManager

    signal newGameCreated

    Rectangle {
        anchors.fill: newGameScene
        color: "#49a349"
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        MenuNumberInput {
            id: worldWidth
            label: "World Width"
            input: "1500"
        }
        MenuNumberInput {
            id: worldHeight
            label: "World Height"
            input: "1000"
        }
        MenuNumberInput {
            id: originPointsCount
            label: "Origin Points Count"
            input: "25"
        }
        MenuButton {
            text: "Generate"
            onClicked: {
                newGameScene.gameManager.startNewGame(parseInt(worldWidth.input), parseInt(worldHeight.input), parseInt(originPointsCount.input))
                newGameScene.newGameCreated()
            }
        }
    }

    MenuButton {
        text: "Back"
        anchors.right: newGameScene.right
        anchors.rightMargin: 10
        anchors.top: newGameScene.top
        anchors.topMargin: 10
        onClicked: back()
    }
}
