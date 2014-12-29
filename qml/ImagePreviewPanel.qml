import QtQuick 2.3

Rectangle {
    id: previewPanel

    property string imageSource

    Flickable {
        id: flickArea

        contentWidth: image.width * image.scale
        contentHeight: image.height * image.scale

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
                // current point the mouse is over in image coords
                // note: mappedPoint should retain its position in screen space
                var mappedPoint = mapToItem(image, wheel.x, wheel.y)

                // left and top edge in flick area coords
                var leftEdge = flickArea.contentX
                var topEdge = flickArea.contentY

                // the distance from the edges in flickArea coords (multiply by scale to go from image coords to flick area coords)
                var scaledDistLeft = mappedPoint.x * image.scale - leftEdge
                var scaledDistTop = mappedPoint.y * image.scale - topEdge

                var exp = wheel.angleDelta.y / 15.0

                // new scale with non-nan limits, nans are bad
                var newScale = Math.max(1, Math.min(100000, image.scale * Math.pow(1.05, exp)))

                // the final location of the mapped point in flick area coords
                var mappedPointDestX = mappedPoint.x * newScale
                var mappedPointDestY = mappedPoint.y * newScale

                // the new contentX/contentY positions in flick area coords, computed by taking the location of the mapped point
                // and subtracting the desired distance between it and the new contentx/contenty positions
                // this desired distance is the same as the old distance because we don't want it to move on the screen
                var newContentX = mappedPointDestX - scaledDistLeft
                var newContentY = mappedPointDestY - scaledDistTop

                // rescale
                image.scale = newScale

                flickArea.contentX = newContentX
                flickArea.contentY = newContentY

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

            source: previewPanel.imageSource

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
