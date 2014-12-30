#include "TopLevelControllerFixture.h"

#include "Project.h"
#include "ProjectController.h"
#include "ResourcePath.h"

#include <QDir>

class ProjectControllerTest : public TopLevelControllerFixture<ProjectController>
{
protected:
    virtual ProjectController* createController()
    {
        return new ProjectController;
    }
};

TEST_F(ProjectControllerTest, testImport)
{
    ProjectPtr project = appModel->getCurrentProject();

    QStringList files;
    QList<QUrl> urls;

    files << QDir(RESOURCE_PATH).absoluteFilePath("images/sunset.jpg");
    urls << QUrl::fromLocalFile(files.last());

    files << QDir(RESOURCE_PATH).absoluteFilePath("images/stream.jpg");
    urls << QUrl::fromLocalFile(files.last());

    controller->importImages(urls);

    EXPECT_TRUE(project->getProjectImagePaths().contains(files.first()));
    EXPECT_TRUE(project->getProjectImagePaths().contains(files.last()));
}
