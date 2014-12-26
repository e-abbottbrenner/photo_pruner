#include "GoogleTest.h"

#include "ProjectImage.h"

#include <QJsonDocument>
#include <QSignalSpy>

class ProjectImageTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        path = "/this/is/a/dummy/path.png";
        projectImage.reset(new ProjectImage(path));
    }

    QString path;
    ProjectImagePtr projectImage;
};

TEST_F(ProjectImageTest, testGetImagePath)
{
    EXPECT_EQ(path, projectImage->getImagePath());
}

TEST_F(ProjectImageTest, testTags)
{
    QString tag1 = "blah";
    QString tag2 = "bleh";

    QSignalSpy tagAddedSpy(projectImage.data(), SIGNAL(tagAdded(ProjectImage*,QString)));
    QSignalSpy tagRemovedSpy(projectImage.data(), SIGNAL(tagRemoved(ProjectImage*,QString)));

    EXPECT_FALSE(projectImage->hasImageTag(tag1));
    EXPECT_FALSE(projectImage->hasImageTag(tag2));

    projectImage->addImageTag(tag1);
    projectImage->addImageTag(tag1);

    ASSERT_EQ(1, tagAddedSpy.size());

    EXPECT_EQ(projectImage.data(), tagAddedSpy[tagAddedSpy.size() - 1][0].value<ProjectImage*>());
    EXPECT_EQ(tag1, tagAddedSpy[tagAddedSpy.size() - 1][1].toString());

    projectImage->addImageTag(tag2);

    ASSERT_EQ(2, tagAddedSpy.size());

    EXPECT_EQ(projectImage.data(), tagAddedSpy[tagAddedSpy.size() - 1][0].value<ProjectImage*>());
    EXPECT_EQ(tag2, tagAddedSpy[tagAddedSpy.size() - 1][1].toString());

    EXPECT_TRUE(projectImage->hasImageTag(tag1));
    EXPECT_TRUE(projectImage->hasImageTag(tag2));

    EXPECT_EQ(2, projectImage->getImageTags().size());

    projectImage->removeImageTag(tag1);

    ASSERT_EQ(1, tagRemovedSpy.size());

    EXPECT_EQ(projectImage.data(), tagRemovedSpy[tagRemovedSpy.size() - 1][0].value<ProjectImage*>());
    EXPECT_EQ(tag1, tagRemovedSpy[tagRemovedSpy.size() - 1][1].toString());

    EXPECT_FALSE(projectImage->hasImageTag(tag1));
    EXPECT_TRUE(projectImage->hasImageTag(tag2));

    EXPECT_EQ(1, projectImage->getImageTags().size());
}

TEST_F(ProjectImageTest, testWillBePruned)
{
    EXPECT_FALSE(projectImage->getWillBePruned());

    QSignalSpy prunedSpy(projectImage.data(), SIGNAL(willBePrunedChanged(ProjectImage*,bool)));

    projectImage->setWillBePruned(true);

    EXPECT_TRUE(projectImage->getWillBePruned());

    ASSERT_EQ(1, prunedSpy.size());

    EXPECT_EQ(projectImage.data(), prunedSpy[0][0].value<ProjectImage*>());
    EXPECT_EQ(true, prunedSpy[0][1].toBool());

    projectImage->setWillBePruned(false);

    EXPECT_FALSE(projectImage->getWillBePruned());

    ASSERT_EQ(2, prunedSpy.size());
}

class ProjectImageJsonTest : public ProjectImageTest
{
protected:
    virtual void SetUp()
    {
        ProjectImageTest::SetUp();

        // make sure these are sorted
        QString tag1 = "blah";
        QString tag2 = "bleh";

        projectImage->addImageTag(tag1);
        projectImage->addImageTag(tag2);

        QString jsonString = QString("{ \"%1\":\"%2\", \"%3\": [ \"%4\", \"%5\" ], \"%6\": %7 }")
                .arg(ProjectImage::JsonKeys::IMAGE_PATH, path,
                     ProjectImage::JsonKeys::TAGS, tag1, tag2,
                     ProjectImage::JsonKeys::WILL_BE_PRUNED, "false");

        jsonObject = QJsonDocument::fromJson(jsonString.toUtf8()).object();
    }

    virtual void TearDown()
    {
        ProjectImageTest::TearDown();
    }

    QJsonObject jsonObject;
};

TEST_F(ProjectImageJsonTest, testToJson)
{
    EXPECT_EQ(jsonObject, projectImage->toJsonObject());
}

TEST_F(ProjectImageJsonTest, testFromJson)
{
    ProjectImagePtr fromJson(ProjectImage::fromJsonObject(jsonObject));

    EXPECT_TRUE(projectImage->equals(fromJson));
}
