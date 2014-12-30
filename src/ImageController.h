#ifndef CURRENTIMAGECONTROLLER_H
#define CURRENTIMAGECONTROLLER_H

#include <QObject>

#include "TopLevelController.h"

#include "ProjectImagePtr.h"

class ImageController : public QObject, public TopLevelController
{
    Q_OBJECT

public:
    explicit ImageController(QObject *parent = 0);

    Q_INVOKABLE void setImage(const QString& imageSourcePath);

private:
    ProjectImagePtr image;
};

#endif // CURRENTIMAGECONTROLLER_H
