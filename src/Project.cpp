#include "Project.h"

#include "ProjectImage.h"

#include <cassert>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QFile>
#include <QFileInfo>
#include <QStringList>

const QString Project::JsonKeys::IMAGES = "images";

/*!
 * \brief Project::createProject creates a pruning project
 * \return
 */
ProjectPtr Project::createProject()
{
    return ProjectPtr(new Project);
}

/*!
 * \brief Project::equals checks for equality
 * \param other
 * \return
 */
bool Project::equals(ProjectPtr other)
{
    if(other == NULL)
    {
        return false;
    }

    bool imageCountEqual = other->projectImages.size() == projectImages.size();

    if(!imageCountEqual)
    {
        return false;
    }

    foreach(QString key, projectImages.keys())
    {
        if(!projectImages.value(key)->equals(other->projectImages.value(key)))
        {// some image differs, return false
            return false;
        }
    }

    // all checks passed projects are the same, return true
    return true;
}

/*!
 * \brief Project::getProjectImages gets the project images
 * \return
 */
QList<ProjectImagePtr> Project::getProjectImages() const
{
    return projectImages.values();
}

/*!
 * \brief Project::getProjectImagePaths gets the paths used by project images
 * \return
 */
QStringList Project::getProjectImagePaths() const
{
    return projectImages.keys();
}

/*!
 * \brief Project::imageCount gets the number of images in the project
 * \return
 */
int Project::imageCount() const
{
    return projectImages.size();
}

ProjectImagePtr Project::getImage(const QString& imagePath) const
{
    return projectImages.value(imagePath);
}

/*!
 * \brief Project::addProjectImage adds an image to the project
 * \param imagePath
 */
void Project::addProjectImage(const QString &imagePath)
{
    if(!projectImages.contains(imagePath))
    {
        projectImages.insert(imagePath, ProjectImage::createProjectImage(imagePath));

        emit imageAdded(imagePath);
    }
}

/*!
 * \brief Project::removeProjectImage removes an iamage from the project
 * \param imagePath
 */
void Project::removeProjectImage(const QString &imagePath)
{
    if(projectImages.contains(imagePath))
    {
        projectImages.remove(imagePath);

        emit imageRemoved(imagePath);
    }
}

/*!
 * \brief Project::toJsonObject
 * \return
 */
QJsonObject Project::toJsonObject() const
{
    QJsonObject object;

    QJsonArray imagesArray;

    foreach(ProjectImagePtr image, getProjectImages())
    {// save images out to an array
        imagesArray.append(image->toJsonObject());
    }

    object.insert(JsonKeys::IMAGES, imagesArray);

    return object;
}

/*!
 * \brief Project::fromJsonObject
 * \param object
 * \return
 */
ProjectPtr Project::fromJsonObject(const QJsonObject& object)
{
    QJsonArray imagesArray = object.value(JsonKeys::IMAGES).toArray();

    ProjectPtr project = createProject();

    foreach(QJsonValue value, imagesArray)
    {// load images back in
        ProjectImagePtr image = ProjectImage::fromJsonObject(value.toObject());

        project->projectImages.insert(image->getImagePath(), image);
    }

    return project;
}

Project::Project()
{

}

namespace ProjectUtils
{
    /*!
     * \brief addImagesToProject adds a set of images to the project
     * \param project
     * \param imagePaths
     */
    void addImagesToProject(ProjectPtr project, const QStringList &imagePaths)
    {
        foreach(QString imagePath, imagePaths)
        {// add new images to the project
            project->addProjectImage(imagePath);
        }
    }

    /*!
     * \brief pruneProject prunes the unwanted photos from the project
     * \param project
     */
    void pruneProject(ProjectPtr project)
    {
        QList<ProjectImagePtr> projectImages = project->getProjectImages();

        foreach(ProjectImagePtr image, projectImages)
        {
            if(image->getWillBePruned())
            {
                assert(QFileInfo(image->getImagePath()).exists());

                bool removed = QFile(image->getImagePath()).remove();

                if(removed)
                {
                    project->removeProjectImage(image->getImagePath());
                }
            }
        }
    }

    /*!
     * \brief saveToFile saves the document to the file
     * \param project
     * \param projectPath
     */
    void saveToFile(ProjectPtr project, const QString& projectPath)
    {
        QJsonObject projectObject = project->toJsonObject();

        QJsonDocument document;
        document.setObject(projectObject);

        QSaveFile saveFile(projectPath);
        // fall back on directly writing the file in case there are permissions issues
        saveFile.setDirectWriteFallback(true);

        saveFile.open(QSaveFile::WriteOnly);

        saveFile.write(document.toJson());

        saveFile.commit();
    }

    /*!
     * \brief loadFromFile loads the project from a file
     * \param projectPath
     * \return
     */
    ProjectPtr loadFromFile(const QString& projectPath)
    {
        QFile loadFile(projectPath);
        loadFile.open(QFile::ReadOnly);

        QJsonDocument document = QJsonDocument::fromJson(loadFile.readAll());

        return Project::fromJsonObject(document.object());
    }
}
