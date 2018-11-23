import QtQuick 2.11
import com.louissimonmcnicoll.how.bind.gamemanager 1.0
import "components/"

BaseMenu {
    id: loadScene

    property GameManager gameManager

    Text {
        text: "Load Game Menu"
        color: "blue"

        anchors.centerIn: parent
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
