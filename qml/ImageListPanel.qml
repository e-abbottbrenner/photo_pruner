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
            id: imageListScrollView

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

                boundsBehavior: Flickable.StopAtBounds

                model: appController.projectModel
                keyNavigationWraps: true

                delegate: Component {
                    Item {
                        id: imageDelegate

                        property variant sourceModel: model

                        width: listView.width
                        height: 24

                        Rectangle {
                            anchors.fill: parent
                            anchors.topMargin: 2
                            anchors.bottomMargin: 2

                            color: imageDelegate.ListView.isCurrentItem? "#b0b0d8" : "transparent"
                            border.color: "#c0c0c0"
                            border.width: 1

                            radius: 5

                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                color: pruned? "red" : "black"
                                text: display

                                Behavior on color {
                                    PropertyAnimation { duration: 400; }
                                }
                            }
                        }

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                listView.currentIndex = index
                                imageListScrollView.forceActiveFocus()

                            }
                        }
                    }
                }

                highlightMoveDuration: 0
                focus: false

                readonly property int fadeDuration: 500
                readonly property int moveDuration: 250

                populate: Transition {
                    NumberAnimation {
                        properties: "opacity"
                        from: 0.0
                        to: 1.0
                        easing.type: Easing.InQuad
                        duration: listView.fadeDuration
                    }
                }


                add: Transition {
                    NumberAnimation {
                        properties: "opacity"
                        from: 0.0
                        to: 1.0
                        easing.type: Easing.InQuad
                        duration: listView.fadeDuration
                    }
                }

                remove: Transition {
                    NumberAnimation {
                        properties: "opacity"
                        from: 1.0
                        to: 0.0
                        easing.type: Easing.OutQuart
                        duration: listView.fadeDuration
                    }
                }

                addDisplaced: Transition {
                    NumberAnimation { properties: "x,y"; duration: listView.moveDuration }
                }

                removeDisplaced: Transition {
                    NumberAnimation { properties: "x,y"; duration: listView.moveDuration }
                }
            }
        }
    }

    onCurrentImagePathChanged: {
        imageController.setImage(currentImagePath)
    }
}
