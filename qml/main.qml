import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

import PhotoPruner.Controllers 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
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
        }
    }

    toolBar: ToolBar {
        RowLayout {
            ToolButton { action: actions.newAction }
            ToolButton { action: actions.openAction }
            ToolButton { action: actions.saveAction }
            ToolButton { action: actions.saveAsAction }
            ToolButton { action: actions.importAction }
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
                    property string sourcePath: model.sourcePath
                    property url sourceUrl: model.sourceUrl

                    width: 180; height: 40
                    Column {
                        Text { text: '<b>Path:</b> ' + display }
                    }

                    MouseArea {
                        anchors.fill: parent

                        onClicked: listView.currentIndex = index
                    }
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
                    imageController.setImage(currentItem.sourcePath)
                }
            }

            ImagePreviewPanel {
                imageSource: listView.currentItem? listView.currentItem.sourceUrl : ""
                color: "grey"

                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}
