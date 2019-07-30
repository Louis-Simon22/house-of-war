import QtQuick 2.11

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0

import "game/"
import "menu/"
import "./components"

Item {
    id: swapper
    focus: true

    ModelController {
        id: modelController
    }

    Loader {
        id: menuLoader
        anchors.fill: parent
        active: false
        sourceComponent: ParentMenu {
            id: parentMenu
        }
        onLoaded: {
            item.modelController = modelController
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
            item.modelController = modelController
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
