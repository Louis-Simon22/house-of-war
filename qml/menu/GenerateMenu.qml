import QtQuick 2.11
import QtQuick.Layouts 1.1

import "../components"

import com.louissimonmcnicoll.how.ui.modelcontroller 1.0

BaseMenu {
    id: generateMenu

    property ModelController modelController

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
                generateMenu.modelController.newModelGenerated.connect(
                            generateMenu.newModelGenerated)
                generateMenu.modelController.newModel(
                            fileName.input, parseInt(worldWidth.input, 10),
                            parseInt(worldHeight.input, 10),
                            parseFloat(minimumVoronoiCellDistance.input),
                            parseInt(randomSeed.input, 10))
                generateMenu.modelController.newModelGenerated.disconnect(
                            generateMenu.newModelGenerated)
            }
        }

        MenuInput {
            id: fileName
            Layout.alignment: Qt.AlignCenter
            inputMethodHints: Qt.ImhLowercaseOnly
            label: "File Name"
            input: "greg.json"
        }
        MenuInput {
            id: worldWidth
            Layout.alignment: Qt.AlignCenter
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            label: "World Width"
            input: "300"
        }
        MenuInput {
            id: worldHeight
            Layout.alignment: Qt.AlignCenter
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            label: "World Height"
            input: "200"
        }
        MenuInput {
            id: minimumVoronoiCellDistance
            Layout.alignment: Qt.AlignCenter
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            label: "Minimum Voronoi Cell Distance"
            input: "25"
        }
        MenuInput {
            id: randomSeed
            Layout.alignment: Qt.AlignCenter
            inputMethodHints: Qt.ImhFormattedNumbersOnly
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
