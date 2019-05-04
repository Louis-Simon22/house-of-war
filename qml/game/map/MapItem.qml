import QtQuick 2.12
import QtQuick.Shapes 1.12
import QtQml 2.12

import com.louissimonmcnicoll.how.ui.modelmanager 1.0
import com.louissimonmcnicoll.how.ui.graphentitycontroller 1.0
import com.louissimonmcnicoll.how.ui.entitiesmodel 1.0

Flickable {
    id: mapItemFlickable
    anchors.fill: parent
    x: modelManager.worldBounds.x
    y: modelManager.worldBounds.y
    width: modelManager.worldBounds.width
    height: modelManager.worldBounds.height
    contentWidth: mapItem.width * mapItem.scale
    contentHeight: mapItem.height * mapItem.scale
    boundsBehavior: Flickable.DragAndOvershootBounds
    clip: true

    property ModelManager modelManager

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

    // TODO army and characters of cells
    // TODO scale not working
    Item {
        id: mapItem
        anchors.fill: parent

        x: modelManager.worldBounds.x
        y: modelManager.worldBounds.y
        width: modelManager.worldBounds.width
        height: modelManager.worldBounds.height
        property real scale: 3
        transform: Scale {
            xScale: mapItem.scale
            yScale: mapItem.scale
        }

        Repeater {
            id: entities
            model: modelManager.entitiesModel

            property int selectedCharacterIndex: -1
            Text {
                anchors.centerIn: parent

                font.pixelSize: 16
                color: "red"
                text: modelManager.worldBounds.width + "|" + modelManager.worldBounds.height
            }

            delegate: Rectangle {
                id: envelope
                x: rolePosX
                y: rolePosY
                width: roleWidth
                height: roleHeight
                color: "transparent"

                MouseArea {
                    anchors.fill: parent

                    // ignore warning
                    acceptedButtons: roleAcceptedButtons
                    propagateComposedEvents: false
                    onClicked: {
                        mouse.accepted = true
                        console.log("woohoo")
                        // TODO handle click
                    }
                }

                Component.onCompleted: {
                    var entityWrapperItem = modelManager.graphEntityController.createEntityWrapperPainterAtIndex(
                                index)
                    entityWrapperItem.parent = mapItem
                    entityWrapperItem.anchors.fill = mapItem
                }
            }
        }
    }
}
