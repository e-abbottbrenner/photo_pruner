import QtQuick 2.4
import QtQuick.Layouts 1.1

import PhotoPruner.Controllers 1.0

Rectangle {
    id: previewPanel

    property string imageSource

    color: "#a8a8a8"

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
                var mappedPoint = mapToItem(imageWrapper, wheel.x, wheel.y)

                // left and top edge in flick area coords
                var leftEdge = flickArea.contentX
                var topEdge = flickArea.contentY

                // the distance from the edges in flickArea coords (multiply by scale to go from imageWrapper coords to flick area coords)
                var scaledDistLeft = mappedPoint.x * imageWrapper.scale - leftEdge
                var scaledDistTop = mappedPoint.y * imageWrapper.scale - topEdge

                var exp = wheel.angleDelta.y / 15.0

                // new scale with non-nan limits, nans are bad
                var newScale = Math.max(1, Math.min(100000, imageWrapper.scale * Math.pow(1.05, exp)))

                // the final location of the mapped point in flick area coords
                var mappedPointDestX = mappedPoint.x * newScale
                var mappedPointDestY = mappedPoint.y * newScale

                // the new contentX/contentY positions in flick area coords, computed by taking the location of the mapped point
                // and subtracting the desired distance between it and the new contentx/contenty positions
                // this desired distance is the same as the old distance because we don't want it to move on the screen
                var newContentX = mappedPointDestX - scaledDistLeft
                var newContentY = mappedPointDestY - scaledDistTop

                // rescale
                imageWrapper.scale = newScale

                flickArea.contentX = newContentX
                flickArea.contentY = newContentY

                // just in case
                flickArea.returnToBounds()
            }
        }

        Item {
            id: imageWrapper

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

                anchors.fill: parent

                asynchronous: true

                fillMode: Image.PreserveAspectFit

                source: previewPanel.imageSource

                rotation: imageController.rotation

                onSourceChanged: {
                    imageWrapper.scale = 1.0
                }
            }
        }
    }
}
