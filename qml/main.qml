import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import PhotoPruner.AppModel 1.0

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

            MenuItem { action: actions.openAction }
            MenuItem { action: actions.saveAction }
            MenuItem { action: actions.saveAsAction }
            MenuItem { action: actions.importAction }
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

                model: appModel.projectModel
                keyNavigationWraps: true
                delegate: imageListDelegate
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                focus: true

                onCurrentIndexChanged: appModel.determineCurrentImageUrl(currentIndex)
            }

            Rectangle {
                id: previewPanel

                color: "red"

                Layout.fillHeight: true
                Layout.fillWidth: true

                Image {
                    id: image

                    asynchronous: true

                    source: appModel.currentImageUrl

                    anchors.fill: parent

                    onSourceChanged: console.log("source changed to" + source)
                }
            }
        }
    }
}
