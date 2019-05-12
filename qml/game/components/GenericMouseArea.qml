import QtQuick 2.0

MouseArea {
    id: genericMouseArea
    anchors.fill: parent

    signal mouseClicked(real posX, real posY, int button)

    propagateComposedEvents: false
    onClicked: {
        genericMouseArea.mouseClicked(mouse.x, mouse.y, mouse.button)
        mouse.accepted = true
    }
}
