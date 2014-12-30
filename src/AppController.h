#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

#include "TopLevelController.h"

#include "AppModelPtr.h"
#include "ImageListModelPtr.h"
#include "ProjectPtr.h"

#include <QUrl>

class QAbstractItemModel;

class AppController : public QObject, public TopLevelController
{
    Q_OBJECT

    /* Expose the following items via properties:
     * * The item model(s) for displaying and editing the photo list
     * * The project url to support standard save operation
     */

    Q_PROPERTY(QAbstractItemModel* projectModel READ getRawProjectModel NOTIFY projectModelChanged)
    Q_PROPERTY(QUrl projectUrl READ getProjectUrl NOTIFY projectUrlChanged)

public:
    AppController(QObject *parent = 0);

    QAbstractItemModel* getRawProjectModel() const;
    QUrl getProjectUrl() const;

    Q_INVOKABLE void newProject();
    Q_INVOKABLE void openProject(const QUrl& projectUrl);
    Q_INVOKABLE void saveProject(const QUrl& projectUrl);

signals:
    // this is just for the sake of qml bindings, the model itself never changes so this is pointless otherwise
    void projectModelChanged(QAbstractItemModel* model);
    void projectUrlChanged(QUrl projectUrl);

private:
    QUrl currentProjectUrl;
    QUrl currentImageUrl;
};

#endif // APPCONTROLLER_H
