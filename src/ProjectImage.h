#ifndef PROJECTIMAGE_H
#define PROJECTIMAGE_H

#include <QObject>

#include <QJsonObject>
#include <QSharedPointer>
#include <QString>
#include <QSet>

typedef QSet<QString> StringSet;

class ProjectImage;
typedef QSharedPointer<ProjectImage> ProjectImagePtr;

class ProjectImage : public QObject
{
    Q_OBJECT

public:
    ProjectImage(QString imagePath);

    StringSet getImageTags() const;

    bool hasImageTag(const QString& tag);
    void addImageTag(const QString& tag);
    void removeImageTag(const QString& tag);

    bool getWillBePruned() const;
    void setWillBePruned(bool value);

    QString getImagePath() const;

    QJsonObject toJsonObject() const;
    static ProjectImage* fromJsonObject(const QJsonObject& obj);

    class JsonKeys
    {
    public:
        static const QString IMAGE_PATH;
        static const QString TAGS;
        static const QString WILL_BE_PRUNED;
    };

    bool equals(ProjectImagePtr other) const;
    bool equals(const ProjectImage *other) const;

signals:
    void tagAdded(ProjectImage *image, const QString& tag);
    void tagRemoved(ProjectImage *image, const QString& tag);
    void willBePrunedChanged(ProjectImage *image, bool willBePruned);

private:
    QString imagePath;
    StringSet imageTags;
    bool willBePruned;
};

#endif // PROJECTIMAGE_H
