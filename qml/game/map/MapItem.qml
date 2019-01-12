import QtQuick 2.12

import com.louissimonmcnicoll.how.bind.gamemanager 1.0
import com.louissimonmcnicoll.how.bind.models.worldmodel 1.0

Item {
    id: mapItem

    property GameManager gameManager

    Flickable {
        anchors.fill: mapItem

        contentWidth: gameManager.worldDimensions.width
        contentHeight: gameManager.worldDimensions.height

        Rectangle {
            x: gameManager.worldDimensions.x
            y: gameManager.worldDimensions.y
            width: gameManager.worldDimensions.width
            height: gameManager.worldDimensions.height
            border.color: "black";
            color: "transparent"
        }
        Repeater {
            model: gameManager.worldModel
            delegate: Text {
                x: posX
                y: posY
                text: index
            }
        }
        Repeater {
            model: gameManager.edgesModel
            delegate: Text {
                x: posX1
                y: posY1
                color: "red"
                text: index
            }
        }
    //        Repeater {
    //            model: gameManager.edgesModel
    //            delegate: Item {
    //                Path {
    //                    startX: posX1; startY: posY1
    //                    PathLine { x: posX2; y: posY2 }
    //                }
    //            }
    //        }
    }
}
