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

    controller->setWillBePruned(true);

    EXPECT_TRUE(image->getWillBePruned());

    controller->setWillBePruned(false);

    EXPECT_FALSE(image->getWillBePruned());
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

    controller->setImage(QString());

    EXPECT_FALSE(controller->imageAvailable());

    ASSERT_EQ(1, imageAvailableChanged.size());
    EXPECT_EQ(0, tagsChangedSpy.size());

    EXPECT_FALSE(imageAvailableChanged[0][0].toBool());

    QString tag = "tag";
    image->addImageTag(tag);

    controller->setImage(image->getImagePath());

    EXPECT_TRUE(controller->imageAvailable());

    ASSERT_EQ(2, imageAvailableChanged.size());

    EXPECT_TRUE(imageAvailableChanged[1][0].toBool());

    ASSERT_EQ(1, tagsChangedSpy.size());

    EXPECT_EQ(QStringList(tag), tagsChangedSpy[0][0].toStringList());
}
