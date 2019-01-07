import QtQuick 2.0

import com.louissimonmcnicoll.how.bind.gamemanager 1.0
import com.louissimonmcnicoll.how.bind.models.worldmodel 1.0

Item {
    id: mapItem

    property GameManager gameManager

    Flickable {
        anchors.fill: mapItem

        contentWidth: gameManager.worldDimensions.width
        contentHeight: gameManager.worldDimensions.height
        Repeater {
            model: gameManager.worldModel
            delegate: Text {
                x: posX
                y: posY
                text: index + "(" + posX + ","  + posY + ")"
            }
        }
    }
}
