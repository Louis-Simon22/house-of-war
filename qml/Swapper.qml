import QtQuick 2.11

import com.louissimonmcnicoll.how.ui.maincontroller 1.0

import "game/"
import "menu/"

Item {
    id: swapper
    focus: true

    MainController {
        id: mainController
    }

    Loader {
        id: menuLoader
        anchors.fill: parent
        active: false
        sourceComponent: ParentMenu {
            id: parentMenu
        }
        onLoaded: {
            item.mainController = mainController
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
            item.mainController = mainController
            item.instantiateGame()
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            swapper.state = "menu"
            event.accepted = true
        }
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
        },
        State {
            name: "inGameMenu"
            PropertyChanges {
                target: menuLoader
                active: true
            }
            PropertyChanges {
                target: gameLoader
                active: true
            }
        }
    ]
}
