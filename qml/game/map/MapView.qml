import QtQuick 2.11
import gamemanager 1.0
import worldmodel 1.0
import QtQml.Models 2.11

Item {
    id: mapView

    property GameManager gameManager

    signal instantiateMap

    onInstantiateMap: {
        mapLoader.active = true
    }

    Loader {
        id: mapLoader
        anchors.fill: parent
        active: false
        sourceComponent: MapItem {
            id: mapItem
        }
        onLoaded: {
            item.gameManager = gameManager;
            item.instantiateMap();
        }
    }
}
