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

    onClosing: actions.autosave()

    color: "white"

    title: "Photo Pruner | " + appController.projectName

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
            MenuSeparator {}
            MenuItem { action: actions.quitAction }
        }

        Menu {
            title: "&Edit"

            MenuItem { action: actions.flagForPruningAction }
            MenuItem { action: actions.unflagForPruningAction }

            MenuSeparator {}

            MenuItem { action: actions.editTagsAction }

            MenuSeparator {}

            MenuItem { action: actions.rotateCW }
            MenuItem { action: actions.rotateCCW }

            MenuSeparator {}

            MenuItem { action: actions.removeFromProjectAction }
        }

        Menu {
            title: "&View"

            MenuItem { action: actions.resetZoom }
            MenuSeparator {}
            MenuItem { action: actions.zoomIn }
            MenuItem { action: actions.zoomOut }
        }
    }

    RowLayout {
        id: viewingPanels

        spacing: 0

        anchors.fill: parent

        ColumnLayout {
            spacing: 0

            Layout.fillWidth: false

            ToolBar {
                Layout.fillWidth: true

                RowLayout {
                    anchors.verticalCenter: parent.verticalCenter

                    FontAwesomeButton { action: actions.newAction; text: "\uf016" } // fa-file-o
                    FontAwesomeButton { action: actions.openAction; text: "\uf115" } // fa-folder-open-o
                    FontAwesomeButton { action: actions.saveAction; text: "\uf0c7" } // fa-save
                    FontAwesomeButton { action: actions.importAction; text: "\uf1c5" } // fa-file-image-o
                    FontAwesomeButton { action: actions.deletePrunedImagesAction; text: "\uf014" } // fa-trash-o
                }
            }

            ImageListPanel {
                id: listPanel

                Layout.fillHeight: true
                Layout.fillWidth: true

                Layout.minimumWidth: minimumWidth
            }
        }

        ColumnLayout {
            spacing: 0

            ToolBar {
                Layout.fillWidth: true

                RowLayout {
                    anchors.centerIn: parent

                    FontAwesomeButton { action: actions.editTagsAction; text: "\uf02c" } // fa-tags
                    FontAwesomeButton { action: actions.flagForPruningAction; text: "\uf024" } // fa-flag
                    FontAwesomeButton { action: actions.unflagForPruningAction; text: "\uf11d" } //fa-flag-o
                    FontAwesomeButton { action: actions.rotateCCW; text: "\uf0e2" } // fa-rotate-left
                    FontAwesomeButton { action: actions.rotateCW; text: "\uf01e" } // fa-rotate-right
                    FontAwesomeButton { action: actions.removeFromProjectAction; text: "\uf00d" } // fa-times
                }
            }

            ImagePreviewPanel {
                id: previewPanel

                Layout.fillHeight: true
                Layout.fillWidth: true

                imageSource: listPanel.currentImageUrl

                Connections {
                    target: actions

                    onResetZoomRequested: previewPanel.resetZoom()
                    onZoomInRequested: previewPanel.zoomIn()
                    onZoomOutRequested: previewPanel.zoomOut()

                    onRotatingCW: previewPanel.setRotationDirectionClockwise()
                    onRotatingCCW: previewPanel.setRotationDirectionCounterClockwise()
                }
            }
        }
    }
}
