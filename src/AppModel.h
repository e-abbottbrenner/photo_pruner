#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>

#include "ImageListModelPtr.h"
#include "ProjectPtr.h"

class QAbstractItemModel;

class AppModel : public QObject
{
    Q_OBJECT

    /* Expose the following items via properties:
     * * The item model(s) for displaying and editing the photo list
     */

    Q_PROPERTY(QAbstractItemModel* projectModel READ getRawProjectModel NOTIFY projectModelChanged)

public:
    AppModel(QObject *parent = 0);

    QAbstractItemModel* getRawProjectModel() const;

signals:
    void projectModelChanged(QAbstractItemModel* model);
    void currentIndexChanged(const QModelIndex& index);

    /* Expose the following functions via slots for qml usage
     * * Open project (path)
     * * Save project (path)
     */
public slots:
    void openProject(const QString& projectUrl);
    void saveProject(const QString& projectUrl);

private:
    void setCurrentProject(ProjectPtr project);

    ProjectPtr currentProject;
    ImageListModelPtr mainProjectModel;
};

#endif // APPMODEL_H
