#include "GoogleTest.h"

#include "ImageListModel.h"
#include "Project.h"
#include "ProjectImage.h"
#include "ResourcePath.h"

#include <QDir>
#include <QSignalSpy>

class ImageListModelTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        project = ProjectUtils::loadFromFile(QDir(RESOURCE_PATH).absoluteFilePath("projects/sampleproj.json"));

        model = ImageListModel::createImageListModel();

        model->setProject(project);
    }

    virtual void TearDown()
    {
        model.clear();

        project.clear();
    }

    ProjectPtr project;
    ImageListModelPtr model;
};

TEST_F(ImageListModelTest, testModelResetSignal)
{
    QSignalSpy aboutToResetSpy(model.data(), SIGNAL(modelAboutToBeReset()));
    QSignalSpy resetSpy(model.data(), SIGNAL(modelReset()));

    model->setProject(ProjectPtr());

    EXPECT_EQ(1, aboutToResetSpy.size());
    EXPECT_EQ(1, resetSpy.size());

    model->setProject(project);

    EXPECT_EQ(2, aboutToResetSpy.size());
    EXPECT_EQ(2, resetSpy.size());
}

TEST_F(ImageListModelTest, testData)
{
    ASSERT_EQ(2, model->rowCount(QModelIndex()));

    EXPECT_EQ("blah", model->data(model->index(0, 0), Qt::DisplayRole).toString());
    EXPECT_EQ("bleh", model->data(model->index(1, 0), Qt::DisplayRole).toString());
}

TEST_F(ImageListModelTest, testRemoveData)
{
    QSignalSpy aboutToRemoveSpy(model.data(), SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)));
    QSignalSpy removeSpy(model.data(), SIGNAL(rowsRemoved(QModelIndex,int,int)));

    project->removeProjectImage("bleh");

    ASSERT_EQ(1, aboutToRemoveSpy.size());
    ASSERT_EQ(1, removeSpy.size());

    EXPECT_EQ(1, aboutToRemoveSpy[0][1].toInt());
    EXPECT_EQ(1, removeSpy[0][1].toInt());
    EXPECT_EQ(1, aboutToRemoveSpy[0][2].toInt());
    EXPECT_EQ(1, removeSpy[0][2].toInt());

    EXPECT_EQ(1, model->rowCount(QModelIndex()));
}

TEST_F(ImageListModelTest, testAddData)
{
    QSignalSpy aboutToInsertSpy(model.data(), SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)));
    QSignalSpy insertSpy(model.data(), SIGNAL(rowsInserted(QModelIndex,int,int)));

    project->addProjectImage("blargh");

    ASSERT_EQ(1, aboutToInsertSpy.size());
    ASSERT_EQ(1, insertSpy.size());

    EXPECT_EQ(1, aboutToInsertSpy[0][1].toInt());
    EXPECT_EQ(1, insertSpy[0][1].toInt());
    EXPECT_EQ(1, aboutToInsertSpy[0][2].toInt());
    EXPECT_EQ(1, insertSpy[0][2].toInt());

    EXPECT_EQ(3, model->rowCount(QModelIndex()));
}

TEST_F(ImageListModelTest, testDataChanged)
{
    ProjectImagePtr image = project->getImage("bleh");

    // just to be sure we're changing it
    image->setWillBePruned(false);

    QSignalSpy dataChangedSpy(model.data(), SIGNAL(dataChanged(QModelIndex,QModelIndex)));

    image->setWillBePruned(true);

    ASSERT_EQ(1, dataChangedSpy.size());

    EXPECT_EQ(1, dataChangedSpy[0][0].toModelIndex().row());
}

TEST_F(ImageListModelTest, testSelectableFlags)
{
    EXPECT_TRUE(model->flags(QModelIndex()).testFlag(Qt::ItemIsSelectable));
}
