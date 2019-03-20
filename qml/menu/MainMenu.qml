import QtQuick 2.11

import com.louissimonmcnicoll.how.ui.gamedatamanager 1.0

Item {
    id: mainMenu

    signal startGame

    property GameDataManager gameDataManager

    IntroMenu {
        id: introMenu
        anchors.fill: parent
        onNewGamePressed: mainMenu.state = "new"
        onLoadGamePressed: mainMenu.state = "load"
        onCreditsPressed: mainMenu.state = "credits"
        onBack: {
            Qt.quit()
        }
    }

    GenerateMenu {
        id: generateMenu
        anchors.fill: parent
        gameDataManager: mainMenu.gameDataManager
        onNewGameGenerated: {
            mainMenu.startGame();
        }
        onBack: mainMenu.state = "intro"
    }

    LoadMenu {
        id: loadGameMenu
        anchors.fill: parent
        onBack: mainMenu.state = "intro"
    }

    CreditsMenu {
        id: creditsMenu
        anchors.fill: parent
        onBack: mainMenu.state = "intro"
    }

    state: "intro"

    states: [
        State {
            name: "intro"
            PropertyChanges {
                target: introMenu
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
