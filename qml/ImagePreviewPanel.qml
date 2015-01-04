import QtQuick 2.4
import QtQuick.Layouts 1.1

import PhotoPruner.Controllers 1.0

Rectangle {
    id: previewPanel

    property string imageSource

    color: "#a8a8a8"

    function resetZoom() {
        zoomOnPoint(1.0, imageWrapper.centerPoint)
    }

    property int standardZoomExp: 2

    function zoomIn() {
        var newScale = Math.max(1, Math.min(100000, imageWrapper.scale * Math.pow(1.05, standardZoomExp)))

        zoomOnPoint(newScale, imageWrapper.centerPoint)
    }

    function zoomOut() {
        var newScale = Math.max(1, Math.min(100000, imageWrapper.scale * Math.pow(1.05, -standardZoomExp)))

        zoomOnPoint(newScale, imageWrapper.centerPoint)
    }

    function zoomOnPoint(newScale, zoomPoint) {

        // left and top edge in flick area coords
        var leftEdge = flickArea.contentX
        var topEdge = flickArea.contentY

        // the distance from the edges in flickArea coords (multiply by scale to go from imageWrapper coords to flick area coords)
        var scaledDistLeft = zoomPoint.x * imageWrapper.scale - leftEdge
        var scaledDistTop = zoomPoint.y * imageWrapper.scale - topEdge

        // the final location of the mapped point in flick area coords
        var zoomPointDestX = zoomPoint.x * newScale
        var zoomPointDestY = zoomPoint.y * newScale

        // the new contentX/contentY positions in flick area coords, computed by taking the location of the mapped point
        // and subtracting the desired distance between it and the new contentx/contenty positions
        // this desired distance is the same as the old distance because we don't want it to move on the screen
        var newContentX = zoomPointDestX - scaledDistLeft
        var newContentY = zoomPointDestY - scaledDistTop

        // rescale
        imageWrapper.scale = newScale

        flickArea.contentX = newContentX
        flickArea.contentY = newContentY

        // just in case
        flickArea.returnToBounds()
    }

    function setRotationDirectionClockwise() {
        image.rotationDirection = RotationAnimation.Clockwise
    }

    function setRotationDirectionCounterClockwise() {
        image.rotationDirection = RotationAnimation.Counterclockwise
    }

    Connections {
        target: appController

        // reset the scale if the project changes
        onProjectUrlChanged: imageWrapper.scale = 1.0
    }

    Flickable {
        id: flickArea

        contentWidth: imageWrapper.width * imageWrapper.scale
        contentHeight: imageWrapper.height * imageWrapper.scale

        interactive: true
        clip: true

        boundsBehavior: Flickable.StopAtBounds

        maximumFlickVelocity: 0

        anchors.fill: previewPanel

        MouseArea {
            id: mouseArea

            // keep the mouse area over the flick area's content zone so it always works
            x: flickArea.contentX
            y: flickArea.contentY
            width: flickArea.contentWidth
            height: flickArea.contentHeight

            onWheel: {
                // current point the mouse is over in imageWrapper coords
                // note: mappedPoint should retain its position in screen space
                if(imageController.hasImage)
                {
                    var mappedPoint = mapToItem(imageWrapper, wheel.x, wheel.y)

                    var exp = wheel.angleDelta.y / 15.0

                    // new scale with non-nan limits, nans are bad
                    var newScale = Math.max(1, Math.min(100000, imageWrapper.scale * Math.pow(1.05, exp)))

                    previewPanel.zoomOnPoint(newScale, mappedPoint)
                }

                wheel.accepted = true
            }
        }

        Item {
            id: imageWrapper

            property point centerPoint: Qt.point(x + width / 2.0, y + height / 2.0)

            width: previewPanel.width
            height: previewPanel.height

            property real scale: 1.0

            property Scale scalingTransform: Scale {
                origin.x: 0
                origin.y: 0
                xScale: imageWrapper.scale
                yScale: imageWrapper.scale
            }

            transform: scalingTransform

            Image {
                id: image

                anchors.centerIn: parent

                width: sourceSize.width? sourceSize.width : previewPanel.width
                height: sourceSize.height? sourceSize.height : previewPanel.height

                asynchronous: true

                fillMode: Image.PreserveAspectFit

                source: previewPanel.imageSource

                rotation: imageController.rotation

                property var rotationDirection

                Behavior on rotation {
                    RotationAnimation {
                        duration: 200
                        direction: image.rotationDirection
                    }
                }

                // we're guaranteed an even multiple of 90
                property real rotatedWidth: imageController.rotation % 180 == 0? width: height
                property real rotatedHeight: imageController.rotation % 180 == 0? height: width

                // adjusts the scale for when the width and height flip from the rotation
                property real rotationFitScale: Math.min(width / rotatedWidth, height / rotatedHeight)

                // fits the image appropriately inside the parent item
                property real initialFitScale: Math.min(parent.width / width, parent.height / height)

                scale: initialFitScale * rotationFitScale
            }
        }
    }
}
