import QtQuick 2.11

import "../components"

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0

BaseMenu {
    id: loadScene

    property ModelController modelController

    signal newModel
    signal modelLoaded

    ListView {
        id: saveFilesList
        width: contentItem.childrenRect.width
        height: contentItem.childrenRect.height
        anchors.centerIn: parent

        model: loadScene.modelController.getAllSaveFiles()
        delegate: MenuListItem {
            anchors.left: parent.left

            labelText: modelData.name
            buttonText: qsTr("Load")
            onClicked: {
                loadScene.modelController.loadFromFile(modelData.name)
                loadScene.modelLoaded()
            }
        }
    }

    MenuButton {
        id: newGameButton
        anchors.right: saveFilesList.right
        anchors.top: saveFilesList.bottom
        anchors.topMargin: 5

        text: qsTr("New")
        onClicked: {
            loadScene.newModel()
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
