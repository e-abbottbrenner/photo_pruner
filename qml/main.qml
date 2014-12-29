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

                    contentWidth: image.width * image.scale
                    contentHeight: image.height * image.scale

                    interactive: true
                    clip: true

                    boundsBehavior: Flickable.StopAtBounds

                    anchors.fill: previewPanel

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

                            // left and top edge in image coords
                            var leftEdge = flickArea.contentX / image.scale
                            var topEdge = flickArea.contentY / image.scale

                            // the distance from the edges in flickArea coords
                            var scaledDistLeft = (mappedPoint.x - leftEdge) * image.scale
                            var scaledDistTop = (mappedPoint.y - topEdge) * image.scale

                            var exp = wheel.angleDelta.y / 15.0

                            // non-nan limits, nans are bad
                            var newScale = Math.max(1, Math.min(100000, image.scale * Math.pow(1.05, exp)))

                            var mappedPointDestX = mappedPoint.x * newScale
                            var mappedPointDestY = mappedPoint.y * newScale

                            var scaledContentX = mappedPointDestX - scaledDistLeft
                            var scaledContentY = mappedPointDestY - scaledDistTop

                            // rescale
                            image.scale = newScale

                            flickArea.contentX = scaledContentX
                            flickArea.contentY = scaledContentY

                            // just in case
                            flickArea.returnToBounds()
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

                        property Scale scalingTransform: Scale {
                            origin.x: 0
                            origin.y: 0
                            xScale: image.scale
                            yScale: image.scale
                        }

                        transform: scalingTransform

                        onSourceChanged: {
                            image.scale = 1.0
                            console.log("source changed to" + source)
                        }
                    }
                }
            }
        }
    }
}
