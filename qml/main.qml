import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

import PhotoPruner.Controllers 1.0

ApplicationWindow {
    id: mainWindow
    visible: true

    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600

    visibility: Window.Maximized

    color: "white"

    Actions {
        id: actions
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"

            MenuItem { action: actions.newAction }
            MenuItem { action: actions.openAction }
            MenuSeparator {}
            MenuItem { action: actions.saveAction }
            MenuItem { action: actions.saveAsAction }
            MenuSeparator{}
            MenuItem { action: actions.importAction }
            MenuSeparator{}
            MenuItem { action: actions.deletePrunedImagesAction }
        }

        Menu {
            title: "&Edit"

            MenuItem { action: actions.flagForPruningAction }
            MenuItem { action: actions.unflagForPruningAction }

            MenuSeparator {}

            MenuItem { action: actions.editTagsAction }

            MenuSeparator {}

            MenuItem { action: actions.removeFromProjectAction }
        }
    }

    toolBar: ToolBar {
        RowLayout {
            ToolButton { action: actions.newAction }
            ToolButton { action: actions.openAction }
            ToolButton { action: actions.saveAction }
            ToolButton { action: actions.saveAsAction }
            ToolButton { action: actions.importAction }
            ToolButton { action: actions.deletePrunedImagesAction }
            ToolButton { action: actions.flagForPruningAction }
            ToolButton { action: actions.unflagForPruningAction }
            ToolButton { action: actions.editTagsAction }
            ToolButton { action: actions.removeFromProjectAction }
        }
    }

    Rectangle {
        anchors.fill: parent

        color: "blue"

        RowLayout {
            spacing: 0

            anchors.fill: parent

            Component {
                id: imageListDelegate

                Item {
                    property variant sourceModel: model

                    width: 180; height: 40
                    Column {
                        Text { text: '<b>Path:</b> ' + display }
                    }

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            listView.currentIndex = index
                        }
                    }
                }

            }

            // qml equivalent to "wrap it in widget", "wrap it in an item!"
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    Row {
                        PruningFilterComboBox {
                            id: pruningFilterCombo
                        }

                        TextField {
                            id: tagFilterField

                            onTextChanged: appController.setTagFilter(text)
                        }
                    }

                    ListView {
                        id: listView

                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        model: appController.projectModel
                        keyNavigationWraps: true
                        delegate: imageListDelegate
                        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                        focus: true

                        onCurrentItemChanged: {
                            imageController.setImage(currentItem.sourceModel.sourcePath)
                        }
                    }
                }
            }

            ImagePreviewPanel {
                imageSource: listView.currentItem? listView.currentItem.sourceModel?
                                                       listView.currentItem.sourceModel.sourceUrl : "" : ""
                color: "grey"

                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}
