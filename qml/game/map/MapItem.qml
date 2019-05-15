import QtQuick 2.12
import QtQuick.Shapes 1.12
import QtQml 2.12

import com.louissimonmcnicoll.how.ui.maincontroller 1.0
import com.louissimonmcnicoll.how.ui.entitycontroller 1.0

Flickable {
    id: mapItemFlickable
    contentWidth: mapItem.width * mapItem.scale
    contentHeight: mapItem.height * mapItem.scale
    boundsBehavior: Flickable.DragAndOvershootBounds
    clip: true

    property MainController mainController

    signal loadMap
    onLoadMap: {
        mapItemFlickable.mainController.instantiateUiElements(mapItem)
    }

    Item {
        id: mapItem
        x: mapItemFlickable.mainController.worldController.worldBounds.x
        y: mapItemFlickable.mainController.worldController.worldBounds.y
        width: mapItemFlickable.mainController.worldController.worldBounds.width
        height: mapItemFlickable.mainController.worldController.worldBounds.height
        property real minScale: Math.max(
                                    mapItemFlickable.width / mapItem.width,
                                    mapItemFlickable.height / mapItem.height)
        property real scale: 3
        transform: Scale {
            xScale: mapItem.scale
            yScale: mapItem.scale
        }

        // TODO initial zoom and on window resize
        MouseArea {
            anchors.fill: parent

            acceptedButtons: Qt.NoButton
            propagateComposedEvents: false
            onWheel: {
                mapItem.scale = Math.max(
                            mapItem.minScale,
                            mapItem.scale + (wheel.angleDelta.y > 0 ? 0.1 : -0.1))
                wheel.accepted = true
            }
        }
    }
}
