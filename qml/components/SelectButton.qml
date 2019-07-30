import QtQuick 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.12

AbstractButton {
    id: selectButton

    height: button.height
    width: button.width

    property int paddingVertical: 3

    property bool isSelected: false

    property alias text: button.text

    signal selected

    MenuButton {
        id: button

        onClicked: {
            selectButton.selected()
        }
    }

    RectangularGlow {
        id: buttonGlow
        anchors.fill: button
        visible: selectButton.checked

        glowRadius: 10
        spread: 0.2
        color: "white"
        cornerRadius: button.radius + glowRadius
    }
}
