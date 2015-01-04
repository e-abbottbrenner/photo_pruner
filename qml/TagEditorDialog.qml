import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import PhotoPruner.Controllers 1.0

Dialog {
    id: tagEditorDialog

    property var tags: imageController.tags

    width: 240
    height: 240

    onVisibleChanged: {
        newTagText.forceActiveFocus()
    }

    contentItem: Rectangle {
        color: "#d8d8d8"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 10

            RowLayout {
                Layout.fillHeight: false

                TextField {
                    id: newTagText

                    Layout.fillWidth: true
                    Layout.fillHeight: false

                    focus: true

                    anchors.verticalCenter: parent.verticalCenter

                    Keys.onEnterPressed: addTagButton.addTag()
                    Keys.onReturnPressed: addTagButton.addTag()
                    Keys.onEscapePressed: tagEditorDialog.close()
                }

                Button {
                    id: addTagButton

                    text: "Add Tag"

                    enabled: newTagText.text.length > 0

                    height: newTagText.height

                    anchors.verticalCenter: parent.verticalCenter

                    function addTag() {
                        if(tags.indexOf(newTagText.text) >= 0) {
                            tagList.currentItem.blink()
                        } else {
                            imageController.addTag(newTagText.text)
                            newTagText.text = ""
                        }
                    }

                    onClicked: {
                        addTag()
                    }
                }
            }

            ListView {
                id: tagList
                model: tags

                currentIndex: tags.indexOf(newTagText.text)

                Layout.fillHeight: true
                Layout.fillWidth: true

                spacing: 5
                clip: true

                boundsBehavior: Flickable.StopAtBounds

                delegate: Component {
                    Item {
                        id: tagDelegate

                        width: tagList.width
                        height: 20

                        function blink() {
                            blinkAnimation.start()
                        }

                        Rectangle {
                            id: tagRect

                            anchors.fill: parent

                            readonly property color highlightColor: "#ffc000"
                            readonly property color normalColor: "#c0c0c0"

                            color: tagDelegate.ListView.isCurrentItem? highlightColor : normalColor
                            radius: 5

                            property real fontSize: 10

                            Behavior on color {
                                ColorAnimation { duration: 1000; easing.type: Easing.InQuad }
                            }

                            SequentialAnimation on color {
                                id: blinkAnimation

                                running: false

                                readonly property int totalDuration: 2000
                                readonly property int totalBlinks: 2

                                loops: totalBlinks

                                ColorAnimation {
                                    from: tagRect.highlightColor
                                    to: tagRect.normalColor

                                    easing.type: Easing.InOutQuad

                                    duration: blinkAnimation.totalDuration / (2 * blinkAnimation.totalBlinks)
                                }

                                ColorAnimation {
                                    from: tagRect.normalColor
                                    to: tagRect.highlightColor

                                    easing.type: Easing.InOutQuad

                                    duration: blinkAnimation.totalDuration / (2 * blinkAnimation.totalBlinks)
                                }
                            }

                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 5

                                text: modelData
                                font.pointSize: parent.fontSize
                            }

                            FontAwesomeButton {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 5

                                // fa-times
                                text: "\uf00d"
                                borderless: true

                                pressedColor: "white"
                                unpressedColor: "black"

                                fontSize: parent.fontSize

                                onClicked: imageController.removeTag(modelData)
                            }
                        }
                    }
                }
            }

            Button {
                text: "Ok"

                Layout.alignment: Qt.AlignRight

                onClicked: close()
            }
        }
    }
}
