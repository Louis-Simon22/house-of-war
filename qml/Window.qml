import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    id: mainWindow
    visible: true
    title: qsTr("Era")
    visibility: Window.Maximized

    Swapper {
        anchors.fill: parent
    }
}
