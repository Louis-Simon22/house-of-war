import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

Button {
    id: button

    text: "Greg"
    hoverEnabled: true
    onPressed: button.opacity = 0.5
    onReleased: button.opacity = 1
    onCanceled: released()
    onCheckedChanged: button.opacity = checked ? 0.5 : 1
    background: Rectangle {
        color: "#e9e9e9"
        radius: 10
    }
    font.pointSize: 12
    font.bold: true
}
