import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

import PhotoPruner.Controllers 1.0

Item {
    function autosave() {
        if(appController.projectUrl.toString().length > 0) {
            // do this directly instead of through the action to prevent any chance of it getting queued
            console.log("autosaving")
            appController.saveProject(appController.projectUrl)
        }
    }

    property Action newAction: Action {
        text: "&New Project"
        shortcut: StandardKey.New

        onTriggered: {
            autosave()
            appController.newProject()
        }
    }

    property Action saveAction: Action {
        text: "&Save Project"
        shortcut: StandardKey.Save

        onTriggered: {
            appController.projectUrl.toString().length > 0? appController.saveProject(appController.projectUrl) : saveAsAction.trigger()
        }
    }

    property Action saveAsAction: Action {
        text: "Save Project As..."
        shortcut: StandardKey.SaveAs

        property FileDialog saveAsDialog: FileDialog {
            title: "Save As..."
            selectExisting: false
            nameFilters: ["Json files (*.json)"]

            onAccepted: appController.saveProject(fileUrl)
        }

        onTriggered: {
            saveAsDialog.open()
        }
    }

    property Action openAction: Action {
        text: "&Open Project"
        shortcut: StandardKey.Open

        property FileDialog openDialog: FileDialog {
            title: "Open..."
            nameFilters: ["Json files (*.json)"]

            onAccepted: appController.openProject(fileUrl)
        }

        onTriggered: {
            autosave()
            openDialog.open()
        }
    }

    property Action importAction: Action {
        text: "&Import Images"
        shortcut: "Ctrl+I"

        property FileDialog importDialog: FileDialog {
            title: "Import Images..."
            selectMultiple: true
            nameFilters: ["Jpg files (*.jpg)", "Jpeg files (*.jpeg)", "Png files (*.png)"]

            onAccepted: projectController.importImages(fileUrls)
        }

        onTriggered: importDialog.open()
    }

    property Action deletePrunedImagesAction : Action {
        text: "Delete Pruned Images"

        property MessageDialog confirmDeletionDialog : MessageDialog {
            title: "Delete?"
            text: "This will premanently delete all pruned images from your file system.  Do you want to continue?"

            standardButtons: StandardButton.Yes | StandardButton.No

            onYes: projectController.deletePrunedImages()
        }

        onTriggered: {
            confirmDeletionDialog.open()
        }
    }

    property Action flagForPruningAction: Action {
        text: "&Flag Image for Pruning"
        shortcut: "Ctrl+D"

        enabled: imageController.hasImage && !imageController.willBePruned

        onTriggered: imageController.willBePruned = true
    }

    property Action unflagForPruningAction: Action {
        text: "&Unflag Image For Pruning"
        shortcut: "Ctrl+U"

        enabled: imageController.hasImage && imageController.willBePruned

        onTriggered: imageController.willBePruned = false
    }

    property Action removeFromProjectAction: Action {
        text:"&Remove Image"

        enabled: imageController.hasImage

        onTriggered: imageController.removeFromProject()
    }

    property Action editTagsAction: Action {
        text: "&Edit Tags"
        shortcut: "Ctrl+T"

        enabled: imageController.hasImage

        property TagEditorDialog tagEditor: TagEditorDialog {}

        onTriggered: tagEditor.open()
    }

    property Action quitAction : Action {
        text: "&Quit"

        shortcut: "Ctrl+Q"

        onTriggered: {
            autosave()
            Qt.quit()
        }
    }
}
