#include "ImageController.h"

#include "AppModel.h"
#include "ImageListModel.h"

ImageController::ImageController(QObject *parent) : QObject(parent)
{
}


QUrl ImageController::getCurrentImageUrl() const
{
    return currentImageUrl;
}

/*!
 * \brief ImageController::setCurrentIndex sets the idnex of the current image
 * \param currentIndex
 */
void ImageController::setCurrentIndex(int currentIndex)
{
    QUrl newImageUrl = appModel()->getProjectModel()->data(appModel()->getProjectModel()->index(currentIndex), ImageListModel::UrlRole).toUrl();

    if(newImageUrl != currentImageUrl)
    {
        currentImageUrl = newImageUrl;

        emit currentImageUrlChanged(newImageUrl);
    }
}
