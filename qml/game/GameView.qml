import QtQuick 2.11
import com.louissimonmcnicoll.how.bind.gamemanager 1.0
import "map/"

Item {
    id: gameView

    property GameManager gameManager

    signal instantiateGame

    onInstantiateGame: {
        state = "map"
    }

    Loader {
        id: mapSceneLoader
        anchors.fill: parent
        active: false
        sourceComponent: MapView {
            id: mapView
        }
        onLoaded: {
            item.gameManager = gameManager
            item.instantiateMap()
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
