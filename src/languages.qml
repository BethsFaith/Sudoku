import QtQuick 2.0

import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12

import SudokuModule
Item {
    id : languagePage

    ColumnLayout {
        id : languageMenu

        anchors.centerIn : parent

        Button {
            id : ruButton

            text : "Русский"

            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                languageChanged("ru")

                viewLoader.source = "qrc:/SudokuModule/src/mainMenu.qml"
            }
        }
        Button {
            id : enButton

            text : "English"

            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                languageChanged("en")

                viewLoader.source = "qrc:/SudokuModule/src/mainMenu.qml"
            }
        }
        Button {
            id : spButton

            text : "Español"

            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                languageChanged("sp")

                viewLoader.source = "qrc:/SudokuModule/src/mainMenu.qml"
            }
        }
        Button {
            id : chButton

            text : "Chino"

            Layout.preferredWidth: 200
            Layout.preferredHeight: 50

            onClicked : {
                languageChanged("ch")

                viewLoader.source = "qrc:/SudokuModule/src/mainMenu.qml"
            }
        }
    }
}