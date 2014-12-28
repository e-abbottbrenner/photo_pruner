import QtQuick 2.3
import QtQuick.Controls 1.2

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

    ListView {
        width: 200; height: 250

        anchors.fill: parent

        model: appModel.projectModel
        delegate: Text { text: "path:" + display}
    }
}
