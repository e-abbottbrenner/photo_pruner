#include "TopLevelControllerFixture.h"

#include "ImageController.h"

class ImageControllerTest : public TopLevelControllerFixture<ImageController>
{
protected:
    virtual ImageController* createController()
    {
        return new ImageController;
    }
}
