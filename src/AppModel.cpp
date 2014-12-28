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

QString AppModel::getProjectUrl() const
{
    return currentProjectUrl;
}

/*!
 * \brief AppModel::openProject does what you think
 * \param projectPath
 */
void AppModel::openProject(const QString& projectUrl)
{
    qDebug() << "Opening project with url" << projectUrl;
    setCurrentProject(ProjectUtils::loadFromFile(QUrl(projectUrl).toLocalFile()));

    if(currentProject)
    {// successful load
        currentProjectUrl = projectUrl;
    }
}

/*!
 * \brief AppModel::saveProject does what you think
 * \param projectPath
 */
void AppModel::saveProject(const QString& projectUrl)
{
    if(currentProject)
    {
        qDebug() << "saving project with url" << projectUrl;
        ProjectUtils::saveToFile(currentProject, QUrl(projectUrl).toLocalFile());
        currentProjectUrl = projectUrl;
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

