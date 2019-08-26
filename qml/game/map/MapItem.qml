import QtQuick 2.12

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0

import "./overlay"

Item {
    id: mapContainer
    clip: true

    property ModelController modelController

    signal loadMap
    onLoadMap: {
        modelController.entitiesController.generateMapItems(mapItem)
    }

    Item {
        id: mapItem
        x: 0
        y: 0
        width: modelController.worldBounds.width
        height: modelController.worldBounds.height
        property real minScale: Math.max(mapContainer.width / width,
                                         mapContainer.height / height)
        property real scale: minScale
        transform: Scale {
            xScale: mapItem.scale
            yScale: mapItem.scale
        }

        MouseArea {
            id: mapItemMouseArea
            anchors.fill: parent

            acceptedButtons: Qt.AllButtons
            propagateComposedEvents: false
            preventStealing: true

            property point previousMousePosition
            property point initialMousePosition

            onPressed: {
                mapItemMouseArea.initialMousePosition = Qt.point(mouse.x,
                                                                 mouse.y)
                mapItemMouseArea.previousMousePosition = mapItemMouseArea.initialMousePosition
            }
            onPositionChanged: {
                if (containsMouse) {
                    if (mouse.buttons & Qt.MiddleButton) {
                        var deltaX = mouse.x - mapItemMouseArea.previousMousePosition.x
                        var deltaY = mouse.y - mapItemMouseArea.previousMousePosition.y
                        mapItem.x += deltaX * 1.25
                        mapItem.y += deltaY * 1.25
                    } else if (mouse.buttons & Qt.LeftButton) {
                        selectionRect.width = mouse.x - mapItemMouseArea.initialMousePosition.x
                        selectionRect.height = mouse.y - mapItemMouseArea.initialMousePosition.y
                        selectionRect.visible = true
                    } else {
                        modelController.entitiesSegmentEvent(
                                    mapItemMouseArea.previousMousePosition.x,
                                    mapItemMouseArea.previousMousePosition.y,
                                    mouse.x, mouse.y, mouse.buttons,
                                    mouse.modifiers)
                    }
                    mapItemMouseArea.previousMousePosition = Qt.point(mouse.x,
                                                                      mouse.y)
                }
            }
            onReleased: {
                if (containsMouse) {
                    modelController.entitiesBoxEvent(
                                mapItemMouseArea.initialMousePosition.x,
                                mapItemMouseArea.initialMousePosition.y,
                                mouse.x, mouse.y, mouse.buttons,
                                mouse.modifiers)
                }
                selectionRect.visible = false
                mouse.accepted = true
            }
            onClicked: {
                modelController.entitiesClickEvent(mouse.x, mouse.y,
                                                   mouse.button,
                                                   mouse.modifiers)
                mouse.accepted = true
            }
            onWheel: {
                mapItem.scale = Math.max(
                            mapItem.minScale,
                            mapItem.scale * (wheel.angleDelta.y > 0 ? 1.05 : 0.95))
                wheel.accepted = true
            }
        }
    }

    Rectangle {
        id: selectionRect
        x: mapItemMouseArea.initialMousePosition.x
        y: mapItemMouseArea.initialMousePosition.y

        visible: false
        border.color: "red"
        border.width: 3
    }

    MapOverlay {
        id: mapOverlay
        anchors.fill: parent
        modelController: mapContainer.modelController
    }
}
