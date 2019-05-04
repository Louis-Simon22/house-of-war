import QtQuick 2.11
import QtQuick.Layouts 1.1

import "components/"

import com.louissimonmcnicoll.how.ui.modelmanager 1.0

BaseMenu {
    id: generateMenu

    property ModelManager modelManager

    signal newModelGenerated

    Rectangle {
        anchors.fill: generateMenu
        color: "#49a349"
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10

        MenuButton {
            Layout.alignment: Qt.AlignCenter
            text: "Generate"
            onClicked: {
                generateMenu.modelManager.newModelGenerated.connect(
                            generateMenu.newModelGenerated)
                generateMenu.modelManager.newModel(
                            parseInt(worldWidth.input, 10),
                            parseInt(worldHeight.input, 10),
                            parseFloat(minimumVoronoiCellDistance.input),
                            parseInt(randomSeed.input, 10))
                generateMenu.modelManager.newModelGenerated.disconnect(
                            generateMenu.newModelGenerated)
            }
        }

        MenuNumberInput {
            Layout.alignment: Qt.AlignCenter
            id: worldWidth
            label: "World Width"
            input: "500"
        }
        MenuNumberInput {
            Layout.alignment: Qt.AlignCenter
            id: worldHeight
            label: "World Height"
            input: "300"
        }
        MenuNumberInput {
            Layout.alignment: Qt.AlignCenter
            id: minimumVoronoiCellDistance
            label: "Minimum Voronoi Cell Distance"
            input: "30"
        }
        MenuNumberInput {
            Layout.alignment: Qt.AlignCenter
            id: randomSeed
            label: "Random Seed"
            input: "100"
        }

    }

    MenuButton {
        text: "Back"
        anchors.right: generateMenu.right
        anchors.rightMargin: 10
        anchors.top: generateMenu.top
        anchors.topMargin: 10
        onClicked: back()
    }
}
