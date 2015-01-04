import QtQuick 2.4

ListView {
    id: listView

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

