import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import PhotoPruner.Controllers 1.0

Dialog {
    property var tags: imageController.tags

    Column {
        Row {
            TextField {
                id: newTagText
            }

            Button {
                text: "Add Tag"

                onClicked: {
                    imageController.addTag(newTagText.text)
                }
            }
        }

        Row {
            ListView {
                id: tagRemovalComboBox
                model: tags

                width:200
                height: 200

                delegate: Component {
                    Row {
                        Text {
                            text: modelData
                        }

                        Button {
                            text: "x"

                            onClicked: imageController.removeTag(modelData)
                        }
                    }
                }
            }
        }
    }
}
