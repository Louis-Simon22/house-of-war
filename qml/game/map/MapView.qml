import QtQuick 2.11
import QtQml.Models 2.11
import com.louissimonmcnicoll.how.bind.gamemanager 1.0

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
        }
    }
}
