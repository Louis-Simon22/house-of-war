import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Swapper {
        anchors.fill: parent
    }
}
