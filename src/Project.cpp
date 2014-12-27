#include "Project.h"

#include "ProjectImage.h"

#include <cassert>

#include <QStringList>

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
 * \brief Project::addProjectImage adds an image to the project
 * \param projectImage
 */
void Project::addProjectImage(ProjectImagePtr projectImage)
{
    assert(projectImage != NULL);

    if(!projectImages.contains(projectImage->getImagePath()))
    {
        projectImages.insert(projectImage->getImagePath(), projectImage);

        emit imageAdded(projectImage);
    }
}

/*!
 * \brief Project::removeProjectImage adds an image to the project
 * \param projectImage
 */
void Project::removeProjectImage(ProjectImagePtr projectImage)
{
    assert(projectImage != NULL);

    if(projectImages.contains(projectImage->getImagePath()))
    {
        projectImages.remove(projectImage->getImagePath());

        emit imageRemoved(projectImage);
    }
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
            project->addProjectImage(ProjectImage::createProjectImage(imagePath));
        }
    }
}
