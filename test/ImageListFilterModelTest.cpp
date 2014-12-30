#include "GoogleTest.h"

#include "ImageListFilterModel.h"
#include "ImageListModel.h"
#include "Project.h"
#include "ProjectImage.h"
#include "ResourcePath.h"

#include <QDir>

class ImageListFilterModelTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        baseModel = ImageListModel::createImageListModel();
        filterModel = ImageListFilterModel::createImageListFilterModel(baseModel);
        baseModel->setProject(ProjectUtils::loadFromFile(QDir(RESOURCE_PATH).absoluteFilePath("projects/sampleproj.json")));

        unprunedImage = baseModel->getProject()->getImage("blah");
        prunedImage = baseModel->getProject()->getImage("bleh");

        unprunedImage->setWillBePruned(false);
        prunedImage->setWillBePruned(true);
    }

    virtual void TearDown()
    {
        baseModel.clear();
        filterModel.clear();
        unprunedImage.clear();
        prunedImage.clear();
    }

    ImageListModelPtr baseModel;
    ImageListFilterModelPtr filterModel;
    ProjectImagePtr unprunedImage;
    ProjectImagePtr prunedImage;
};

TEST_F(ImageListFilterModelTest, testPruningFilters)
{
    filterModel->setPruningFilter(PruningFilters::ShowAll);

    EXPECT_EQ(2, filterModel->rowCount());

    filterModel->setPruningFilter(PruningFilters::ShowPruned);

    EXPECT_EQ(1, filterModel->rowCount());

    // this is the pruned one
    EXPECT_EQ(prunedImage->getImagePath(), filterModel->data(filterModel->index(0, 0), ImageListModel::PathRole).toString());

    filterModel->setPruningFilter(PruningFilters::ShowUnpruned);

    EXPECT_EQ(1, filterModel->rowCount());

    // this is the unpruned one
    EXPECT_EQ(unprunedImage->getImagePath(), filterModel->data(filterModel->index(0, 0), ImageListModel::PathRole).toString());
}

TEST_F(ImageListFilterModelTest, testDynamicUpdate)
{
    filterModel->setPruningFilter(PruningFilters::ShowUnpruned);

    EXPECT_EQ(1, filterModel->rowCount());

    prunedImage->setWillBePruned(false);

    // now that the pruned image is updated, it should go in the pruned model
    EXPECT_EQ(2, filterModel->rowCount());
}
