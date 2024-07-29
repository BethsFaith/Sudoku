import QtQuick 2.15

import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.Material 2.12

import SudokuModule
Item {
    ColumnLayout {
        id: gamePage

        anchors.fill: parent

        visible: true

        Sudoku {
            id: sudoku

            Component.onCompleted : {
                sudoku.start(root.difficulty);
            }
        }

        Timer {
            id : timer

            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                time.seconds += 1;

                time.text = (time.name + ": " + time.seconds)
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignTop  | Qt.AlignHCenter

            Text {
                id : time
                color: "#ffffff"

                property string name : labels.getText("time")
                property int seconds : 0;

                text : (name + ": " + time.seconds)
            }

            Button {
                id : hintButton

                palette.button: "#5d5454"
                palette.buttonText: "#ffffff"
                text: labels.getText("hintButton");

                onPressed : {
                    sudoku.playerHint();
                }
            }

            Button {
                id : exitButton

                palette.button: "#5d5454"
                palette.buttonText: "#ffffff"
                text: labels.getText("exitButton");

                onPressed : {
                    exitDialog.open();
                    }
            }
        }

        TableView {
            id: gameGrid

            interactive: false

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.preferredWidth: 270
            Layout.preferredHeight: 270

            columnSpacing: 1
            rowSpacing: 1

            visible: true

            model: sudoku.grid

            delegate: Rectangle {
                implicitWidth: 30
                implicitHeight: 30

                border.width : 2

                Text {
                    id: value

                    color: "#ffffff"
                    text: display
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log(model.row, model.column, buttons.checkedButton.index + 1);
                        sudoku.playerMove(model.row, model.column, buttons.checkedButton.index + 1);
                    }
                }

                Component.onCompleted : {
                    color = sudoku.style.getCellBackgroundColor(model.row, model.column);
                    value.color = sudoku.style.getCellTextColor(model.row, model.column);
                    border.color = sudoku.style.getCellBorderColor(model.row, model.column);
                }
            }
        }

        Connections {
            target: sudoku.grid

            function onDataChanged(topLeft, bottomRight) {
                let cell = gameGrid.itemAtIndex(topLeft);
                cell.color = sudoku.style.getCellBackgroundColor(topLeft.row, topLeft.column);
                cell.border.color = sudoku.style.getCellBorderColor(topLeft.row, topLeft.column);
            }
        }

        ButtonGroup {
            id: buttons

            buttons: row.children
        }
        RowLayout {
            id: row

            Layout.alignment: Qt.AlignHCenter
            spacing : 0

            Repeater {
                model: 9
                delegate: Button {
                    checked: false

                    implicitWidth: 40
                    implicitHeight: 40

                    background: Rectangle {
                        id: buttonBackground

                        color: "#5d5454"
                        border.color: "#ffffff"
                        border.width : 2
                    }

                    required property int index

                    Text {
                        anchors.centerIn: parent
                        color: "#ffffff"
                        text: (index + 1)
                    }

                    onPressedChanged: {
                        buttonBackground.border.color = "cyan"
                        buttonBackground.color = "darkCyan";
                        checked = true
                    }
                    onActiveFocusChanged: {
                        buttonBackground.border.color = "white"
                        buttonBackground.color = "#5d5454"
                        checked = false
                    }

                    ButtonGroup.group: buttons
                }
            }
        }

        Dialog {
            id: winDialog
            title: labels.getText("winDialog")
            modal: true
            anchors.centerIn : parent
            implicitWidth: 200
            implicitHeight: 150
            padding: 0
            header:
                Label {
                    text: winDialog.title
                    horizontalAlignment: Text.AlignHCenter
                    color: "#ffffff"
                    font.bold: true
                    padding: 10
                    background: Rectangle {
                        color: "#5d5454"
                        border.width: 1.0
                        border.color: "#ffffff"
                    }
                }
            contentItem:
                Label {
                    text: labels.getText("winDialogContent").arg(time.seconds)
                    font.pointSize: 9
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#ffffff"
                    font.bold: true
                    padding: 10
                    background: Rectangle {
                        color: "#353535"
                    }
                }
            footer: DialogButtonBox {
                background: Rectangle {
                    color: "#707070"
                    border.width: 1.0
                    border.color: "#ffffff"
                }
                Button {
                    DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
                    contentItem: Text {
                        text: labels.getText("okButton")
                        color: "#ffffff"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                    background: Rectangle {
                        color: "#8fbc8f"
                        radius: 10
                        border.width: 1.0
                        border.color: "#b1ffb1"
                    }
                }
                Button {
                    DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
                    contentItem: Text {
                        text: labels.getText("cancelButton")
                        color: "#ffffff"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                    background: Rectangle {
                        color: "#c07d9d"
                        radius: 10
                        border.width: 1.0
                        border.color: "#be5b8c"
                    }
                }
            }
            onAccepted: {
                winDialog.close();
                viewLoader.source = qsTr("")
                viewLoader.source = qsTr("qrc:/SudokuModule/src/game/game.qml")
            }
            onRejected: {
                winDialog.close();
                viewLoader.source = qsTr("qrc:/SudokuModule/src/mainMenu.qml")
            }
        }

        Dialog {
            id: exitDialog

            title: labels.getText("exitDialog")
            modal: true
            anchors.centerIn : parent
            implicitWidth: 200
            implicitHeight: 150
            padding: 0

            Material.theme : Material.Dark

            header:
                Label {
                    text: exitDialog.title
                    horizontalAlignment: Text.AlignHCenter
                    color: "#ffffff"
                    font.bold: true
                    padding: 10
                    background: Rectangle {
                        color: "#5d5454"
                        border.width: 1.0
                        border.color: "#ffffff"
                    }
                }
            contentItem:
                Label {
                    text: labels.getText("exitDialogContent")
                    font.pointSize: 9
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#ffffff"
                    font.bold: true
                    padding: 10
                    background: Rectangle {
                        color: "#353535"
                    }
                }
            footer: DialogButtonBox {
                background: Rectangle {
                    border.width: 1.0
                }
                Button {
                    DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
                    contentItem: Text {
                        text: labels.getText("okButton")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                    background: Rectangle {
                        radius: 10
                        border.width: 1.0
                    }
                }
                Button {
                    DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
                    contentItem: Text {
                        text: labels.getText("cancelButton")
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                    }
                    background: Rectangle {
                        radius: 10
                        border.width: 1.0
                    }
                }
            }
            onAccepted: {
                exitDialog.close();
                viewLoader.source = qsTr("qrc:/SudokuModule/src/mainMenu.qml")
            }
            onRejected: {
                exitDialog.close();
            }
        }

        Connections {
            target: sudoku

            function onWin(mouse) {
                timer.stop();
                storage.setRecord(sudoku.getDifficultyName(difficulty), time.seconds);
                winDialog.open();
            }
        }
    }
}