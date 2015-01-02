import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

import PhotoPruner.Controllers 1.0

// qml equivalent to "wrap it in widget", "wrap it in an item!"
Item {
    Component {
        id: imageListDelegate

        Item {
            property variant sourceModel: model

            width: 180; height: 40
            Column {
                Text { text: '<b>Path:</b> ' + display }
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    listView.currentIndex = index
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Row {
            PruningFilterComboBox {
                id: pruningFilterCombo
            }

            TextField {
                id: tagFilterField

                onTextChanged: appController.setTagFilter(text)
            }
        }

        ListView {
            id: listView

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: appController.projectModel
            keyNavigationWraps: true
            delegate: imageListDelegate
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true

            onCurrentItemChanged: {
                imageController.setImage(currentItem.sourceModel.sourcePath)
            }
        }
    }

    property url currentImageUrl: listView.currentItem? listView.currentItem.sourceModel?
                                                            listView.currentItem.sourceModel.sourceUrl : "" : ""
}
