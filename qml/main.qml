import QtQuick 2.4
import QtQuick.Controls 1.3
import photopruner.appmodel 1.0

ApplicationWindow
{
    id: mainWindow
    visible: true
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
    color: "white"

//    AppModel {
//        id: appModel
//    }

    ListView {
        width: 200; height: 250

//        color: blue
        visible: true

        anchors.fill: parent

        model: appModel.projectModel
        delegate: Text { text: "path:" + display}
    }
}
