import QtQuick 2.12
import QtQuick.Shapes 1.12
import QtQml 2.12

import com.louissimonmcnicoll.how.ui.maincontroller 1.0
import com.louissimonmcnicoll.how.ui.entitycontroller 1.0
import com.louissimonmcnicoll.how.ui.worldmanager 1.0
import com.louissimonmcnicoll.how.ui.entitiesmodel 1.0

Flickable {
    id: mapItemFlickable
    contentWidth: mapItem.width * mapItem.scale
    contentHeight: mapItem.height * mapItem.scale
    boundsBehavior: Flickable.DragAndOvershootBounds
    clip: true

    property MainController mainController

    Item {
        id: mapItem
        x: mainController.worldManagerWrapper.worldBounds.x
        y: mainController.worldManagerWrapper.worldBounds.y
        width: mainController.worldManagerWrapper.worldBounds.width
        height: mainController.worldManagerWrapper.worldBounds.height
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

        Repeater {
            id: entities
            model: mainController.entitiesModel

            property int selectedCharacterIndex: -1

            delegate: MouseArea {
                id: envelope
                x: rolePosX
                y: rolePosY
                z: roleLayer
                width: roleWidth
                height: roleHeight

                // ignore "Enum value must be a string" warning
                acceptedButtons: roleAcceptedButtons
                propagateComposedEvents: false
                onClicked: {
                    mainController.entityController.onEntityWrapperClicked(
                                index, mouse.button)
                    mouse.accepted = true
                }

                Component.onCompleted: {
                    var entityWrapperPainter = mainController.entityController.createEntityWrapperPainterAtIndex(
                                index)
                    entityWrapperPainter.z = roleLayer
                    entityWrapperPainter.parent = mapItem
                    entityWrapperPainter.anchors.fill = envelope
                }
            }
        }
    }
}
