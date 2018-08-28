import QtQuick 2.11
import gamemanager 1.0

Item {
    id: mainMenu

    property GameManager gameManager

    signal startGame

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

    NewGameMenu {
        id: newGameMenu
        anchors.fill: parent
        gameManager: mainMenu.gameManager
        onNewGameCreated: {
            mainMenu.startGame()
        }
        onBack: mainMenu.state = "intro"
    }

    LoadGameMenu {
        id: loadGameMenu
        anchors.fill: parent
        gameManager: gameManager
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
                target: newGameMenu
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
