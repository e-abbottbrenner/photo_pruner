#include "AppController.h"

#include "AppModel.h"
#include "ImageListModel.h"
#include "Project.h"

#include <QDebug>
#include <QUrl>

/*!
 * \brief AppController::AppController constructor, needs to be public for qml
 */
AppController::AppController(QObject* parent)
    : QObject(parent)
{
}

/*!
 * \brief AppController::getRawProjectModel gets a raw pointer to the project model
 * \return
 */
QAbstractItemModel* AppController::getRawProjectModel() const
{
    return appModel()->getProjectModel().data();
}

QUrl AppController::getProjectUrl() const
{
    return currentProjectUrl;
}

/*!
 * \brief AppController::newProject does what you think
 */
void AppController::newProject()
{
    qDebug() << "Creating new project";

    appModel()->setCurrentProject(Project::createProject());

    currentProjectUrl = QUrl();
}

/*!
 * \brief AppController::openProject does what you think
 * \param projectPath
 */
void AppController::openProject(const QUrl& projectUrl)
{
    qDebug() << "Opening project with url" << projectUrl;
    appModel()->setCurrentProject(ProjectUtils::loadFromFile(projectUrl.toLocalFile()));

    if(currentProject())
    {// successful load
        currentProjectUrl = projectUrl;
    }
}

/*!
 * \brief AppController::saveProject does what you think
 * \param projectPath
 */
void AppController::saveProject(const QUrl& projectUrl)
{
    if(currentProject())
    {
        qDebug() << "saving project with url" << projectUrl;
        ProjectUtils::saveToFile(currentProject(), projectUrl.toLocalFile());
        currentProjectUrl = projectUrl;
    }
}
