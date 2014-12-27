#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>

#include <QJsonObject>
#include <QMap>

#include "ProjectImagePtr.h"
#include "ProjectPtr.h"

typedef QMap<QString, ProjectImagePtr> ProjectImageMap;

class Project : public QObject
{
    Q_OBJECT
public:
    static ProjectPtr createProject();

    bool equals(ProjectPtr other);

    QList<ProjectImagePtr> getProjectImages() const;

    void addProjectImage(ProjectImagePtr projectImage);
    void removeProjectImage(ProjectImagePtr projectImage);

signals:
    void imageAdded(ProjectImagePtr image);
    void imageRemoved(ProjectImagePtr image);

private:
    // we use a map so that we have consistent ordering for the items in it
    ProjectImageMap projectImages;

    Project();
};

namespace ProjectUtils
{
    extern void addImagesToProject(ProjectPtr project, const QStringList& imagePaths);
}

#endif // PROJECT_H
