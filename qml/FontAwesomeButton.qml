import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

Button {
    property real fontSize: 12
    property bool borderless: false

    property color unpressedColor: "black"
    property color pressedColor: "white"

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
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
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

                color: control.borderless? (control.pressed? control.pressedColor : control.unpressedColor) : control.unpressedColor
            }
        }
    }
}
