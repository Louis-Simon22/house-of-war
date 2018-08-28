import VPlay 2.0
import QtQuick 2.11
import gamemanager 1.0
import worldmodel 1.0
import "../"
import "../../components/menu"

SceneBase {
    id: mapScene

    property GameManager gameManager

    // TODO make a binder to call the data with methods based on index
    Repeater {
        model: gameManager.getWorldModel()
        delegate: Rectangle {
            x: 50
            y: 50
            width: 15
            height: 15
        }
    }

    Text {
        id: loadingView
        anchors.centerIn: parent
        color: "white"
        text: "Map Scene"
    }

    // Hold properties not meant for outside use
//    QtObject {
//        id: p
//        property real worldModel: mapScene.gameManager.getWorldModel() //not meant for outside use
//    }
}
