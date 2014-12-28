#include "AppModel.h"

#include "ImageListModel.h"
#include "Project.h"

#include <QDebug>
#include <QUrl>

/*!
 * \brief AppModel::AppModel constructor, needs to be public for qml
 */
AppModel::AppModel(QObject* parent)
    : QObject(parent)
    , mainProjectModel(ImageListModel::createImageListModel())
{
    setCurrentProject(Project::createProject());
}

/*!
 * \brief AppModel::getRawProjectModel gets a raw pointer to the project model
 * \return
 */
QAbstractItemModel* AppModel::getRawProjectModel() const
{
    return mainProjectModel.data();
}

QUrl AppModel::getProjectUrl() const
{
    return currentProjectUrl;
}

/*!
 * \brief AppModel::openProject does what you think
 * \param projectPath
 */
void AppModel::openProject(const QUrl& projectUrl)
{
    qDebug() << "Opening project with url" << projectUrl;
    setCurrentProject(ProjectUtils::loadFromFile(projectUrl.toLocalFile()));

    if(currentProject)
    {// successful load
        currentProjectUrl = projectUrl;
    }
}

/*!
 * \brief AppModel::saveProject does what you think
 * \param projectPath
 */
void AppModel::saveProject(const QUrl& projectUrl)
{
    if(currentProject)
    {
        qDebug() << "saving project with url" << projectUrl;
        ProjectUtils::saveToFile(currentProject, projectUrl.toLocalFile());
        currentProjectUrl = projectUrl;
    }
}

void AppModel::importImages(const QList<QUrl>& imageUrls)
{
    if(currentProject)
    {
        QStringList systemPaths;

        foreach(QUrl url, imageUrls)
        {
            systemPaths << url.toLocalFile();
        }

        ProjectUtils::addImagesToProject(currentProject, systemPaths);
    }
}

/*!
 * \brief AppModel::setCurrentProject internal method for setting the current project
 * \param project
 */
void AppModel::setCurrentProject(ProjectPtr project)
{
    currentProject = project;
    mainProjectModel->setProject(project);
}

