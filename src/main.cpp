#include "AppModel.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    AppModel *appModel = new AppModel(&app);

    qRegisterMetaType<QAbstractItemModel*>();
    qmlRegisterType<AppModel>("photopruner.appmodel", 1, 0, "AppModel");

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("appModel", appModel);

    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
