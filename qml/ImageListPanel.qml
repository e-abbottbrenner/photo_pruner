import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

import PhotoPruner.Controllers 1.0

Rectangle {
    width: filterControlsRow.width

    property int minimumWidth: filterControlsRow.width + mainColumn.anchors.leftMargin + mainColumn.anchors.rightMargin

    property url currentImageUrl: listView.currentItem? listView.currentItem.sourceModel?
                                                            listView.currentItem.sourceModel.sourceUrl : "" : ""

    property string currentImagePath:  listView.currentItem? listView.currentItem.sourceModel?
                                                                 listView.currentItem.sourceModel.sourcePath : "" : ""

    color: "#c8c8c8"

    ColumnLayout {
        id: mainColumn

        anchors.fill: parent
        anchors.margins: 5

        Row {
            id: filterControlsRow

            spacing: 10

            Column {
                id: pruningFilterColumn

                spacing: 5

                Text {
                    text: "Pruning filter"
                }

                PruningFilterComboBox {
                    id: pruningFilterCombo
                }
            }

            Column {
                id: tagFilterColumn

                spacing: 5

                Text {
                    text: "Tag filter"
                }

                TextField {
                    id: tagFilterField

                    onTextChanged: appController.setTagFilter(text)
                }
            }
        }


        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            contentItem: listView

            frameVisible: false

            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

            focus: true

            Keys.onRightPressed: listView.incrementCurrentIndex()
            Keys.onLeftPressed: listView.decrementCurrentIndex()
            Keys.onUpPressed: listView.decrementCurrentIndex()
            Keys.onDownPressed: listView.incrementCurrentIndex()

            ListView {
                id: listView

                clip: true

                spacing: 2

                boundsBehavior: Flickable.StopAtBounds

                model: appController.projectModel
                keyNavigationWraps: true

                delegate: Component {
                    Item {
                        property variant sourceModel: model

                        width: listView.width
                        height: 20

                        Rectangle {
                            anchors.fill: parent

                            color: "transparent"
                            border.color: "#c0c0c0"
                            border.width: 1

                            radius: 5

                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                color: pruned? "red" : "black"
                                text: display
                            }
                        }

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                listView.currentIndex = index
                            }
                        }
                    }
                }

                highlightMoveDuration: 0
                highlight: Rectangle { color: "#b0b0d8"; radius: 5 }
                focus: true
            }
        }
    }

    onCurrentImagePathChanged: {
        imageController.setImage(currentImagePath)
    }
}
