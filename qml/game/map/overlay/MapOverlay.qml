import QtQuick 2.0

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0

Item {
    id: mapOverlay
    width: parent.width * 0.4
    height: 100
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom

    property ModelController modelController

    Rectangle {
        anchors.fill: parent
        color: "orange"
    }

    TileDetails {
        id: tileDetails
        tileBindings: mapOverlay.modelController.entitiesController.tileBindings
    }

    ArmyDetails {
        id: armyDetails
        armyBindings: mapOverlay.modelController.entitiesController.armyBindings
    }
}
