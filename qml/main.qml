import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import PhotoPruner.AppModel 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
    color: "white"

    Actions {
        id: actions
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"

            MenuItem { action: actions.openAction }
            MenuItem { action: actions.saveAction }
            MenuItem { action: actions.saveAsAction }
            MenuItem { action: actions.importAction }
        }
    }

    Rectangle {
        anchors.fill: parent

        color: "blue"

        RowLayout {
            spacing: 0

            anchors.fill: parent

            Component {
                id: imageListDelegate

                Item {
                    width: 180; height: 40
                    Column {
                        Text { text: '<b>Path:</b> ' + display }
                    }

                    MouseArea {
                        anchors.fill: parent

                        onClicked: listView.currentIndex = index
                    }
                }

            }

            ListView {
                id: listView

                Layout.fillHeight: true
                Layout.fillWidth: true

                model: appModel.projectModel
                keyNavigationWraps: true
                delegate: imageListDelegate
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                focus: true

                onCurrentIndexChanged: appModel.determineCurrentImageUrl(currentIndex)
            }

            Rectangle {
                id: previewPanel

                color: "red"

                clip: true

                Layout.fillHeight: true
                Layout.fillWidth: true

                Flickable {
                    id: flickArea

                    contentWidth: image.width
                    contentHeight: image.height

                    interactive: true
                    clip: true

                    boundsBehavior: Flickable.StopAtBounds

                    anchors.fill: previewPanel

                    Connections {
                        target: image
                        onScaleChanged: {
                            var bounds = previewPanel.mapFromItem(image, image.x, image.y, image.width, image.height)

                            flickArea.leftMargin = Math.max(0, -bounds.x)
                            flickArea.topMargin = Math.max(0, -bounds.y)

                            flickArea.contentWidth = Math.max(image.width, bounds.width - flickArea.leftMargin)
                            flickArea.contentHeight = Math.max(image.height, bounds.height - flickArea.topMargin)
                        }
                    }

                    MouseArea {
                        id: mouseArea

                        // keep the mouse area over the flick area's content zone so it always works
                        x: flickArea.contentX
                        y: flickArea.contentY
                        width: flickArea.contentWidth
                        height: flickArea.contentHeight

                        onWheel: {
                            // compute this before rescaling so we have correct center point
                            // note: mappedPoint should retain its position in screen space
                            var mappedPoint = mapToItem(image, wheel.x, wheel.y)

                            var exp = wheel.angleDelta.y / 15.0
                            // rescale
                            image.scaleOriginX = mappedPoint.x
                            image.scaleOriginY = mappedPoint.y
                            image.scale = image.scale * Math.pow(1.05, exp)

                            console.log(image.scale)
                        }
                    }

                    Image {
                        id: image

                        asynchronous: true

                        width: previewPanel.width
                        height: previewPanel.height

                        fillMode: Image.PreserveAspectFit

                        source: appModel.currentImageUrl

                        property real scale: 1.0
                        property real scaleOriginX: 0
                        property real scaleOriginY: 0

                        property Translate shiftCenterTransform: Translate {
                            x: -image.scaleOriginX
                            y: -image.scaleOriginY
                        }

                        property Scale scalingTransform: Scale {
                            origin.x: 0
                            origin.y: 0
                            xScale: image.scale
                            yScale: image.scale
                        }

                        property Translate shiftBackTransform: Translate {
                            x: image.scaleOriginX
                            y: image.scaleOriginY
                        }

                        transform: [shiftCenterTransform, scalingTransform, shiftBackTransform]

                        onSourceChanged: {
                            image.scale = 1.0
                            image.scaleOriginX = 0;
                            image.scaleOriginY = 0;
                            console.log("source changed to" + source)
                        }
                    }
                }
            }
        }
    }
}
