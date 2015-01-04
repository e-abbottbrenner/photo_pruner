import QtQuick 2.4

// hacky shit that's only necessary because of https://bugreports.qt-project.org/browse/QTBUG-19507
Item {
    id: imageCacher

    // no more than 100 in cache to keep the element count down
    readonly property int maxImages: 100
    readonly property int maxMegaPixels: 500

    property var imagePaths: []
    property var imagePathPriorities: []
    // will mirror image paths
    property var imageMegapixels: []

    property real totalMegapixels: 0

    property Image sourceImage

    Repeater {
        model: imageCacher.maxImages

        Image {
            visible: false
            asynchronous: true
            cache: true

            source: index < imageCacher.imagePaths.length? imageCacher.imagePaths[index] : ""
        }
    }

    function cacheImage(source, sourceMegapixels) {
        var imagePaths = imageCacher.imagePaths
        var imagePathPriorities = imageCacher.imagePathPriorities
        var imageMegapixels = imageCacher.imageMegapixels
        var totalMegapixels = imageCacher.totalMegapixels

        // IMPORTANT: if an old image shifts forward in list indices, it will be lost
        // this is because when images are shifted, the repeater's cache slots are updated in order
        // so if an image moves forward in the list, the slot that was holding it will be changed to a different image
        // and it will be gone by the time the slot that will hold it tries to set it
        // but if an image moves backward in the list, the slot that was holding it is updated after the dest slot
        // for this reason we only ever push to the end of image paths and keep a separate list to track ordering

        var priorityIndex = imagePathPriorities.indexOf(source)

        if(priorityIndex < 0) {
            // this image wasn't used before, push it to end of both lists
            imagePaths.push(source)
            imagePathPriorities.push(source)
            imageMegapixels.push(sourceMegapixels)

            totalMegapixels += sourceMegapixels
        } else {
            // it already exists, so just update the priority
            imagePathPriorities.splice(priorityIndex, 1)

            // move it to the highest priority
            imagePathPriorities.push(source)
        }

        while(imagePaths.length > 0 && // paranoia check in case total megapixels gets wonky
              (imagePaths.length > imageCacher.maxImages || totalMegapixels > imageCacher.maxMegaPixels)) {
            // get the lowest priority image(also remove it from the priorities list)
            var removedPath = imagePathPriorities.shift()

            var removedPathIndex = imagePaths.indexOf(removedPath)

            // and remove it from the main list, note  this can only shift elements down
            imagePaths.splice(removedPathIndex, 1)

            // get the number of megapixels removed
            var removedMegapixels = imageMegapixels[removedPathIndex]
            // remove the log of those megapixels
            imageMegapixels.splice(removedPathIndex, 1)

            totalMegapixels -= removedMegapixels
        }

        imageCacher.imagePaths = imagePaths
        imageCacher.imagePathPriorities = imagePathPriorities
        imageCacher.imageMegapixels = imageMegapixels
        imageCacher.totalMegapixels = totalMegapixels
    }

    Connections {
        target: imageCacher.sourceImage

        onStatusChanged: {
            if(imageCacher.sourceImage.status == Image.Ready)
            {
                // trigger this off the ready status so both source and sourceSize are available
                var source = imageCacher.sourceImage.source
                var sourceMegapixels = (imageCacher.sourceImage.sourceSize.width * imageCacher.sourceImage.sourceSize.height) / 1000000.0
                imageCacher.cacheImage(source, sourceMegapixels)
            }
        }
    }
}
