import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

Button {
    property real fontSize: 12
    property bool borderless: false

    property color unpressedColor: "#282828"
    property color pressedColor: unpressedColor
    property color disabledColor: "#a0a0a0"
    property color borderColor: "#808080"

    FontLoader {
        id: fontAwesome
        source: "qrc:/fonts/fontawesome-webfont.ttf"
    }

    FontMetrics {
        id: fontAwesomeMetrics

        font.family: fontAwesome.name
        font.pointSize: fontSize
    }

    style: ButtonStyle {
        Component {
            id: borderRect

            Rectangle {
                implicitWidth:  fontAwesomeMetrics.boundingRect(text).width
                implicitHeight:  fontAwesomeMetrics.boundingRect(text).height
                border.color: control.enabled? borderColor : disabledColor
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#dddddd" : "#ffffff" }
                    GradientStop { position: 1 ; color: control.pressed ? "#bbbbcc" : "#ddddff" }
                }

                Behavior on border.color {
                    PropertyAnimation { duration: 200 }
                }
            }
        }

        background: control.borderless? null : borderRect

        label: Component {
            Text {
                text: control.text

                width:  fontAwesomeMetrics.boundingRect(text).width
                height:  fontAwesomeMetrics.boundingRect(text).height

                font.family: fontAwesome.name
                font.pointSize: fontSize

                color: control.enabled? (control.pressed? control.pressedColor : control.unpressedColor)
                                      : control.disabledColor

                Behavior on color {
                    PropertyAnimation { duration: 200 }
                }
            }
        }
    }
}
