import QtQuick 2.0
import QtQuick.Controls 2.5

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0
import com.louissimonmcnicoll.how.ui.entitiescontroller 1.0
import com.louissimonmcnicoll.how.ui.tilescontroller 1.0
import com.louissimonmcnicoll.how.ui.tiledisplaystatuswrapper 1.0

Item {
    id: mapOverlay

    property ModelController modelController
    property EntitiesController entitiesController: modelController.entitiesController
    property TilesController tilesController: entitiesController.tilesController

    Item {
        id: entityPanel
        width: mapOverlay.width * 0.4
        height: 100
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Rectangle {
            anchors.fill: parent
            color: "orange"
        }

        TileDetails {
            id: tileDetails
            anchors.fill: parent

            tileBindings: entitiesController.tileBindings
        }

        ArmyDetails {
            id: armyDetails
            anchors.fill: parent

            armyBindings: entitiesController.armyBindings
        }
    }

    Item {
        id: tilesControlPanel
        height: 100
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: childrenRect.width

        Row {
            id: buttonRow

            Button {
                text: qsTr("Altitude")
                onClicked: {
                    var greg = TileDisplayStatusWrapper.TILE_DISPLAY_STATUS_ALTITUDE
                    tilesController.tileDisplayStatus = greg
                }
            }

            Button {
                text: qsTr("Resources")
                onClicked: tilesController.tileDisplayStatus
                           = TileDisplayStatusWrapper.TILE_DISPLAY_STATUS_RESOURCES
            }

            Button {
                text: qsTr("Owner")
                onClicked: tilesController.tileDisplayStatus
                           = TileDisplayStatusWrapper.TILE_DISPLAY_STATUS_OWNER
            }
        }
    }
}
