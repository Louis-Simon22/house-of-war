import QtQuick 2.11
import QtQml.Models 2.11

import com.louissimonmcnicoll.how.ui.graphentitymanager 1.0
import com.louissimonmcnicoll.how.ui.characterscontroller 1.0
import com.louissimonmcnicoll.how.ui.worldmanager 1.0

Item {
    id: mapView

    property WorldManager worldManager
    property GraphEntityManager graphEntityManager
    property CharactersController charactersController

    MapItem {
        id: mapItem
        anchors.fill: parent

        worldManager: modelManager.worldManager
        graphEntityManager: modelManager.graphEntityManager
        charactersController: modelManager.charactersController
    }

    MapOverlay {
        id: mapOverlay
        anchors.fill: parent

        worldManager: modelManager.worldManager
        graphEntityManager: modelManager.graphEntityManager
    }
}
