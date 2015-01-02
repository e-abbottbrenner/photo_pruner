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

        SplitView {
            orientation: Qt.Horizontal

            anchors.fill: parent

            ImageListPanel {
                id: listPanel

                Layout.minimumWidth: minimumWidth
            }

            ImagePreviewPanel {
                imageSource: listPanel.currentImageUrl

                color: "grey"
            }
        }
    }
}
