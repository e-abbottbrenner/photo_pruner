#ifndef CURRENTIMAGECONTROLLER_H
#define CURRENTIMAGECONTROLLER_H

#include <QObject>

#include "TopLevelController.h"

#include <QUrl>

class ImageController : public QObject, public TopLevelController
{
    Q_OBJECT

    Q_PROPERTY(QUrl currentImageUrl READ getCurrentImageUrl NOTIFY currentImageUrlChanged)

public:
    explicit ImageController(QObject *parent = 0);

    QUrl getCurrentImageUrl() const;

    Q_INVOKABLE void setCurrentIndex(int currentIndex);

signals:
    void currentImageUrlChanged(QUrl url);

private:
    QUrl currentImageUrl;
};

#endif // CURRENTIMAGECONTROLLER_H
