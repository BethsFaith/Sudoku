import QtQuick 2.0

import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: recordsPage

    SwipeView {
        id: recordView

        anchors.fill: parent
        wheelEnabled: true

        currentIndex: recordTabBar.currentIndex

        Repeater {
            id: recordPageRepeater

            model: recordPages
            delegate: Page {
                header: ColumnLayout {
                    spacing : 10
                    Button {
                        palette.button: "#ffffff"
                        palette.buttonText : "#5d5454"
                        text: "<---"
                        font.bold : true
                        font.pixelSize : 20

                        onClicked : {
                            viewLoader.source = "qrc:/SudokuModule/src/mainMenu.qml";
                        }
                    }
                    Label {
                        Layout.fillWidth : true

                        text: recordTabBar.currentItem.text
                        color: "#832758"
                        font.pixelSize: 22
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
                background: Rectangle {
                    gradient: Gradient {
                        GradientStop {
                            position: 0; color: "#ffa0a0"
                        }
                        GradientStop {
                            position: 1; color: "#ffffff"
                        }
                    }
                }
                ColumnLayout {
                    visible: true

                    anchors.left : parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.topMargin: 25
                    spacing : 0

                    property var records: storage.getRecords(model.source)

                    Repeater {
                        model: parent.records

                        delegate: RowLayout {
                            required property int index
                            required property string modelData

                            Layout.fillWidth : true

                            spacing : 0

                            Label {
                                Layout.minimumHeight: 50
                                Layout.minimumWidth: 50

                                color : "white"
                                font.bold : true

                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter

                                background: Rectangle {
                                    color: "#626262"
                                    border.width: 1
                                    border.color: "black"
                                }

                                text : index+1
                            }
                            Label {
                                Layout.minimumHeight: 50
                                Layout.minimumWidth: 50
                                Layout.fillWidth : true

                                color : "white"
                                font.bold : true

                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter

                                background: Rectangle {
                                    color: "#626262"
                                    border.width: 1
                                    border.color: "black"
                                }
                                text : modelData
                            }
                        }
                    }
                }
            }
        }
    }

    ListModel {
        id: recordPages

        ListElement {
            index: 0
            source: "easy"
        }
        ListElement {
            index: 1
            source: "medium"
        }
        ListElement {
            index: 2
            source: "hard"
        }
        ListElement {
            index: 3
            source: "extreme"
        }
    }

    TabBar {
        id: recordTabBar

        currentIndex: recordView.currentIndex

        width: parent.width
        anchors.bottom: recordView.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        TabButton {
            anchors.bottom: parent.bottom

            text: labels.getText("easyLevel")
            palette.button: "#3f3c3c"
            palette.buttonText: "#ffffff"
        }
        TabButton {
            anchors.bottom: parent.bottom

            text: labels.getText("mediumLevel")
            palette.button: "#3f3c3c"
            palette.buttonText: "#ffffff"
        }
        TabButton {
            anchors.bottom: parent.bottom

            text: labels.getText("hardLevel")
            palette.button: "#3f3c3c"
            palette.buttonText: "#ffffff"
        }
        TabButton {
            anchors.bottom: parent.bottom

            text: labels.getText("extremeLevel")
            palette.button: "#3f3c3c"
            palette.buttonText: "#ffffff"
        }
    }
}