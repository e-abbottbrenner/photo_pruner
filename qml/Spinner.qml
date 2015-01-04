import QtQuick 2.4

Item {
    id: spinner

    property int spinnerSize
    property real spinTime

    property color color: "black"
    property color outlineColor: "transparent"

    width: childrenRect.width
    height: childrenRect.height

    FontLoader {
        id: fontAwesome
        source: "qrc:/fonts/fontawesome-webfont.ttf"
    }

    Text {
        font.family: fontAwesome.name
        font.pixelSize: spinnerSize

        style: Text.Outline
        color: spinner.color
        styleColor: spinner.outlineColor

        text: "\uf110"

        SequentialAnimation on rotation {
            id: spinnerAnimation

            loops: Animation.Infinite

            property int pauseDuration: spinner.spinTime / 8

            PauseAnimation {
                duration: spinnerAnimation.pauseDuration
            }

            RotationAnimation {
                from: 0
                to: 45

                duration: 0

                direction: RotationAnimation.Clockwise
            }

            PauseAnimation {
                duration: spinnerAnimation.pauseDuration
            }

            RotationAnimation {
                from: 45
                to: 90

                duration: 0

                direction: RotationAnimation.Clockwise
            }

            PauseAnimation {
                duration: spinnerAnimation.pauseDuration
            }

            RotationAnimation {
                from: 90
                to: 135

                duration: 0

                direction: RotationAnimation.Clockwise
            }

            PauseAnimation {
                duration: spinnerAnimation.pauseDuration
            }

            RotationAnimation {
                from: 135
                to: 180

                duration: 0

                direction: RotationAnimation.Clockwise
            }

            PauseAnimation {
                duration: spinnerAnimation.pauseDuration
            }
            RotationAnimation {
                from: 180
                to: 225

                duration: 0

                direction: RotationAnimation.Clockwise
            }

            PauseAnimation {
                duration: spinnerAnimation.pauseDuration
            }

            RotationAnimation {
                from: 225
                to: 270

                duration: 0

                direction: RotationAnimation.Clockwise
            }

            PauseAnimation {
                duration: spinnerAnimation.pauseDuration
            }
            RotationAnimation {
                from: 270
                to: 315

                duration: 0

                direction: RotationAnimation.Clockwise
            }

            PauseAnimation {
                duration: spinnerAnimation.pauseDuration
            }

            RotationAnimation {
                from: 315
                to: 360

                duration: 0

                direction: RotationAnimation.Clockwise
            }
        }
    }
}
