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
        var elementId = model.get(currentIndex).elementId

        if(elementId === "showAll") {
            appController.pruningFilter = PruningFilters.ShowAll
        }
        else if(elementId === "showUnpruned") {
            appController.pruningFilter = PruningFilters.ShowUnpruned
        }
        else if(elementId === "showPruned") {
            appController.pruningFilter = PruningFilters.ShowPruned
        }
    }
}
