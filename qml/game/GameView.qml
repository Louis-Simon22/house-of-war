import QtQuick 2.11

import com.louissimonmcnicoll.how.ui.modelmanager 1.0

import "map/"

Item {
    id: gameView

    property ModelManager modelManager

    signal instantiateGame

    onInstantiateGame: {
        gameView.state = "map"
    }

    Text {
        id: loadingView
        anchors.centerIn: parent
        visible: false
        color: "black"
        text: "Loading..."
    }

    Loader {
        id: mapViewLoader
        anchors.fill: parent

        active: false
        sourceComponent: MapView {
            id: mapView
        }
        onLoaded: {
            item.worldManager = modelManager.worldManager
            item.graphEntityManager = modelManager.graphEntityManager
            item.charactersController = modelManager.charactersController
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
                target: mapViewLoader
                active: true
            }
        }
    ]
}
