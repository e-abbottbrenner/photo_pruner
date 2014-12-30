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

    QStringList getProjectImagePaths() const;

    int imageCount() const;

    ProjectImagePtr getImage(const QString& imagePath) const;

    void addProjectImage(const QString& imagePath);
    void removeProjectImage(const QString& imagePath);

    QJsonObject toJsonObject() const;
    static ProjectPtr fromJsonObject(const QJsonObject& object);

    class JsonKeys
    {
    public:
        static const QString IMAGES;
    };

signals:
    void imageAdded(const QString& image);
    void imageRemoved(const QString& image);
    void imageChanged(const QString& image);

private:
    void connectTo(ProjectImagePtr image);

    // we use a map so that we have consistent ordering for the items in it
    ProjectImageMap projectImages;

    Project();
};

namespace ProjectUtils
{
    extern void addImagesToProject(ProjectPtr project, const QStringList& imagePaths);
    extern void pruneProject(ProjectPtr project);
    extern void saveToFile(ProjectPtr project, const QString& projectPath);
    extern ProjectPtr loadFromFile(const QString& projectPath);
}

#endif // PROJECT_H
