import QtQuick 2.11

Rectangle {
    id: listItem

    height: Math.max(label.height, button.height) + paddingVertical * 2
    width: label.width + button.width + paddingHorizontal * 2

    border.color: "#e9e9e9"
    border.width: 5
    // round edges
    radius: 10

    property int paddingHorizontal: 10
    property int paddingVertical: 5

    property alias labelText: label.text
    property alias buttonText: button.text

    signal clicked

    Text {
        id: label
        anchors.left: parent.left
        anchors.leftMargin: paddingHorizontal
        anchors.verticalCenter: parent.verticalCenter

        font.pixelSize: 18
        color: "black"
    }

    MenuButton {
        id: button
        anchors.left: label.right
        anchors.leftMargin: paddingHorizontal
        anchors.verticalCenter: parent.verticalCenter

        onClicked: listItem.clicked()
    }
}
