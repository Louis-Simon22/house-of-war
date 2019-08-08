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
        if (gameView.state === "map") {
            event.accepted = true
            if (event.modifiers & Qt.ControlModifier) {
                switch (event.key) {
                case Qt.Key_S:
                    modelController.saveToFile()
                    break
                }
            } else {
                switch (event.key) {
                case Qt.Key_Space:
                    modelController.iterationTimerManager.toggleIterations()
                    break
                }
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
