import QtQuick 2.11

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0

import "map/"

Item {
    id: gameView

    property ModelController modelController

    signal instantiateGame

    onInstantiateGame: {
        gameView.state = "map"
    }
    focus: true
    Keys.onPressed: {
        if (gameView.state === "map" && !event.isAutoRepeat) {
            event.accepted = false
            if (event.modifiers & Qt.ControlModifier) {
                if (event.key === Qt.Key_S) {
                    modelController.saveToFile()
                    event.accepted = true
                }
            } else if (event.key === Qt.Key_Space) {
                modelController.iterationTimerManager.toggleIterations()
                event.accepted = true
            }
        }
    }

    Text {
        id: loadingView
        anchors.centerIn: parent
        visible: false
        color: "black"
        text: "Loading..."
    }

    Loader {
        id: mapItemLoader
        anchors.fill: parent

        active: false
        sourceComponent: MapItem {
            id: mapItem
        }
        onLoaded: {
            item.modelController = gameView.modelController
            item.loadMap()
        }
    }

    state: "loading"

    states: [
        State {
            name: "loading"
            PropertyChanges {
                target: loadingView
                visible: true
            }
        },
        State {
            name: "map"
            PropertyChanges {
                target: mapItemLoader
                active: true
            }
        }
    ]
}
