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
                x: posX + 200
                y: posY + 150
                text: index
            }
        }
        Repeater {
            model: gameManager.edgesModel
            delegate: Item {
                id: edgeItem
                x: posX + 600
                y: posY + 450

                Text {
                    color: "red"
                    text: index
                }
                Canvas {
                    x: 0
                    y: 0
                    width: 200
                    height: 200
                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.strokeStyle = Qt.rgba(1, 0, 0, 1);
                        console.log(edges);
                        ctx.moveTo(edges[0], edges[1]);
                        ctx.lineTo(edges[2], edges[3]);
                        ctx.lineTo(edges[4], edges[5]);
                        ctx.lineTo(edges[6], edges[7]);
                        ctx.stroke();
                    }
                }
            }
        }
    }
}
