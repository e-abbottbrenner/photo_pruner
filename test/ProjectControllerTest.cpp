#include "TopLevelControllerFixture.h"

#include "Project.h"
#include "ProjectImage.h"
#include "ProjectController.h"
#include "ResourcePath.h"

#include <QDir>
#include <QTemporaryDir>

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

TEST_F(ProjectControllerTest, testPruneProject)
{
    ProjectPtr project = appModel->getCurrentProject();

    QTemporaryDir tempDir("PhotoPrunerTest");

    QString streamPath = tempDir.path() + "/stream.jpg";
    QString sunsetPath = tempDir.path() + "/sunset.jpg";

    QFile::copy(RESOURCE_PATH + "/images/stream.jpg", streamPath);
    QFile::copy(RESOURCE_PATH + "/images/sunset.jpg", sunsetPath);

    project->addProjectImage(streamPath);
    project->addProjectImage(sunsetPath);

    ProjectImagePtr imageToPrune = project->getImage(sunsetPath);
    imageToPrune->setWillBePruned(true);

    EXPECT_TRUE(QFileInfo(streamPath).exists());
    EXPECT_TRUE(QFileInfo(sunsetPath).exists());

    controller->deletePrunedImages();

    EXPECT_TRUE(QFileInfo(streamPath).exists());
    EXPECT_FALSE(QFileInfo(sunsetPath).exists());
}
