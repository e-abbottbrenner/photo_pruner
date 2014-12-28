import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

import PhotoPruner.AppModel 1.0

Item {
    property Action saveAction: Action {
        text: "&Save Project"
        shortcut: StandardKey.Save

        onTriggered: appModel.saveProject(appModel.projectUrl)
    }

    property Action saveAsAction: Action {
        text: "Save Project As..."
        shortcut: StandardKey.SaveAs

        property FileDialog saveAsDialog: FileDialog {
            title: "Save As..."
            selectExisting: false
            nameFilters: ["Json files (*.json)"]

            onAccepted: appModel.saveProject(fileUrl)
        }

        onTriggered: saveAsDialog.open()
    }

    property Action openAction: Action {
        text: "&Open Project"
        shortcut: StandardKey.Open

        property FileDialog openDialog: FileDialog {
            title: "Open..."
            nameFilters: ["Json files (*.json)"]

            onAccepted: appModel.openProject(fileUrl)
        }

        onTriggered: openDialog.open()
    }
}
