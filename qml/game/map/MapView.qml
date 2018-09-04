import QtQuick 2.11
import gamemanager 1.0
import worldmodel 1.0
import QtQml.Models 2.11

Item {
    property GameManager gameManager

    // TODO make a binder to call the data with methods based on index
    Repeater {
        model: mapModel //gameManager.getWorldModel()
    }

    DelegateModel {
        id: mapModel
//        model: gameManager.getWorldModel()
        delegate: Rectangle {
            x: posX
            y: posY
            height: 25
            width: 100
            Text {
                text: "Name: " + name
            }
            color: "red"
        }
    }

    Text {
        id: loadingView
        anchors.centerIn: parent
        color: "black"
        text: "Map Scene"
    }

    // Hold properties not meant for outside use
    //    QtObject {
    //        id: p
    //        property real worldModel: mapScene.gameManager.getWorldModel() //not meant for outside use
    //    }
}
