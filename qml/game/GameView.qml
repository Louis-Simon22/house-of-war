import QtQuick 2.11

import com.louissimonmcnicoll.how.ui.maincontroller 1.0

import "map/"

Item {
    id: gameView

    property MainController mainController

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
        sourceComponent: MapItem {
            id: mapView
        }
        onLoaded: {
            item.mainController = mainController
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
