#include "ProjectController.h"

#include <QStringList>
#include <QUrl>

#include "Project.h"

ProjectController::ProjectController(QObject *parent) : QObject(parent)
{
}

void ProjectController::importImages(const QList<QUrl>& imageUrls)
{
    if(currentProject())
    {
        QStringList systemPaths;

        foreach(QUrl url, imageUrls)
        {
            systemPaths << url.toLocalFile();
        }

        ProjectUtils::addImagesToProject(currentProject(), systemPaths);
    }
}

void ProjectController::deletePrunedImages()
{
    if(currentProject())
    {
        ProjectUtils::pruneProject(currentProject());
    }
}
