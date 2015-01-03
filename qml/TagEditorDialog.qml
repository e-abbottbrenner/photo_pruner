import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import PhotoPruner.Controllers 1.0

Dialog {
    property var tags: imageController.tags

    width: 240
    height: 240

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

                    anchors.verticalCenter: parent.verticalCenter
                }

                Button {
                    text: "Add Tag"

                    enabled: newTagText.text.length > 0

                    height: newTagText.height

                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: {
                        imageController.addTag(newTagText.text)
                    }
                }
            }

            ListView {
                id: tagList
                model: tags

                Layout.fillHeight: true
                Layout.fillWidth: true

                spacing: 5
                clip: true

                boundsBehavior: Flickable.StopAtBounds

                delegate: Component {
                    Item {
                        width: tagList.width
                        height: 20

                        Rectangle {
                            anchors.fill: parent
                            color: "#c0c0c0"
                            radius: 5

                            property real fontSize: 10

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
