#include "AppModel.h"

#include "ImageListModel.h"
#include "Project.h"

/*!
 * \brief AppModel::AppModel constructor, needs to be public for qml
 */
AppModel::AppModel(QObject* parent)
    : QObject(parent)
    , mainProjectModel(ImageListModel::createImageListModel())
{
    setCurrentProject(Project::createProject());

    // TEMPORARY UNTIL WE GET ACTIONS WORKING
    this->openProject(QString(REPOSITORY_PATH) + "/test/resources/projects/sampleproj.json");
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
void AppModel::openProject(const QString& projectPath)
{
    setCurrentProject(ProjectUtils::loadFromFile(projectPath));
}

/*!
 * \brief AppModel::saveProject does what you think
 * \param projectPath
 */
void AppModel::saveProject(const QString& projectPath)
{
    if(currentProject)
    {
        ProjectUtils::saveToFile(currentProject, projectPath);
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

