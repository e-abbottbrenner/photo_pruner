#include "TopLevelControllerFixture.h"

#include "ImageController.h"
#include "Project.h"
#include "ProjectImage.h"

#include <QSignalSpy>

class ImageControllerTest : public TopLevelControllerFixture<ImageController>
{
protected:
    virtual void SetUp()
    {
        TopLevelControllerFixture<ImageController>::SetUp();

        QString imagePath = "asdf";

        appModel->getCurrentProject()->addProjectImage(imagePath);

        image = appModel->getCurrentProject()->getImage(imagePath);

        controller->setImage(imagePath);
    }

    virtual void TearDown()
    {
        image.clear();

        TopLevelControllerFixture<ImageController>::SetUp();
    }

    virtual ImageController* createController()
    {
        return new ImageController;
    }

    ProjectImagePtr image;
};

TEST_F(ImageControllerTest, testSetWillBePruned)
{
    EXPECT_FALSE(image->getWillBePruned());

    QSignalSpy willBePrunedChangedSpy(controller.data(), SIGNAL(willBePrunedChanged(bool)));

    controller->setWillBePruned(true);

    EXPECT_TRUE(image->getWillBePruned());

    ASSERT_EQ(1, willBePrunedChangedSpy.size());

    EXPECT_EQ(true, willBePrunedChangedSpy[0][0].toBool());

    controller->setWillBePruned(false);

    EXPECT_FALSE(image->getWillBePruned());

    ASSERT_EQ(2, willBePrunedChangedSpy.size());

    EXPECT_FALSE(willBePrunedChangedSpy[1][0].toBool());
}

TEST_F(ImageControllerTest, testSetRotation)
{
    EXPECT_EQ(0, image->getRotation());

    QSignalSpy rotationChangedSpy(controller.data(), SIGNAL(rotationChanged(int)));

    controller->setRotation(540);

    ASSERT_EQ(1, rotationChangedSpy.size());

    EXPECT_EQ(180, rotationChangedSpy[0][0].toInt());

    EXPECT_EQ(180, image->getRotation());
}

TEST_F(ImageControllerTest, testRemoveFromProject)
{
    EXPECT_TRUE(!appModel->getCurrentProject()->getImage(image->getImagePath()).isNull());

    image->addImageTag("tag");

    QSignalSpy tagsChangedSpy(controller.data(), SIGNAL(tagsChanged(QStringList)));

    controller->removeFromProject();

    EXPECT_TRUE(appModel->getCurrentProject()->getImage(image->getImagePath()).isNull());

    ASSERT_EQ(1, tagsChangedSpy.size());

    EXPECT_EQ(QStringList(), tagsChangedSpy[0][0].toStringList());
}

TEST_F(ImageControllerTest, testAddTag)
{
    QString newTag = "tag";

    EXPECT_FALSE(image->getImageTags().contains(newTag));

    QSignalSpy tagsChangedSpy(controller.data(), SIGNAL(tagsChanged(QStringList)));

    controller->addTag(newTag);

    EXPECT_TRUE(image->getImageTags().contains(newTag));

    ASSERT_EQ(1, tagsChangedSpy.size());

    EXPECT_EQ(QStringList(newTag), tagsChangedSpy[0][0].toStringList());
}

TEST_F(ImageControllerTest, testRemoveTag)
{
    QString tag = "tag";

    image->addImageTag(tag);

    EXPECT_TRUE(image->getImageTags().contains(tag));

    QSignalSpy tagsChangedSpy(controller.data(), SIGNAL(tagsChanged(QStringList)));

    controller->removeTag(tag);

    EXPECT_FALSE(image->getImageTags().contains(tag));

    ASSERT_EQ(1, tagsChangedSpy.size());

    EXPECT_EQ(QStringList(), tagsChangedSpy[0][0].toStringList());
}

TEST_F(ImageControllerTest, testSetImage)
{
    EXPECT_TRUE(controller->imageAvailable());

    QSignalSpy imageAvailableChanged(controller.data(), SIGNAL(imageAvailableChanged(bool)));
    QSignalSpy tagsChangedSpy(controller.data(), SIGNAL(tagsChanged(QStringList)));
    QSignalSpy willBePrunedChangedSpy(controller.data(), SIGNAL(willBePrunedChanged(bool)));
    QSignalSpy rotationChangedSpy(controller.data(), SIGNAL(rotationChanged(int)));

    controller->setImage(QString());

    EXPECT_FALSE(controller->imageAvailable());

    ASSERT_EQ(1, imageAvailableChanged.size());
    EXPECT_EQ(0, tagsChangedSpy.size());
    EXPECT_EQ(0, willBePrunedChangedSpy.size());
    EXPECT_EQ(0, rotationChangedSpy.size());

    EXPECT_FALSE(imageAvailableChanged[0][0].toBool());

    QString tag = "tag";
    image->addImageTag(tag);
    image->setWillBePruned(true);
    image->setRotation(90);

    controller->setImage(image->getImagePath());

    EXPECT_TRUE(controller->imageAvailable());

    ASSERT_EQ(2, imageAvailableChanged.size());

    EXPECT_TRUE(imageAvailableChanged[1][0].toBool());

    ASSERT_EQ(1, tagsChangedSpy.size());

    EXPECT_EQ(QStringList(tag), tagsChangedSpy[0][0].toStringList());

    ASSERT_EQ(1, willBePrunedChangedSpy.size());

    EXPECT_EQ(true, willBePrunedChangedSpy[0][0].toBool());

    ASSERT_EQ(1, rotationChangedSpy.size());

    EXPECT_EQ(90, rotationChangedSpy[0][0].toInt());
}
