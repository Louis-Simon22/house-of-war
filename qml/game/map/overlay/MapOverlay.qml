import QtQuick 2.0
import QtQuick.Controls 2.5

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0
import com.louissimonmcnicoll.how.ui.entitiescontroller 1.0
import com.louissimonmcnicoll.how.ui.tilescontroller 1.0
import com.louissimonmcnicoll.how.ui.tiledisplaystatus 1.0

import "../../../components"

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
        id: tileDisplayStatusPanel
        height: 100
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: childrenRect.width

        Row {
            MenuButton {
                text: qsTr("Altitude")
                onClicked: tilesController.tileDisplayStatus
                           = TileDisplayStatusWrapper.TILE_DISPLAY_STATUS_ALTITUDE
            }

            MenuButton {
                text: qsTr("Resources")
                onClicked: tilesController.tileDisplayStatus
                           = TileDisplayStatusWrapper.TILE_DISPLAY_STATUS_RESOURCES
            }

            MenuButton {
                text: qsTr("Owner")
                onClicked: tilesController.tileDisplayStatus
                           = TileDisplayStatusWrapper.TILE_DISPLAY_STATUS_OWNER
            }
        }
    }

    Item {
        id: editPanel
        width: 100
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height * 0.3

        ButtonGroup {
            buttons: editPanelButtonsColumn.children
        }

        Column {
            id: editPanelButtonsColumn
            anchors.fill: parent

            MenuButton {
                anchors.left: parent.left
                anchors.right: parent.right
                checked:true
                text: qsTr("Plain")
                onClicked: console.log("greg1")
            }

            MenuButton {
                anchors.left: parent.left
                anchors.right: parent.right
                text: qsTr("Forest")
                onClicked: console.log("greg2")
            }

            MenuButton {
                anchors.left: parent.left
                anchors.right: parent.right
                text: qsTr("Mountain")
                onClicked: console.log("greg3")
            }
        }
    }
}
