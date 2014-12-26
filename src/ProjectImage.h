#ifndef PROJECTIMAGE_H
#define PROJECTIMAGE_H

#include <QObject>

#include <QSharedPointer>
#include <QString>
#include <QSet>

typedef QSet<QString> StringSet;

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

signals:
    void tagAdded(ProjectImage *image, const QString& tag);
    void tagRemoved(ProjectImage *image, const QString& tag);
    void willBePrunedChanged(ProjectImage *image, bool willBePruned);

private:
    QString imagePath;
    StringSet imageTags;
    bool willBePruned;
};

typedef QSharedPointer<ProjectImage> ProjectImagePtr;

#endif // PROJECTIMAGE_H
