import QtQuick 2.12
import QtQuick.Shapes 1.12
import QtQml 2.12

import com.louissimonmcnicoll.how.ui.worldmanager 1.0
import com.louissimonmcnicoll.how.ui.graphentitymanager 1.0
import com.louissimonmcnicoll.how.ui.characterscontroller 1.0
import com.louissimonmcnicoll.how.ui.voronoicellsmodel 1.0
import com.louissimonmcnicoll.how.ui.segmentspainter 1.0
import com.louissimonmcnicoll.how.ui.TilePainter 1.0

Flickable {
    id: mapItemFlickable
    contentWidth: mapItem.width * mapItem.scale
    contentHeight: mapItem.height * mapItem.scale
    boundsBehavior: Flickable.DragAndOvershootBounds
    clip: true

    property WorldManager worldManager
    property GraphEntityManager graphEntityManager
    property CharactersController charactersController

    MouseArea {
        anchors.fill: parent

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

    Item {
        id: mapItem
        x: worldManager.worldBounds.x
        y: worldManager.worldBounds.y
        width: worldManager.worldBounds.width
        height: worldManager.worldBounds.height
        property real scale: 3
        transform: Scale {
            xScale: mapItem.scale
            yScale: mapItem.scale
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
                        voronoiCells.selectedVoronoiCellIndex = worldManager.cellIndexAtPosition(
                                    mouseX, mouseY)
                        charactersController.addMoveOrder(
                                    characters.selectedCharacterIndex,
                                    voronoiCells.selectedVoronoiCellIndex)
                    }
                }
            }

            Repeater {
                model: worldManager.voronoiCellsModel

                delegate: TilePainter {
                    x: rollEnvelope.x
                    y: rollEnvelope.y
                    width: rollEnvelope.width
                    height: rollEnvelope.height

                    worldManager: mapItemFlickable.worldManager
                    cellIndex: index

                    Text {
                        id: cellLabel
                        x: rollEnvelope.width / 2 - paintedWidth / 2
                        y: rollEnvelope.height / 2 - paintedHeight / 2

                        font.pixelSize: 6
                        color: "white"
                        text: index
                    }
                }
            }
        }

        SegmentsPainter {
            anchors.fill: mapItem
            showVoronoiSegments: true
            showDelaunaySegments: false

            worldManager: mapItemFlickable.worldManager
        }

        Repeater {
            id: characters
            model: graphEntityManager.charactersModel

            property int selectedCharacterIndex: -1

            delegate: Rectangle {
                id: characterEnvelope
                x: posX - width / 2
                y: posY - height / 2
                width: 10
                height: 10

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

                    font.pixelSize: 8
                    color: "white"
                    text: index
                }
            }
        }
    }
}
