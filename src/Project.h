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

    ProjectImagePtr getImage(const QString& imagePath) const;

    void addProjectImage(const QString& imagePath);
    void removeProjectImage(const QString& imagePath);

signals:
    void imageAdded(const QString& image);
    void imageRemoved(const QString& image);

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
