#ifndef CURRENTIMAGECONTROLLER_H
#define CURRENTIMAGECONTROLLER_H

#include <QObject>

#include "TopLevelController.h"

#include "ProjectImagePtr.h"

#include <QStringList>

class ImageController : public QObject, public TopLevelController
{
    Q_OBJECT

    Q_PROPERTY(QStringList tags READ getTags NOTIFY tagsChanged)
    Q_PROPERTY(bool hasImage READ imageAvailable NOTIFY imageAvailableChanged)
    Q_PROPERTY(bool willBePruned READ getWillBePruned WRITE setWillBePruned NOTIFY willBePrunedChanged)

public:
    explicit ImageController(QObject *parent = 0);

    bool getWillBePruned() const;
    void setWillBePruned(bool prune);

    Q_INVOKABLE void setImage(const QString& imageSourcePath);

    Q_INVOKABLE void removeFromProject();

    Q_INVOKABLE void addTag(const QString& tag);
    Q_INVOKABLE void removeTag(const QString& tag);

    QStringList getTags() const;

    bool imageAvailable() const;

signals:
    void tagsChanged(const QStringList& tags);
    void imageAvailableChanged(bool imageAvailable);
    void willBePrunedChanged(bool willBePruned);

private:    
    ProjectImagePtr image;

    void emitTagsChanged(const QStringList& tags);
    void emitImageAvailableChanged(bool imageAvailable);
    void emitWillBePrunedChanged(bool willBePruned);

    class ChangeCatcher
    {
    public:
        ChangeCatcher(ImageController *controller);

        ~ChangeCatcher();

    private:
        QStringList oldTags;
        bool oldImageAvailable;
        bool oldWillBePruned;

        ImageController *controller;
    };
};

#endif // CURRENTIMAGECONTROLLER_H
