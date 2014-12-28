#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>

#include "ImageListModelPtr.h"
#include "ProjectPtr.h"

#include <QUrl>

class QAbstractItemModel;

class AppModel : public QObject
{
    Q_OBJECT

    /* Expose the following items via properties:
     * * The item model(s) for displaying and editing the photo list
     * * The project url to support standard save operation
     */

    Q_PROPERTY(QAbstractItemModel* projectModel READ getRawProjectModel NOTIFY projectModelChanged)
    Q_PROPERTY(QUrl projectUrl READ getProjectUrl NOTIFY projectUrlChanged)

public:
    AppModel(QObject *parent = 0);

    QAbstractItemModel* getRawProjectModel() const;
    QUrl getProjectUrl() const;

signals:
    void projectModelChanged(QAbstractItemModel* model);
    void projectUrlChanged(QString projectUrl);

    /* Expose the following functions via slots for qml usage
     * * Open project (path)
     * * Save project (path)
     * * Import images (path list)
     */
public slots:
    void openProject(const QUrl& projectUrl);
    void saveProject(const QUrl& projectUrl);
    void importImages(const QList<QUrl>& imageUrls);

private:
    void setCurrentProject(ProjectPtr project);

    ProjectPtr currentProject;
    QUrl currentProjectUrl;
    ImageListModelPtr mainProjectModel;
};

#endif // APPMODEL_H
