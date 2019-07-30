import QtQuick 2.11

import "../components"

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0

BaseMenu {
    id: loadScene

    property ModelController modelController

    signal modelLoaded

    ListView {
        id: saveFilesList

        width: childrenRect.width
        height: childrenRect.height

        anchors.centerIn: parent

        model: loadScene.modelController.getAllSaveFiles()
        delegate: MenuListItem {
            labelText: modelData.name
            buttonText: "Load"

            onClicked: {
                loadScene.modelController.loadFromFile(modelData.name)
                loadScene.modelLoaded()
            }
        }
    }

    MenuButton {
        text: "Back"
        anchors.right: loadScene.right
        anchors.rightMargin: 10
        anchors.top: loadScene.top
        anchors.topMargin: 10
        onClicked: back()
    }
}
