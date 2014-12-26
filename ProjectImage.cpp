#include "ProjectImage.h"

#include <cassert>

ProjectImage::ProjectImage(QString imagePath)
    : imagePath(imagePath), willBePruned(false)
{
}

StringSet ProjectImage::getImageTags() const
{
    return imageTags;
}

bool ProjectImage::hasImageTag(const QString &tag)
{
    return imageTags.contains(tag);
}

void ProjectImage::addImageTag(const QString &tag)
{
    assert(!tag.isNull());

    imageTags.insert(tag);

    emit tagAdded(this, tag);
}

void ProjectImage::removeImageTag(const QString &tag)
{
    assert(!tag.isNull());

    if(imageTags.contains(tag))
    {
        imageTags.remove(tag);

        emit tagRemoved(this, tag);
    }
}

bool ProjectImage::getWillBePruned() const
{
    return willBePruned;
}

void ProjectImage::setWillBePruned(bool value)
{
    willBePruned = value;
}


