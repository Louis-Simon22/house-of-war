import QtQuick 2.12
import QtQuick.Shapes 1.12
import QtQml 2.12

import com.louissimonmcnicoll.how.ui.worlddata 1.0
import com.louissimonmcnicoll.how.ui.characterdata 1.0
import com.louissimonmcnicoll.how.ui.characterscontroller 1.0
import com.louissimonmcnicoll.how.ui.voronoicellsmodel 1.0
import com.louissimonmcnicoll.how.ui.segmentspainter 1.0
import com.louissimonmcnicoll.how.ui.cellspainter 1.0

Flickable {
    id: mapItemFlickable
    contentWidth: mapItem.width * mapItem.scale
    contentHeight: mapItem.height * mapItem.scale
    boundsBehavior: Flickable.DragAndOvershootBounds
    clip: true

    property WorldData worldData
    property CharacterData characterData
    property CharactersController charactersController

    Item {
        id: mapItem
        x: worldData.worldBounds.x
        y: worldData.worldBounds.y
        width: worldData.worldBounds.width
        height: worldData.worldBounds.height
        property real scale: 3
        transform: Scale {
            xScale: mapItem.scale
            yScale: mapItem.scale
        }

        MouseArea {
            anchors.fill: mapItem

            acceptedButtons: Qt.NoButton
            onWheel: {
                if (wheel.angleDelta.y > 0) {
                    mapItem.scale += 0.1
                } else {
                    mapItem.scale -= 0.1
                }
                wheel.accepted = true
            }
        }

        Rectangle {
            id: voronoiCells
            anchors.fill: parent

            border.color: "transparent" //voronoiCells.selectedVoronoiCellIndex === index ? "red" : "black"
            color: "transparent"

            property int selectedVoronoiCellIndex: -1

            MouseArea {
                anchors.fill: parent

                acceptedButtons: Qt.RightButton
                propagateComposedEvents: false
                onClicked: {
                    if (characters.selectedCharacterIndex >= 0) {
                        voronoiCells.selectedVoronoiCellIndex = worldData.cellDescAtPosition(
                                    mouseX, mouseY)
                        charactersController.addMoveOrder(
                                    characters.selectedCharacterIndex,
                                    voronoiCells.selectedVoronoiCellIndex)
                    }
                }
            }

            Repeater {
                model: worldData.voronoiCellsModel

                delegate: CellsPainter {
                    x: rollEnvelope.x
                    y: rollEnvelope.y
                    width: rollEnvelope.width
                    height: rollEnvelope.height

                    worldData: mapItemFlickable.worldData
                    cellIndex: index
                }
            }
        }

        SegmentsPainter {
            anchors.fill: mapItem
            showVoronoiSegments: true
            showDelaunaySegments: false

            worldData: mapItemFlickable.worldData
        }

        Repeater {
            id: characters
            model: characterData.charactersModel

            property int selectedCharacterIndex: -1

            delegate: Rectangle {
                id: characterEnvelope
                x: posX - width / 2
                y: posY - height / 2
                width: 7
                height: 7

                color: characters.selectedCharacterIndex === index ? "red" : "black"

                MouseArea {
                    anchors.fill: parent

                    acceptedButtons: Qt.LeftButton
                    propagateComposedEvents: false
                    onClicked: {
                        mouse.accepted = true
                        characters.selectedCharacterIndex = index
                    }
                }

                Text {
                    id: characterLabel
                    x: characterEnvelope.width / 2 - paintedWidth / 2
                    y: characterEnvelope.height / 2 - paintedHeight / 2
                    color: "white"
                    text: index
                }
            }
        }
    }
}
