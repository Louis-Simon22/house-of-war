import QtQuick 2.0

import com.louissimonmcnicoll.how.ui.voronoicellbindings 1.0

Item {
    id: voronoiCellDetails
    visible: voronoiCellBindings.isBound

    property VoronoiCellBindings voronoiCellBindings

    Text {
        id: title
        anchors.top: parent.top
        anchors.left: parent.left
        text: qsTr("Tile")
        font.pixelSize: 12
    }

    Text {
        id: label
        anchors.top: title.bottom
        anchors.left: parent.left
        text: qsTr("Altitude")
        font.pixelSize: 12
    }

    Text {
        id: value
        anchors.top: label.top
        anchors.left: label.right
        text: voronoiCellDetails.voronoiCellBindings.altitude
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }
}
