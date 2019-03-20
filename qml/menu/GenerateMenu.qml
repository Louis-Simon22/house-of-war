import QtQuick 2.11
import QtQuick.Layouts 1.1

import com.louissimonmcnicoll.how.ui.gamedatamanager 1.0
import "components/"

BaseMenu {
    id: generateMenu

    property GameDataManager gameDataManager

    signal newGameGenerated

    Rectangle {
        anchors.fill: generateMenu
        color: "#49a349"
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        MenuButton {
            text: "Generate"
            onClicked: {
                generateMenu.gameDataManager.newGameGenerated.connect(generateMenu.newGameGenerated);
                generateMenu.gameDataManager.newGame(
                    parseInt(worldWidth.input, 10),
                    parseInt(worldHeight.input, 10));
                generateMenu.gameDataManager.newGameGenerated.disconnect(generateMenu.newGameGenerated);
            }
        }
        MenuNumberInput {
            id: worldWidth
            label: "World Width"
            input: "500"
        }
        MenuNumberInput {
            id: worldHeight
            label: "World Height"
            input: "300"
        }
    }

    MenuButton {
        text: "Back"
        anchors.right: generateMenu.right
        anchors.rightMargin: 10
        anchors.top: generateMenu.top
        anchors.topMargin: 10
        onClicked: back()
    }
}
