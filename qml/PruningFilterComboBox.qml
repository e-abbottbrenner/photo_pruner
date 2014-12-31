import QtQuick 2.4
import QtQuick.Controls 1.3

import PhotoPruner.Controllers 1.0
import PhotoPruner.Enums 1.0

ComboBox {
    model : ListModel {
        ListElement {
            text: "Show All"
            elementId: "showAll"
        }

        ListElement {
            text: "Show Unpruned"
            elementId: "showUnpruned"
        }

        ListElement {
            text: "Show Pruned"
            elementId: "showPruned"
        }
    }

    onActivated: {
        var elementId = model.get(index).elementId

        var pruningFilter

        if(elementId === "showAll") {
            pruningFilter = PruningFilters.ShowAll
        }
        else if(elementId === "showUnpruned") {
            pruningFilter = PruningFilters.ShowUnpruned
        }
        else if(elementId === "showPruned") {
            pruningFilter = PruningFilters.ShowPruned
        }

        appController.pruningFilter = pruningFilter
    }
}
