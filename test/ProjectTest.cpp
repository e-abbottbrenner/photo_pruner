#include "GoogleTest.h"

#include "Project.h"
#include "ProjectImage.h"

#include <QSignalSpy>
#include <QStringList>

class ProjectTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        project = Project::createProject();
    }

    virtual void TearDown()
    {
        project.clear();
    }

    ProjectPtr project;
};

TEST_F(ProjectTest, testAddImagesToProject)
{
    QString imagePath1 = "asdf";
    QString imagePath2 = "blah";
    QString imagePath3 = "bleh";

    ProjectImagePtr newImage = ProjectImage::createProjectImage(imagePath1);

    QSignalSpy addSpy(project.data(), SIGNAL(imageAdded(ProjectImagePtr)));

    project->addProjectImage(newImage);

    ASSERT_EQ(1, addSpy.size());

    ASSERT_EQ(1, project->getProjectImages().size());

    EXPECT_EQ(newImage, project->getProjectImages().first());

    QStringList images;
    images << imagePath2 << imagePath3;

    ProjectUtils::addImagesToProject(project, images);

    ASSERT_EQ(3, addSpy.size());

    ASSERT_EQ(3, project->getProjectImages().size());

    EXPECT_EQ(imagePath1, project->getProjectImages()[0]->getImagePath());
    EXPECT_EQ(imagePath2, project->getProjectImages()[1]->getImagePath());
    EXPECT_EQ(imagePath3, project->getProjectImages()[2]->getImagePath());

    ProjectImagePtr oldImage = ProjectImage::createProjectImage(imagePath1);

    project->addProjectImage(oldImage);

    // can't add same image twice
    ASSERT_EQ(3, addSpy.size());
}

TEST_F(ProjectTest, testEquals)
{
    QStringList images1;
    images1 << "test" << "test2";

    QStringList images2;
    images2 << "test" << "test3";

    ProjectPtr otherProject = Project::createProject();

    EXPECT_TRUE(otherProject->equals(project));

    ProjectUtils::addImagesToProject(otherProject, images1);

    EXPECT_FALSE(project->equals(otherProject));

    ProjectUtils::addImagesToProject(project, images1);

    EXPECT_TRUE(project->equals(otherProject));

    otherProject = Project::createProject();

    ProjectUtils::addImagesToProject(otherProject, images2);

    EXPECT_FALSE(project->equals(otherProject));
}

