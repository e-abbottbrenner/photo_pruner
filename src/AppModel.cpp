#include "AppModel.h"

#include "ImageListModel.h"
#include "Project.h"

AppModel::AppModel()
    : projectModel(ImageListModel::createImageListModel())
{
    setCurrentProject(Project::createProject());
}

AppModelPtr AppModel::createAppModel()
{
    return AppModelPtr(new AppModel);
}

/*!
 * \brief AppModel::setCurrentProject internal method for setting the current project
 * \param project
 */
void AppModel::setCurrentProject(ProjectPtr project)
{
    currentProject = project;
    projectModel->setProject(project);
}

ProjectPtr AppModel::getCurrentProject() const
{
    return currentProject;
}

ImageListModelPtr AppModel::getProjectModel() const
{
    return projectModel;
}
