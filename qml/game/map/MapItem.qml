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
                        selectionRect.x = Math.min(
                                    mapItemMouseArea.initialMousePosition.x,
                                    mouse.x)
                        selectionRect.y = Math.min(
                                    mapItemMouseArea.initialMousePosition.y,
                                    mouse.y)
                        selectionRect.width = Math.max(
                                    mapItemMouseArea.initialMousePosition.x,
                                    mouse.x) - selectionRect.x
                        selectionRect.height = Math.max(
                                    mapItemMouseArea.initialMousePosition.y,
                                    mouse.y) - selectionRect.y
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
                    if (selectionRect.visible) {
                        modelController.entitiesBoxEvent(
                                    selectionRect.x, selectionRect.y,
                                    selectionRect.x + selectionRect.width,
                                    selectionRect.y + selectionRect.height,
                                    mouse.buttons, mouse.modifiers)
                    } else {
                        modelController.entitiesClickEvent(
                                    mapItemMouseArea.initialMousePosition.x,
                                    mapItemMouseArea.initialMousePosition.y,
                                    mouse.button, mouse.modifiers)
                    }
                }
                selectionRect.width = 0
                mouse.accepted = true
            }
            onWheel: {
                mapItem.scale = Math.max(
                            mapItem.minScale,
                            mapItem.scale * (wheel.angleDelta.y > 0 ? 1.05 : 0.95))
                wheel.accepted = true
            }
        }

        Rectangle {
            id: selectionRect
            z: modelController.UI_LAYER

            visible: width > 5 && height > 5
            border.color: "red"
            border.width: 3
            color: "transparent"
        }
    }

    MapOverlay {
        id: mapOverlay
        anchors.fill: parent
        modelController: mapContainer.modelController
    }
}
