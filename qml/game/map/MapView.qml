import QtQuick 2.11
import QtQml.Models 2.11

import com.louissimonmcnicoll.how.ui.gamedatamanager 1.0

Item {
    id: mapView

    property GameDataManager gameDataManager

    signal instantiateMap

    onInstantiateMap: {
        mapItemLoader.active = true
        mapOverlayLoader.active = true
    }

    Loader {
        id: mapItemLoader
        anchors.fill: parent
        active: false
        sourceComponent: MapItem {
            id: mapItem
        }
        onLoaded: {
            item.worldData = gameDataManager.worldData
            item.characterData = gameDataManager.characterData
            item.charactersController = gameDataManager.charactersController
        }
    }

    Loader {
        id: mapOverlayLoader
        anchors.fill: parent
        active: false
        sourceComponent: MapOverlay {
            id: mapOverlay
        }
        onLoaded: {
            item.worldData = gameDataManager.worldData
            item.characterData = gameDataManager.characterData
        }
    }
}
