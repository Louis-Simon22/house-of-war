import QtQuick 2.11

Item {
    id: menuBase

    signal back

    opacity: 0
    visible: opacity > 0
    enabled: visible

    Behavior on opacity {
        NumberAnimation {
            property: "opacity"
            easing.type: Easing.InOutQuad
        }
    }
}
