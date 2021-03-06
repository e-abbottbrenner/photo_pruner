#include "ImageListModel.h"

#include "Project.h"
#include "ProjectImage.h"

#include <cassert>
#include <QFileInfo>
#include <QPixmap>
#include <QUrl>

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
            connect(project.data(), &Project::imageChanged, this, &ImageListModel::onImageChanged);
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

    QList<QString> tags;

    switch(role)
    {
    case Qt::DisplayRole:
        return QFileInfo(image->getImagePath()).fileName();
    case Qt::DecorationRole:
        return QPixmap(image->getImagePath());
    case PathRole:
        return image->getImagePath();
    case UrlRole:
        return QUrl::fromLocalFile(image->getImagePath());
    case PrunedRole:
        return image->getWillBePruned();
    case TagsRole:
        tags = image->getImageTags().toList();
        qSort(tags);
        return tags;
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags ImageListModel::flags(const QModelIndex&) const
{
    return Qt::ItemIsSelectable;
}

QHash<int, QByteArray> ImageListModel::roleNames() const
{
    QHash<int, QByteArray> names = QAbstractListModel::roleNames();

    names.insert(PathRole, "sourcePath");
    names.insert(UrlRole, "sourceUrl");
    names.insert(PrunedRole, "pruned");
    names.insert(TagsRole, "tags");

    return names;
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

void ImageListModel::onImageChanged(const QString& imagePath)
{
    // find the first instance of the path
    int row = imagePaths.indexOf(imagePath);

    // signal for data changed
    emit dataChanged(index(row), index(row));
}
