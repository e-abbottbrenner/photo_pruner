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
}

void ImageController::setWillBePruned(bool prune)
{
    if(image)
    {
        image->setWillBePruned(prune);
    }
}

void ImageController::removeFromProject()
{
    currentProject()->removeProjectImage(image->getImagePath());
}

void ImageController::addTag(const QString& tag)
{
    image->addImageTag(tag);
}

void ImageController::removeTag(const QString& tag)
{
    image->removeImageTag(tag);
}
