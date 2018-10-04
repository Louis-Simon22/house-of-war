import gamemanager 1.0
import worldmodel 1.0
import QtQuick 2.0

Item {
    id: mapItem

    property GameManager gameManager

    Flickable {
        anchors.fill: mapItem

        contentWidth: gameManager.worldDimensions.width
        contentHeight: gameManager.worldDimensions.height
        Repeater {
            model: gameManager.worldModel
            delegate: Rectangle {
                x: posX
                y: posY
                height: 5
                width: 5
                color: "red"
            }
        }
    }
}
