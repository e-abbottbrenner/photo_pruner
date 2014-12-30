#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>

#include "AppModelPtr.h"
#include "ImageListModelPtr.h"
#include "ProjectPtr.h"

class AppModel : public QObject
{
    Q_OBJECT

public:
    static AppModelPtr createAppModel();

    void setCurrentProject(ProjectPtr project);
    ProjectPtr getCurrentProject() const;

    ImageListModelPtr getProjectModel() const;

signals:
    void currentProjectChanged(ProjectPtr project);

private:
    AppModel();

    ProjectPtr currentProject;

    ImageListModelPtr projectModel;
};

#endif // APPMODEL_H
