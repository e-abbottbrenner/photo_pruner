#include "ImageController.h"

#include "Project.h"
#include "ProjectImage.h"

#include <QDebug>

ImageController::ImageController(QObject *parent) : QObject(parent)
{
}

bool ImageController::getWillBePruned() const
{
    if(image)
    {
        return image->getWillBePruned();
    }

    return false;
}

void ImageController::setWillBePruned(bool prune)
{
    ChangeCatcher changeCatcher(this);

    if(image)
    {
        image->setWillBePruned(prune);
    }
}

int ImageController::getRotation() const
{
    if(image)
    {
        return image->getRotation();
    }

    return 0;
}

void ImageController::setRotation(int rotation)
{
    ChangeCatcher changeCatcher(this);

    if(image)
    {
        image->setRotation(rotation);
    }
}

void ImageController::setImage(const QString &imageSourcePath)
{
    ChangeCatcher changeCatcher(this);

    if(currentProject())
    {
        image = currentProject()->getImage(imageSourcePath);
    }
    else
    {
        image.clear();
    }
}

void ImageController::removeFromProject()
{
    ChangeCatcher changeCatcher(this);

    currentProject()->removeProjectImage(image->getImagePath());

    image.clear();
}

void ImageController::addTag(const QString& tag)
{
    ChangeCatcher changeCatcher(this);

    image->addImageTag(tag);
}

void ImageController::removeTag(const QString& tag)
{
    ChangeCatcher changeCatcher(this);

    image->removeImageTag(tag);
}

QStringList ImageController::getTags() const
{
    QStringList tags;

    if(image)
    {
        tags = image->getImageTags().toList();
        tags.sort();
    }

    return tags;
}

bool ImageController::imageAvailable() const
{
    return !image.isNull();
}

void ImageController::emitTagsChanged(const QStringList &tags)
{
    emit tagsChanged(tags);
}

void ImageController::emitImageAvailableChanged(bool imageAvailable)
{
    emit imageAvailableChanged(imageAvailable);
}

void ImageController::emitWillBePrunedChanged(bool willBePruned)
{
    emit willBePrunedChanged(willBePruned);
}

void ImageController::emitRotationChanged(int rotation)
{
    emit rotationChanged(rotation);
}

ImageController::ChangeCatcher::ChangeCatcher(ImageController* controller)
    : controller(controller)
    , oldTags(controller->getTags())
    , oldImageAvailable(controller->imageAvailable())
    , oldWillBePruned(controller->getWillBePruned())
    , oldRotation(controller->getRotation())
{
}

ImageController::ChangeCatcher::~ChangeCatcher()
{
    QStringList newTags = controller->getTags();
    bool newImageAvailable = controller->imageAvailable();
    bool newWillBePruned = controller->getWillBePruned();
    int newRotation = controller->getRotation();

    if(oldTags != newTags)
    {
        controller->emitTagsChanged(newTags);
    }

    if(oldImageAvailable != newImageAvailable)
    {
        controller->emitImageAvailableChanged(newImageAvailable);
    }

    if(newWillBePruned != oldWillBePruned)
    {
        controller->emitWillBePrunedChanged(newWillBePruned);
    }

    if(oldRotation != newRotation)
    {
        controller->emitRotationChanged(newRotation);
    }
}
