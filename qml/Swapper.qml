import QtQuick.Window 2.2
import QtQuick 2.11

import gamemanager 1.0
import "game/"
import "menu/"

Item {
    id: swapper
    x: 0
    y: 0
    width: 920
    height: 680

    GameManager {
        id: gameManager
    }

    Loader {
        id: menuLoader
        anchors.fill: parent
        active: false
        sourceComponent: MainMenu {
            id: mainMenu
        }
        onLoaded: {
            item.gameManager = gameManager
        }
    }

    Connections {
        target: menuLoader.item
        onStartGame: swapper.state = "game"
    }

    Loader {
        id: gameLoader
        anchors.fill: parent
        active: false
        sourceComponent: GameView {
            id: gameView
        }
        onLoaded: {
            item.gameManager = gameManager;
            item.instantiateGame();
        }
    }

    Connections {
        target: gameLoader.item
    }

    state: "menu"

    states: [
        State {
            name: "menu"
            PropertyChanges {
                target: menuLoader
                active: true
            }
            PropertyChanges {
                target: gameLoader
                active: false
            }
        },
        State {
            name: "game"
            PropertyChanges {
                target: menuLoader
                active: false
            }
            PropertyChanges {
                target: gameLoader
                active: true
            }
        }
    ]
}
