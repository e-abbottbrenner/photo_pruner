#include "ImageController.h"

#include "Project.h"
#include "ProjectImage.h"

#include <QDebug>

ImageController::ImageController(QObject *parent) : QObject(parent)
{
}

void ImageController::setImage(const QString &imageSourcePath)
{
    image = currentProject()->getImage(imageSourcePath);

    if(image)
    {
        qDebug() << "Image controller set to use image" << imageSourcePath;
    }
}
