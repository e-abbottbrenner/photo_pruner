import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

import PhotoPruner.AppModel 1.0

Item {

    //    Action {
    //        id: saveAction

    //        text: "&Save Project"
    //        shortcut: StandardKey.Save

    //        onTriggered: {}
    //    }

    //    Action {
    //        id: saveAsAction

    //        text: "Save Project As..."
    //        shortcut: StandardKey.SaveAs

    //        onTriggered: {}
    //    }




    property Action openAction: Action {
        text: "&Open Project"
        shortcut: StandardKey.Open

        property FileDialog openDialog: FileDialog {
            nameFilters: ["Json files (*.json)"]

            onAccepted: appModel.openProject(fileUrl)
        }

        onTriggered: openDialog.open()
    }
}
