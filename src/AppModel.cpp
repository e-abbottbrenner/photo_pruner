#include "AppModel.h"

#include "ImageListModel.h"
#include "Project.h"

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

/*!
 * \brief AppModel::openProject does what you think
 * \param projectPath
 */
void AppModel::openProject(const QString& projectUrl)
{
    setCurrentProject(ProjectUtils::loadFromFile(QUrl(projectUrl).toLocalFile()));
}

/*!
 * \brief AppModel::saveProject does what you think
 * \param projectPath
 */
void AppModel::saveProject(const QString& projectUrl)
{
    if(currentProject)
    {
        ProjectUtils::saveToFile(currentProject, QUrl(projectUrl).toLocalFile());
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

