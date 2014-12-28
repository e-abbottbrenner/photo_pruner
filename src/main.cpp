#include "AppModel.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // register types to make the property system happy
    qRegisterMetaType<QAbstractItemModel*>();

    // register types to make qml happy
    qmlRegisterType<AppModel>("PhotoPruner.AppModel", 1, 0, "AppModel");

    QQmlApplicationEngine engine;

    AppModel *appModel = new AppModel(&app);

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("appModel", appModel);

    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
