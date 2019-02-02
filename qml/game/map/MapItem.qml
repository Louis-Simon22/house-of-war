import QtQuick 2.12

import com.louissimonmcnicoll.how.bind.gamemanager 1.0
import com.louissimonmcnicoll.how.bind.worldmodel 1.0
import com.louissimonmcnicoll.how.bind.celloutlinespainter 1.0
import com.louissimonmcnicoll.how.bind.pathspainter 1.0

Item {
    id: mapItem

    property GameManager gameManager

    Flickable {
        anchors.fill: mapItem

        contentWidth: gameManager.worldBounds.width
        contentHeight: gameManager.worldBounds.height

        Rectangle {
            x: gameManager.worldBounds.x
            y: gameManager.worldBounds.y
            width: gameManager.worldBounds.width
            height: gameManager.worldBounds.height
            border.color: "black";
            color: "transparent"
        }

        CellOutlinesPainter {
            x: gameManager.worldBounds.x
            y: gameManager.worldBounds.y
            width: gameManager.worldBounds.width
            height: gameManager.worldBounds.height

            segments: gameManager.outlineSegments
        }    

        PathsPainter {
            x: gameManager.worldBounds.x
            y: gameManager.worldBounds.y
            width: gameManager.worldBounds.width
            height: gameManager.worldBounds.height

            segments: gameManager.pathSegments
        }

        Repeater {
            model: gameManager.worldModel
            delegate: Item{
                Text {
                    id: cellLabel
                    x: posX - paintedWidth  / 2
                    y: posY - paintedHeight / 2
                    text: index
                }
            }
        }
    }
}
