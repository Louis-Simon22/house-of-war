import QtQuick 2.11

import com.louissimonmcnicoll.how.ui.modelmanager 1.0

Item {
    id: parentMenu

    signal startGame

    property ModelManager modelManager

    MainMenu {
        id: mainMenu
        anchors.fill: parent

        onNewGamePressed: parentMenu.state = "new"
        onLoadGamePressed: parentMenu.state = "load"
        onCreditsPressed: parentMenu.state = "credits"
        onBack: {
            Qt.quit()
        }
    }

    GenerateMenu {
        id: generateMenu
        anchors.fill: parent

        modelManager: parentMenu.modelManager
        onNewGameGenerated: {
            parentMenu.startGame()
        }
        onBack: parentMenu.state = "main"
    }

    LoadMenu {
        id: loadGameMenu
        anchors.fill: parent

        onBack: parentMenu.state = "main"
    }

    CreditsMenu {
        id: creditsMenu
        anchors.fill: parent

        onBack: parentMenu.state = "main"
    }

    state: "main"

    states: [
        State {
            name: "main"
            PropertyChanges {
                target: mainMenu
                opacity: 1
            }
        },
        State {
            name: "new"
            PropertyChanges {
                target: generateMenu
                opacity: 1
            }
        },
        State {
            name: "load"
            PropertyChanges {
                target: loadGameMenu
                opacity: 1
            }
        },
        State {
            name: "credits"
            PropertyChanges {
                target: creditsMenu
                opacity: 1
            }
        }
    ]
}
