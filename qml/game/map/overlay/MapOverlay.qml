import QtQuick 2.0
import QtQuick.Controls 2.5

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0
import com.louissimonmcnicoll.how.ui.entitiescontroller 1.0
import com.louissimonmcnicoll.how.ui.tilescontroller 1.0
import com.louissimonmcnicoll.how.ui.terraintype 1.0
import com.louissimonmcnicoll.how.ui.controlmode 1.0
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
        id: editPanel
        width: 100
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height * 0.3
        visible: modelController.controlMode === ControlMode.EDIT

        Column {
            id: editPanelButtonsColumn
            anchors.fill: parent

            MenuButton {
                anchors.left: parent.left
                anchors.right: parent.right
                text: qsTr("Plain")
                checked: tilesController.terrainType === TerrainType.PLAIN
                onClicked: tilesController.terrainType = TerrainType.PLAIN
            }

            MenuButton {
                anchors.left: parent.left
                anchors.right: parent.right
                text: qsTr("Forest")
                checked: tilesController.terrainType === TerrainType.FOREST
                onClicked: tilesController.terrainType = TerrainType.FOREST
            }

            MenuButton {
                anchors.left: parent.left
                anchors.right: parent.right
                text: qsTr("Mountain")
                checked: tilesController.terrainType === TerrainType.MOUNTAIN
                onClicked: tilesController.terrainType = TerrainType.MOUNTAIN
            }
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
                text: qsTr("Terrain")
                checked: tilesController.tileDisplayStatus === TileDisplayStatus.TERRAIN
                onClicked: tilesController.tileDisplayStatus = TileDisplayStatus.TERRAIN
            }

            MenuButton {
                text: qsTr("Owner")
                checked: tilesController.tileDisplayStatus === TileDisplayStatus.OWNER
                onClicked: tilesController.tileDisplayStatus = TileDisplayStatus.OWNER
            }
        }
    }
}
