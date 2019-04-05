import QtQuick 2.11
import com.louissimonmcnicoll.how.ui.gamedatamanager 1.0
import "map/"

Item {
    id: gameView

    property GameDataManager gameDataManager

    signal instantiateGame

    onInstantiateGame: {
        mapViewLoader.active = true;
    }

    Loader {
        id: mapViewLoader
        anchors.fill: parent
        active: false
        visible: false
        sourceComponent: MapView {
            id: mapView
        }
        onLoaded: {
            item.gameDataManager = gameDataManager;
            item.instantiateMap();
            gameView.state = "map";
        }
    }

    Text {
        id: loadingView
        anchors.centerIn: parent
        visible: false
        color: "black"
        text: "Loading..."
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
                visible: true
            }
        }
    ]
}
