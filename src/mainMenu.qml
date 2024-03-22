import QtQuick 2.0

import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12

Item {
    id : mainMenu
    visible : true

    ColumnLayout {
        id: menu
        anchors.centerIn: parent

        Button {
            text: labels.getText("playButton")
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                viewLoader.source = qsTr("qrc:/SudokuModule/src/game/difficultyChoice.qml")
            }
        }
        Button {
            text: labels.getText("recordButton")
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                viewLoader.source = qsTr("qrc:/SudokuModule/src/records/records.qml")
            }
        }
        Button {
            text: labels.getText("exitButton")
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                Qt.exit(0);
            }
        }
    }

    Button {
        anchors.bottom : parent.bottom

        icon.name : "language"
        icon.source : "qrc:/resources/language.png"
        icon.height : 50
        icon.width : 50

        onClicked : {
            viewLoader.source = qsTr("qrc:/SudokuModule/src/languages.qml")
        }
    }
}