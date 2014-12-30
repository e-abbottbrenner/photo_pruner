#include "AppController.h"
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
    qmlRegisterType<AppController>("PhotoPruner.AppController", 1, 0, "AppController");

    QQmlApplicationEngine engine;

    AppModelPtr appModel = AppModel::createAppModel();

    AppController *appController = new AppController(&app);
    appController->setAppModel(appModel);

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("appController", appController);

    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
