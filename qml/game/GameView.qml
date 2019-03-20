import QtQuick 2.11
import com.louissimonmcnicoll.how.ui.gamedatamanager 1.0
import "map/"

Item {
    id: gameView

    property GameDataManager gameDataManager

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
            item.gameDataManager = gameDataManager;
            item.instantiateMap();
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
