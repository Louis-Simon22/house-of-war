import QtQuick 2.0

import com.louissimonmcnicoll.how.ui.armybindings 1.0

Item {
    id: armyDetails
    visible: armyBindings.visible

    property ArmyBindings armyBindings

    Text {
        id: title
        anchors.top: parent.top
        anchors.left: parent.left
        text: qsTr("Army")
        font.pixelSize: 12
    }

    Text {
        id: label
        anchors.top: title.bottom
        anchors.left: parent.left
        text: qsTr("Size")
        font.pixelSize: 12
    }

    Text {
        id: value
        anchors.top: label.top
        anchors.left: label.right
        text: armyDetails.armyBindings.size
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }
}
