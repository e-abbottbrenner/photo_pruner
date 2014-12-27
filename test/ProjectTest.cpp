#include "GoogleTest.h"

#include "ResourcePath.h"
#include "Project.h"
#include "ProjectImage.h"

#include <QDir>
#include <QSignalSpy>
#include <QStringList>
#include <QTemporaryDir>

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

    QSignalSpy addSpy(project.data(), SIGNAL(imageAdded(QString)));

    project->addProjectImage(imagePath1);

    ASSERT_EQ(1, addSpy.size());

    ASSERT_EQ(1, project->getProjectImages().size());

    EXPECT_EQ(imagePath1, addSpy[0][0].toString());

    EXPECT_EQ(imagePath1, project->getProjectImages().first()->getImagePath());

    QStringList images;
    images << imagePath2 << imagePath3;

    ProjectUtils::addImagesToProject(project, images);

    ASSERT_EQ(3, addSpy.size());

    ASSERT_EQ(3, project->getProjectImages().size());

    EXPECT_EQ(imagePath1, project->getProjectImages()[0]->getImagePath());
    EXPECT_EQ(imagePath2, project->getProjectImages()[1]->getImagePath());
    EXPECT_EQ(imagePath3, project->getProjectImages()[2]->getImagePath());

    project->addProjectImage(imagePath1);

    // can't add same image twice
    ASSERT_EQ(3, addSpy.size());
}

TEST_F(ProjectTest, testRemoveImagesFromProject)
{
    QString imagePath = "asdf";

    QSignalSpy removeSpy(project.data(), SIGNAL(imageRemoved(QString)));

    project->removeProjectImage(imagePath);

    EXPECT_EQ(0, removeSpy.size());

    project->addProjectImage(imagePath);
    project->removeProjectImage(imagePath);

    EXPECT_EQ(1, removeSpy.size());

    EXPECT_EQ(imagePath, removeSpy[0][0].toString());

    EXPECT_EQ(0, project->getProjectImages().size());
}

TEST_F(ProjectTest, testGetProjectImage)
{
    QString imagePath = "asdf";

    EXPECT_EQ(ProjectImagePtr(), project->getImage(imagePath));

    project->addProjectImage(imagePath);

    ProjectImagePtr image = project->getImage(imagePath);

    EXPECT_FALSE(image.isNull());

    // always returns same pointer
    EXPECT_EQ(image, project->getImage(imagePath));
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

TEST_F(ProjectTest, testPruneProject)
{
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

    ProjectUtils::pruneProject(project);

    EXPECT_TRUE(QFileInfo(streamPath).exists());
    EXPECT_FALSE(QFileInfo(sunsetPath).exists());
}


TEST_F(ProjectTest, testToJsonObject)
{

}

TEST_F(ProjectTest, testFromJsonObject)
{

}
