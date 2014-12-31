#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

#include "TopLevelController.h"

#include "AppModelPtr.h"
#include "ImageListModelPtr.h"
#include "ProjectPtr.h"
#include "PruningFilters.h"

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

    // moc is bad with enums so we have to express this as a property instead of a Q_INVOKABLE
    // it was fixed for properties in Qt 5.3: https://bugreports.qt-project.org/browse/QTBUG-33577
    // but it appears to still be beoken for invokables
    // can't use the typedef here for some reason, probably moc being finnicky
    Q_PROPERTY(PruningFilters::PruningFilter pruningFilter READ getPruningFilter WRITE setPruningFilter NOTIFY pruningFilterChanged)

public:
    AppController(QObject *parent = 0);

    QAbstractItemModel* getRawProjectModel() const;
    QUrl getProjectUrl() const;

    PruningFilter getPruningFilter() const;
    void setPruningFilter(PruningFilters::PruningFilter filter);

    Q_INVOKABLE void newProject();
    Q_INVOKABLE void openProject(const QUrl& projectUrl);
    Q_INVOKABLE void saveProject(const QUrl& projectUrl);

signals:
    // this is just for the sake of qml bindings, the model itself never changes so this is pointless otherwise
    void projectModelChanged(QAbstractItemModel* model);
    void projectUrlChanged(QUrl projectUrl);
    void pruningFilterChanged(PruningFilters::PruningFilter filter);

private:
    void setProjectUrl(QUrl url);

    QUrl currentProjectUrl;
    QUrl currentImageUrl;
};

#endif // APPCONTROLLER_H
