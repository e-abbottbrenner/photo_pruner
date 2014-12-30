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
    return appModel->getProjectModel().data();
}

QUrl AppController::getProjectUrl() const
{
    return currentProjectUrl;
}

QUrl AppController::getCurrentImageUrl() const
{
    return currentImageUrl;
}

void AppController::setAppModel(AppModelPtr appModel)
{
    this->appModel = appModel;
}

/*!
 * \brief AppController::openProject does what you think
 * \param projectPath
 */
void AppController::openProject(const QUrl& projectUrl)
{
    qDebug() << "Opening project with url" << projectUrl;
    appModel->setCurrentProject(ProjectUtils::loadFromFile(projectUrl.toLocalFile()));

    if(appModel->getCurrentProject())
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
    if(appModel->getCurrentProject())
    {
        qDebug() << "saving project with url" << projectUrl;
        ProjectUtils::saveToFile(appModel->getCurrentProject(), projectUrl.toLocalFile());
        currentProjectUrl = projectUrl;
    }
}

void AppController::importImages(const QList<QUrl>& imageUrls)
{
    if(appModel->getCurrentProject())
    {
        QStringList systemPaths;

        foreach(QUrl url, imageUrls)
        {
            systemPaths << url.toLocalFile();
        }

        ProjectUtils::addImagesToProject(appModel->getCurrentProject(), systemPaths);
    }
}

/*!
 * \brief AppController::determineCurrentImageUrl this is an ugly hack used by the list view to propagate the image url information outside of the delegate
 * \param currentIndex
 */
void AppController::determineCurrentImageUrl(int currentIndex)
{
    QUrl newImageUrl = appModel->getProjectModel()->data(appModel->getProjectModel()->index(currentIndex), ImageListModel::UrlRole).toUrl();

    if(newImageUrl != currentImageUrl)
    {
        currentImageUrl = newImageUrl;

        emit currentImageUrlChanged(newImageUrl);
    }
}
