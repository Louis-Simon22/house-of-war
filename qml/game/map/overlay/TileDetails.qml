import QtQuick 2.0

import com.louissimonmcnicoll.how.ui.tilebindings 1.0

Item {
    id: voronoiCellDetails
    visible: tileBindings.visible

    property TileBindings tileBindings

    Text {
        id: title
        anchors.top: parent.top
        anchors.left: parent.left
        text: qsTr("Tile")
        font.pixelSize: 12
    }

    Text {
        id: altitudeLabel
        anchors.top: title.bottom
        anchors.left: parent.left
        text: qsTr("Altitude")
        font.pixelSize: 12
    }

    Text {
        id: altitudeValue
        anchors.top: altitudeLabel.top
        anchors.left: altitudeLabel.right
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Text {
        id: resourcesLabel
        anchors.top: altitudeLabel.bottom
        anchors.left: parent.left
        text: qsTr("Resources")
        font.pixelSize: 12
    }

    Text {
        id: resourcesValue
        anchors.top: resourcesLabel.top
        anchors.left: resourcesLabel.right
        text: tileBindings.resources
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }
}
