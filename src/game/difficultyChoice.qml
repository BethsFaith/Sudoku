import QtQuick 2.0

import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12

import SudokuModule

Item {
    id : levelChoicePage
    visible : true

    ColumnLayout {
        id: choiceMenu
        anchors.centerIn: parent

        Button {
            id: easyButton
            text: labels.getText("easyLevel")
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                root.difficulty = 1;
                viewLoader.source = qsTr("qrc:/SudokuModule/src/game/game.qml")
            }
        }
        Button {
            id: mediumButton
            text: labels.getText("mediumLevel")
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                root.difficulty = 2;
                viewLoader.source = qsTr("qrc:/SudokuModule/src/game/game.qml")
            }
        }
        Button {
            id: hardButton
            text: labels.getText("hardLevel")
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                root.difficulty = 3;
                viewLoader.source = qsTr("qrc:/SudokuModule/src/game/game.qml")
            }
        }
        Button {
            id: veryHardButton
            text: labels.getText("extremeLevel")
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                root.difficulty = 4;
                viewLoader.source = qsTr("qrc:/SudokuModule/src/game/game.qml")
            }
        }
    }
}