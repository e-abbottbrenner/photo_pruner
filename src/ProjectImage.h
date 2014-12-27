#ifndef PROJECTIMAGE_H
#define PROJECTIMAGE_H

#include <QObject>

#include <QJsonObject>

#include "ProjectImagePtr.h"
#include "StringSet.h"

class ProjectImage : public QObject
{
    Q_OBJECT

public:
    static ProjectImagePtr createProjectImage(const QString& imagePath);

    StringSet getImageTags() const;

    bool hasImageTag(const QString& tag);
    void addImageTag(const QString& tag);
    void removeImageTag(const QString& tag);

    bool getWillBePruned() const;
    void setWillBePruned(bool value);

    QString getImagePath() const;

    bool equals(ProjectImagePtr other) const;

    QJsonObject toJsonObject() const;
    static ProjectImagePtr fromJsonObject(const QJsonObject& obj);


    class JsonKeys
    {
    public:
        static const QString IMAGE_PATH;
        static const QString TAGS;
        static const QString WILL_BE_PRUNED;
    };

signals:
    void tagAdded(const QString& imagePath, const QString& tag);
    void tagRemoved(const QString& imagePath, const QString& tag);
    void willBePrunedChanged(const QString& imagePath, bool willBePruned);

private:
    ProjectImage(const QString &imagePath);

    QString imagePath;
    StringSet imageTags;
    bool willBePruned;
};

#endif // PROJECTIMAGE_H
