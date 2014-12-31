#include "AppController.h"
#include "AppModel.h"
#include "ImageController.h"
#include "ProjectController.h"
#include "PruningFilters.h"

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
    qmlRegisterType<AppController>("PhotoPruner.Controllers", 1, 0, "AppController");
    qmlRegisterType<ImageController>("PhotoPruner.Controllers", 1, 0, "ImageController");
    qmlRegisterType<ProjectController>("PhotoPruner.Controllers", 1, 0, "ProjectController");

    qmlRegisterType<PruningFilters>("PhotoPruner.Enums", 1, 0, "PruningFilters");

    QQmlApplicationEngine engine;

    AppModelPtr appModel = AppModel::createAppModel();

    AppController *appController = new AppController(&app);
    ImageController *imageController = new ImageController(&app);
    ProjectController *projectController = new ProjectController(&app);

    appController->setAppModel(appModel);
    imageController->setAppModel(appModel);
    projectController->setAppModel(appModel);

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("appController", appController);
    context->setContextProperty("imageController", imageController);
    context->setContextProperty("projectController", projectController);

    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}
