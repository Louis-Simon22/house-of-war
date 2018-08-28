import QtQuick 2.11
import gamemanager 1.0
import worldmodel 1.0
import "map/"

Item {
    id: gameView

    property GameManager gameManager

    Loader {
        id: mapSceneLoader
        anchors.fill: parent
        active: false
    }

    Text {
        id: loadingView
        anchors.centerIn: parent
        color: "white"
        text: "Loading..."
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
            StateChangeScript {
                name: "Load map"
                script: {
                    mapSceneLoader.setSource("MapScene.qml", { gameManager: gameView.gameManager })
                }
            }
        }
    ]
}
