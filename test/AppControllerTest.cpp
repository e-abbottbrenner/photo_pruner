#include "TopLevelControllerFixture.h"

#include "AppController.h"
#include "ImageListFilterModel.h"
#include "Project.h"
#include "ResourcePath.h"

#include <QDir>
#include <QSignalSpy>
#include <QTemporaryDir>
#include <QUrl>

class AppControllerTest : public TopLevelControllerFixture<AppController>
{
protected:
    virtual AppController* createController()
    {
        return new AppController;
    }
};

TEST_F(AppControllerTest, testModelAvailable)
{
    EXPECT_TRUE(NULL != controller->getRawProjectModel());
}

TEST_F(AppControllerTest, testNewProject)
{
    controller->openProject(QUrl::fromLocalFile(QDir(RESOURCE_PATH).absoluteFilePath("projects/sampleproj.json")));

    ProjectPtr oldProj = appModel->getCurrentProject();

    QSignalSpy urlChangedSpy(controller.data(), SIGNAL(projectUrlChanged(QUrl)));

    controller->newProject();

    ASSERT_EQ(1, urlChangedSpy.size());

    EXPECT_EQ(QUrl(), urlChangedSpy[0][0].toUrl());
    EXPECT_EQ(QUrl(), controller->getProjectUrl());

    EXPECT_NE(oldProj, appModel->getCurrentProject());

    // fresh project
    EXPECT_EQ(0, appModel->getCurrentProject()->imageCount());
}

TEST_F(AppControllerTest, testOpenProject)
{
    ProjectPtr oldProj = appModel->getCurrentProject();

    QSignalSpy urlChangedSpy(controller.data(), SIGNAL(projectUrlChanged(QUrl)));

    QString projectPath(QDir(RESOURCE_PATH).absoluteFilePath("projects/sampleproj.json"));
    QUrl projectUrl = QUrl::fromLocalFile(projectPath);

    controller->openProject(projectUrl);

    ASSERT_EQ(1, urlChangedSpy.size());

    EXPECT_EQ(projectUrl, urlChangedSpy[0][0].toUrl());
    EXPECT_EQ(projectUrl, controller->getProjectUrl());

    EXPECT_NE(oldProj, appModel->getCurrentProject());

    // make sure it actually loaded
    EXPECT_EQ(2, appModel->getCurrentProject()->imageCount());
}

TEST_F(AppControllerTest, testSaveProject)
{
    QTemporaryDir tempDir("testprojdir");

    QFileInfo fileInfo(QDir(tempDir.path()).absoluteFilePath("testproj.json"));

    QSignalSpy urlChangedSpy(controller.data(), SIGNAL(projectUrlChanged(QUrl)));

    EXPECT_FALSE(fileInfo.exists());

    controller->saveProject(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));

    fileInfo.refresh();

    EXPECT_TRUE(fileInfo.exists());

    ASSERT_EQ(1, urlChangedSpy.size());

    EXPECT_EQ(QUrl::fromLocalFile(fileInfo.absoluteFilePath()), urlChangedSpy[0][0].toUrl());
}

TEST_F(AppControllerTest, testSetPruningFilter)
{
    EXPECT_EQ(PruningFilters::ShowAll, appModel->getFilteredProjectModel()->getPruningFilter());

    controller->setPruningFilter(PruningFilters::ShowPruned);

    EXPECT_EQ(PruningFilters::ShowPruned, appModel->getFilteredProjectModel()->getPruningFilter());
}

TEST_F(AppControllerTest, testSetTagFilter)
{
    EXPECT_EQ(QString(), appModel->getFilteredProjectModel()->getTagFilter());

    controller->setTagFilter("test");

    EXPECT_EQ("test", appModel->getFilteredProjectModel()->getTagFilter());
}
