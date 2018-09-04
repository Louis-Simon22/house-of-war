import QtQuick 2.11
import gamemanager 1.0
import worldmodel 1.0
import "map/"

Item {
    id: gameView

    property GameManager gameManager

    signal instantiateWorld

    onInstantiateWorld: {
        gameManager.instantiateWorld();
        state = "map";
    }

    Loader {
        id: mapSceneLoader
        anchors.fill: parent
        active: false
        sourceComponent: MapView {
            id: mapView
        }
    }

    Text {
        id: loadingView
        anchors.centerIn: parent
        color: "black"
        text: "Loading..."
        opacity: 0
    }

    state: "loading"

    states: [
        State {
            name: "loading"
            PropertyChanges {
                target: loadingView
                opacity: 1
            }
        },
        State {
            name: "map"
            PropertyChanges {
                target: mapSceneLoader
                active: true
            }
        }
    ]
}
