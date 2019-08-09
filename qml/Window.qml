import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    id: mainWindow
    visible: true
    title: qsTr("House of War")
    visibility: Window.Maximized

    Swapper {
        anchors.fill: parent
    }

    onActiveFocusItemChanged: console.log(
                                  "Focus changed to : " + activeFocusItem)
}
