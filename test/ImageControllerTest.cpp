#include "TopLevelControllerFixture.h"

#include "ImageController.h"
#include "Project.h"
#include "ProjectImage.h"

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

    controller->removeFromProject();

    EXPECT_TRUE(appModel->getCurrentProject()->getImage(image->getImagePath()).isNull());
}
