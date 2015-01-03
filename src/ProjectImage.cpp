#include "ProjectImage.h"

#include <cassert>
#include <QJsonArray>
#include <QStringList>

const QString ProjectImage::JsonKeys::IMAGE_PATH = "image-path";
const QString ProjectImage::JsonKeys::TAGS = "tags";
const QString ProjectImage::JsonKeys::WILL_BE_PRUNED = "will-be-pruned";
const QString ProjectImage::JsonKeys::ROTATION = "rotation";

/*!
 * \brief ProjectImage::create constructs a project image for the given system file path
 * \param imagePath
 * \return
 */
ProjectImagePtr ProjectImage::createProjectImage(const QString &imagePath)
{
    return ProjectImagePtr(new ProjectImage(imagePath));
}

/*!
 * \brief ProjectImage::ProjectImage
 * \param imagePath
 */
ProjectImage::ProjectImage(const QString& imagePath)
    : imagePath(imagePath), willBePruned(false), rotation(0)
{
}

/*!
 * \brief ProjectImage::getImageTags gets the set of tags for a ProjectImage,
 * a project image keeps a set of tags to enable easier grouping for pruning
 * \return
 */
StringSet ProjectImage::getImageTags() const
{
    return imageTags;
}

/*!
 * \brief ProjectImage::hasImageTag checks for the presence of a specific tag
 * \param tag
 * \return
 */
bool ProjectImage::hasImageTag(const QString &tag)
{
    return imageTags.contains(tag);
}

/*!
 * \brief ProjectImage::addImageTag adds a new tag, a signal tagAdded will be emitted when successful
 * \param tag
 */
void ProjectImage::addImageTag(const QString &tag)
{
    assert(!tag.isNull());

    if(!imageTags.contains(tag))
    {
        imageTags.insert(tag);

        emit tagAdded(imagePath, tag);
    }
}

/*!
 * \brief ProjectImage::removeImageTag removes an old tag, a signal tagRemoved will be emitted when successful
 * \param tag
 */
void ProjectImage::removeImageTag(const QString &tag)
{
    assert(!tag.isNull());

    if(imageTags.contains(tag))
    {
        imageTags.remove(tag);

        emit tagRemoved(imagePath, tag);
    }
}

/*!
 * \brief ProjectImage::getWillBePruned A ProjectImage can be set to be pruned in a mass deletion.
 *  This getter determines if it's currently supposed to be pruned or not
 * \return
 */
bool ProjectImage::getWillBePruned() const
{
    return willBePruned;
}

/*!
 * \brief ProjectImage::setWillBePruned setter for whether or not to prune this image
 * \param willBePruned
 */
void ProjectImage::setWillBePruned(bool willBePruned)
{
    if(!this->willBePruned == willBePruned)
    {
        this->willBePruned = willBePruned;

        emit willBePrunedChanged(imagePath, willBePruned);
    }
}

int ProjectImage::getRotation() const
{
    return rotation;
}

void ProjectImage::setRotation(int rotation)
{
    rotation = rotation % 360;

    if(rotation < 0)
    {
        rotation += 360;
    }

    if(this->rotation != rotation)
    {
        this->rotation = rotation;

        emit rotationChanged(imagePath, rotation);
    }
}

/*!
 * \brief ProjectImage::getImagePath gets the path of the image on the file system
 * \return
 */
QString ProjectImage::getImagePath() const
{
    return imagePath;
}

/*!
 * \brief ProjectImage::toJsonObject serializes to json
 * \return
 */
QJsonObject ProjectImage::toJsonObject() const
{
    QJsonArray tags;

    QStringList tagList = imageTags.toList();
    // sort the list  so they always come out to the json array in the same order
    // this is necessary for testing equality of json objects
    tagList.sort();

    foreach(QString tag, tagList)
    {// convert the set to a json array
        tags.append(tag);
    }

    QJsonObject object;

    object.insert(JsonKeys::IMAGE_PATH, imagePath);
    object.insert(JsonKeys::TAGS, tags);
    object.insert(JsonKeys::WILL_BE_PRUNED, willBePruned);
    object.insert(JsonKeys::ROTATION, rotation);

    return object;
}

/*!
 * \brief ProjectImage::fromJsonObject deserializes from json
 * \param obj
 * \return
 */
ProjectImagePtr ProjectImage::fromJsonObject(const QJsonObject &obj)
{
    QString imageName(obj.value(JsonKeys::IMAGE_PATH).toString());

    ProjectImagePtr projectImage(new ProjectImage(imageName));

    foreach(QJsonValue value, obj.value(JsonKeys::TAGS).toArray())
    {
        // bypass the signal from the add method
        projectImage->imageTags.insert(value.toString());
    }

    projectImage->willBePruned = obj.value(JsonKeys::WILL_BE_PRUNED).toBool();
    projectImage->rotation = obj.value(JsonKeys::ROTATION).toInt();

    return projectImage;
}

/*!
 * \brief ProjectImage::equals tests two project images for equality
 * \param other
 * \return
 */
bool ProjectImage::equals(ProjectImagePtr other) const
{
    return other != NULL
                    && this->imagePath == other->imagePath
                    && this->imageTags == other->imageTags
                    && this->willBePruned == other->willBePruned
                    && this->rotation == other->rotation;
}
