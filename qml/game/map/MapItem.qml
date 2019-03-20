import QtQuick 2.12

import com.louissimonmcnicoll.how.ui.worlddata 1.0
import com.louissimonmcnicoll.how.ui.characterdata 1.0
import com.louissimonmcnicoll.how.ui.cellsmodel 1.0
import com.louissimonmcnicoll.how.ui.segmentspainter 1.0

Item {
    id: mapItem

    property WorldData worldData
    property CharacterData characterData

    Flickable {
        anchors.fill: mapItem

        contentWidth: worldData.worldBounds.width
        contentHeight: worldData.worldBounds.height

        Rectangle {
            x: worldData.worldBounds.x
            y: worldData.worldBounds.y
            width: worldData.worldBounds.width
            height: worldData.worldBounds.height
            border.color: "black";
            color: "transparent"
        }

        SegmentsPainter {
            x: worldData.worldBounds.x
            y: worldData.worldBounds.y
            width: worldData.worldBounds.width
            height: worldData.worldBounds.height

            segments: worldData.outlineSegments
        }

        SegmentsPainter {
            x: worldData.worldBounds.x
            y: worldData.worldBounds.y
            width: worldData.worldBounds.width
            height: worldData.worldBounds.height

            segments: worldData.pathSegments
        }

        Repeater {
            id: characters
            model: characterData.charactersModel
            delegate: Item{
                Text {
                    id: characterLabel
                    x: posX - paintedWidth  / 2
                    y: posY - paintedHeight / 2
                    text: index
                }
            }
        }

        Repeater {
            id: cells
            model: worldData.cellsModel
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
