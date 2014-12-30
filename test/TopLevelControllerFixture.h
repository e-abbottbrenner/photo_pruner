#ifndef TOPLEVELCONTROLLERFIXTURE
#define TOPLEVELCONTROLLERFIXTURE

#include "GoogleTest.h"

#include "AppModel.h"
#include "TopLevelController.h"

template <typename T>
class TopLevelControllerFixture : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        controller.reset(createController());

        appModel = AppModel::createAppModel();

        controller->setAppModel(appModel);
    }

    virtual void TearDown()
    {
        controller.clear();
    }

    virtual T* createController() = 0;

    AppModelPtr appModel;
    QSharedPointer<T> controller;
};

#endif // TOPLEVELCONTROLLERFIXTURE

