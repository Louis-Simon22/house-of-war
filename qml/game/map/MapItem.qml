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
            anchors.fill: mapItem

            border.color: "black"
            color: "transparent"
        }

        SegmentsPainter {
            anchors.fill: mapItem
            showVoronoiSegments: true
            showDelaunaySegments: false

            worldData: mapItemFlickable.worldData
        }

        Repeater {
            id: voronoiCells
            model: worldData.voronoiCellsModel

            // Position of the voronoi cell click event so it can be propagated to children
            property var propagatedMouseX: null
            property var propagatedMouseY: null
            // Selected voronoi cell
            property int selectedVoronoiCellIndex: -1

            delegate: CellsPainter {
                x: rollEnvelope.x
                y: rollEnvelope.y
                width: rollEnvelope.width
                height: rollEnvelope.height

                worldData: mapItemFlickable.worldData
                cellIndex: index

                Rectangle {
                    id: cellEnvelope
                    anchors.fill: parent

                    border.color: "transparent" //voronoiCells.selectedVoronoiCellIndex === index ? "red" : "black"
                    color: "transparent"

                    MouseArea {
                        anchors.fill: parent

                        acceptedButtons: Qt.RightButton
                        propagateComposedEvents: true
                        onClicked: {
                            if (!voronoiCells.propagatedMouseX
                                    && !voronoiCells.propagatedMouseY) {
                                voronoiCells.propagatedMouseX = mouseX + rollEnvelope.x
                                voronoiCells.propagatedMouseY = mouseY + rollEnvelope.y
                            }
                            if (worldData.isPointWithinVoronoiCell(
                                        index, voronoiCells.propagatedMouseX,
                                        voronoiCells.propagatedMouseY)) {
                                mouse.accepted = true
                                voronoiCells.selectedVoronoiCellIndex = index
                                voronoiCells.propagatedMouseX = null
                                voronoiCells.propagatedMouseY = null
                                charactersController.addMoveOrder(
                                            characters.selectedCharacterIndex,
                                            voronoiCells.selectedVoronoiCellIndex)
                            } else {
                                mouse.accepted = false
                            }
                        }
                    }

                    Text {
                        id: voronoiCellLabel
                        x: cellEnvelope.width / 2 - paintedWidth / 2
                        y: cellEnvelope.height / 2 - paintedHeight / 2
                        font.pixelSize: 7
                        text: index
                    }
                }
            }
        }

        Repeater {
            id: characters
            model: characterData.charactersModel

            property int selectedCharacterIndex: -1

            delegate: Rectangle {
                id: characterEnvelope
                x: posX - width / 2
                y: posY - height / 2
                width: 20
                height: 20

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
