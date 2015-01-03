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

            MenuItem { action: actions.removeFromProjectAction }
        }
    }

    toolBar: ToolBar {
        RowLayout {
            FontAwesomeButton { action: actions.newAction; text: "\uf016" } // fa-file-o
            FontAwesomeButton { action: actions.openAction; text: "\uf115" } // fa-folder-open-o
            FontAwesomeButton { action: actions.saveAction; text: "\uf0c7" } // fa-save
            FontAwesomeButton { action: actions.importAction; text: "\uf1c5" } // fa-file-image-o
            FontAwesomeButton { action: actions.deletePrunedImagesAction; text: "\uf014" } // fa-trash-o
            FontAwesomeButton { action: actions.flagForPruningAction; text: "\uf024" } // fa-flag
            FontAwesomeButton { action: actions.unflagForPruningAction; text: "\uf11d" } //fa-flag-o
            FontAwesomeButton { action: actions.editTagsAction; text: "\uf02c" } // fa-tags
            FontAwesomeButton { action: actions.removeFromProjectAction; text: "\uf00d" } // fa-times
        }
    }

    Rectangle {
        anchors.fill: parent

        SplitView {
            orientation: Qt.Horizontal

            anchors.fill: parent

            ImageListPanel {
                id: listPanel

                Layout.minimumWidth: minimumWidth
            }

            ImagePreviewPanel {
                imageSource: listPanel.currentImageUrl
            }
        }
    }
}
