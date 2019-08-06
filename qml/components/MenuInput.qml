import QtQuick 2.11

Rectangle {
    id: numberInput

    width: Math.max(text.width, textInput.width) + paddingHorizontal * 2
    height: text.height + textInput.height + paddingVertical * 3

    color: "#e9e9e9"
    radius: 10

    property int paddingHorizontal: 10
    property int paddingVertical: 5

    property alias label: text.text
    property alias input: textInput.text
    property alias inputMethodHints: textInput.inputMethodHints

    Text {
        id: text
        font.pixelSize: 18
        color: "black"
        anchors {
            horizontalCenter: parent.horizontalCenter
            topMargin: numberInput.paddingVertical
        }
    }

    TextInput {
        id: textInput
        color: "black"
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: text.bottom
            topMargin: numberInput.paddingVertical
            bottomMargin: numberInput.paddingVertical
        }
        font.pixelSize: 18
    }
}
