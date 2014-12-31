import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import PhotoPruner.Controllers 1.0

Dialog {
    property list<string> tags

    ColumnLayout {
        RowLayout {
            TextField {
                id: newTagText
            }

            Button {
                text: "Add Tag"

                onClicked: {
                    // TODO call controller
//                    imageController.
                }
            }
        }

        RowLayout {
            ComboBox {
                id: tagRemovalComboBox
                model: tags
            }

            Button {
                text: "Remove Tag"

                onClicked:{
                    // TODO: call controller
//                    imageController.
                }
            }
        }


    }
}
