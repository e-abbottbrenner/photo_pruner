#include "GoogleTest.h"

#include "AppModel.h"
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
    EXPECT_FALSE(appModel->getProjectModel().isNull());
}

TEST_F(AppModelTest, testSetProject)
{
    ProjectPtr newProj = Project::createProject();

    QSignalSpy newProjSpy(appModel.data(), SIGNAL(currentProjectChanged(ProjectPtr)));

    appModel->setCurrentProject(newProj);

    EXPECT_EQ(appModel->getCurrentProject(), newProj);

    ASSERT_EQ(1, newProjSpy.size());
}
