import QtQuick 2.4

// hacky shit that's only necessary because of https://bugreports.qt-project.org/browse/QTBUG-19507
Item {
    id: imageCacher

    // no more than 100 in cache to keep the element count down
    readonly property int maxImages: 100

    property var imagePaths: []

    property Image sourceImage

    Repeater {
        model: imageCacher.maxImages

        Image {
            visible: false
            asynchronous: true
            cache: true

            source: index < imageCacher.imagePaths.length? imageCacher.imagePaths[index] : ""

            onSourceChanged: console.log("source", source)
        }
    }

    function cacheImage(source) {
        var imagePaths = imageCacher.imagePaths

        if(imagePaths.indexOf(source) < 0)
        {
            imagePaths.push(source)
            console.log("added image")
            console.log(imagePaths)
        }

        while(imagePaths.length > imageCacher.maxImages) {
            imagePaths.shift()
        }

        imageCacher.imagePaths = imagePaths
    }

    Connections {
        target: imageCacher.sourceImage

        onSourceChanged: {
            imageCacher.cacheImage(imageCacher.sourceImage.source)
        }
    }
}
