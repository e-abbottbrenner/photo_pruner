#include "ImageListModel.h"

#include "Project.h"
#include "ProjectImage.h"

#include <cassert>
#include <QFileInfo>
#include <QPixmap>

ImageListModel::ImageListModel()
{

}

/*!
 * \brief ImageListModel::createImageListModel creates a new image list model
 * \return
 */
ImageListModelPtr ImageListModel::createImageListModel()
{
    return ImageListModelPtr(new ImageListModel);
}

void ImageListModel::setProject(ProjectPtr project)
{
    if(this->project != project)
    {
        this->project = project;

        if(project)
        {
            connect(project.data(), &Project::imageAdded, this, &ImageListModel::onImageAdded);
            connect(project.data(), &Project::imageRemoved, this, &ImageListModel::onImageRemoved);
        }

        refreshImagePaths();
    }
}

ProjectPtr ImageListModel::getProject() const
{
    return project;
}

int ImageListModel::rowCount(const QModelIndex&) const
{
    return imagePaths.size();
}

QVariant ImageListModel::data(const QModelIndex& index, int role) const
{
    if(!project || !index.isValid())
    {// no data
        return QVariant();
    }

    int row = index.row();

    ProjectImagePtr image = project->getImage(imagePaths[row]);

    assert(image);

    switch(role)
    {
    case Qt::DisplayRole:
        return QFileInfo(image->getImagePath()).fileName();
    case Qt::DecorationRole:
        return QPixmap(image->getImagePath());
    default:
        break;
    }

    return QVariant();
}

void ImageListModel::refreshImagePaths()
{
    beginResetModel();

    if(project)
    {
        imagePaths = project->getProjectImagePaths();
    }
    else
    {
        imagePaths.clear();
    }

    endResetModel();
}

void ImageListModel::onImageAdded(const QString& imagePath)
{
    assert(project);

    int insertionPoint = project->getProjectImagePaths().indexOf(imagePath);

    beginInsertRows(QModelIndex(), insertionPoint, insertionPoint);

    imagePaths.insert(insertionPoint, imagePath);

    endInsertRows();
}

void ImageListModel::onImageRemoved(const QString& imagePath)
{
    assert(project);

    int removalPoint = imagePaths.indexOf(imagePath);

    beginRemoveRows(QModelIndex(), removalPoint, removalPoint);

    imagePaths.removeAt(removalPoint);

    endRemoveRows();
}
