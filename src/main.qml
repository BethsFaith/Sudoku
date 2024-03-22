import QtQuick 2.0

import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12

import SudokuModule

ApplicationWindow {
    id: root

    visible: true

    minimumWidth: 400
    minimumHeight: 640

    Material.theme : Material.Dark

    background: Rectangle {
        gradient: Gradient {
            GradientStop {
                position: 0; color: "#8f8a8a"
            }
            GradientStop {
                position: 1; color: "#e56f6f"
            }
        }
    }

    Loader {
        id: viewLoader

        anchors.fill : parent
    }

    RecordStorage {
        id : storage
    }
    LabelStorage {
        id : labels
    }
    Geolocation {
        id : geoloc
    }

    Component.onCompleted : {
        storage.parse(recordsPath);
        labels.parse(labelsPath, "ru");

        viewLoader.source = "qrc:/SudokuModule/src/mainMenu.qml"
    }

    Component.onDestruction : {
        storage.save(recordsPath);
    }

    signal languageChanged(language : string)
    onLanguageChanged : (language) => {
        labels.parse(labelsPath, language);

        let source = viewLoader.source;
        viewLoader.source = "";
        viewLoader.source = source;
    }

    Connections {
        target: geoloc

        function onCountryUpdated(country) {
            var language;
            if (country === "Russia") {
                language = "ru";
            } else if (country === "Spain") {
                language = "sp";
            } else if (country === "China") {
                language = "ch";
            } else {
                language = "en";
            }
            languageChanged(language);
        }
    }

    property int difficulty : 1
    property string recordsPath : "./records.json"
    property string labelsPath : ":/resources/languages.json"
}