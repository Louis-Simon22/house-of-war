import QtQuick 2.12
import QtQuick.Shapes 1.12
import QtQml 2.12

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0

import "./overlay"

Flickable {
    id: mapItemFlickable
    contentWidth: mapItem.width * mapItem.scale
    contentHeight: mapItem.height * mapItem.scale
    boundsBehavior: Flickable.DragAndOvershootBounds
    clip: true

    property ModelController modelController

    signal loadMap
    onLoadMap: {
        modelController.entitiesController.generateMapItems(mapItem)
    }

    Item {
        id: mapItem
        x: modelController.worldBounds.x
        y: modelController.worldBounds.y
        width: modelController.worldBounds.width
        height: modelController.worldBounds.height
        property real minScale: Math.max(
                                    mapItemFlickable.width / mapItem.width,
                                    mapItemFlickable.height / mapItem.height)
        property real scale: 3
        transform: Scale {
            xScale: mapItem.scale
            yScale: mapItem.scale
        }

        // TODO initial zoom and on window resize
//        MouseArea {
//            anchors.fill: parent

//            acceptedButtons: Qt.NoButton
//            propagateComposedEvents: false
//            onWheel: {
//                mapItem.scale = Math.max(
//                            mapItem.minScale,
//                            mapItem.scale * (wheel.angleDelta.y > 0 ? 1.05 : 0.95))
//                wheel.accepted = true
//            }
//        }
    }

//    MapOverlay {
//        id: mapOverlay
//        modelController: mapItemFlickable.modelController
//    }
}
