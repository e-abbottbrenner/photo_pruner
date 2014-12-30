#include "GoogleTest.h"

#include "AppModel.h"
#include "ImageListModel.h"
#include "Project.h"

#include <QSignalSpy>

class AppModelTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        appModel = AppModel::createAppModel();
    }

    virtual void TearDown()
    {
        appModel.clear();
    }

    AppModelPtr appModel;
};

TEST_F(AppModelTest, testModelsExist)
{
    ASSERT_FALSE(appModel->getProjectModel().isNull());
    EXPECT_EQ(appModel->getProjectModel()->getProject(), appModel->getCurrentProject());
}

TEST_F(AppModelTest, testSetProject)
{
    ProjectPtr newProj = Project::createProject();

    QSignalSpy newProjSpy(appModel.data(), SIGNAL(currentProjectChanged(ProjectPtr)));

    appModel->setCurrentProject(newProj);

    EXPECT_EQ(appModel->getCurrentProject(), newProj);
    EXPECT_EQ(appModel->getProjectModel()->getProject(), newProj);

    ASSERT_EQ(1, newProjSpy.size());
}
