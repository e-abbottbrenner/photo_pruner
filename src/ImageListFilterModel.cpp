#include "ImageListFilterModel.h"

#include "ImageListModel.h"
#include "Project.h"
#include "ProjectImage.h"

#include <cassert>
#include <QDebug>

ImageListFilterModel::ImageListFilterModel(ImageListModelPtr baseModel)
    : baseModel(baseModel), pruningFilter(PruningFilters::ShowAll)
{
    assert(baseModel);

    setSourceModel(baseModel.data());
}

/*!
 * \brief ImageListFilterModel::createImageListFilterModel creates the list model
 * \return
 */
ImageListFilterModelPtr ImageListFilterModel::createImageListFilterModel(ImageListModelPtr baseModel)
{
    return ImageListFilterModelPtr(new ImageListFilterModel(baseModel));
}

void ImageListFilterModel::setPruningFilter(PruningFilter filter)
{
    if(pruningFilter != filter)
    {
        pruningFilter = filter;
        invalidateFilter();
    }
}

PruningFilter ImageListFilterModel::getPruningFilter() const
{
    return pruningFilter;
}

QString ImageListFilterModel::getTagFilter() const
{
    return tagFilterSubstring;
}

void ImageListFilterModel::setTagFilter(const QString& tagSubstring)
{
    if(tagFilterSubstring != tagSubstring)
    {
        tagFilterSubstring = tagSubstring;
        invalidateFilter();
    }
}

bool ImageListFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex&) const
{
    ProjectPtr project = baseModel->getProject();

    assert(project);

    bool pruningFilterOk = true;

    QString imagePath = baseModel->data(baseModel->index(sourceRow), ImageListModel::PathRole).toString();

    ProjectImagePtr image = project->getImage(imagePath);

    switch(pruningFilter)
    {
    case PruningFilters::ShowPruned:
        // will be pruned so show
        pruningFilterOk = image->getWillBePruned();
        break;
    case PruningFilters::ShowUnpruned:
        // not to be pruned so show
        pruningFilterOk = !image->getWillBePruned();
        break;
    case PruningFilters::ShowAll:
    default:
        // just show everything
        break;
    }

    bool tagMatch = false;

    if(tagFilterSubstring.isEmpty())
    {
        tagMatch = true;
    }
    else
    {
        foreach(QString tag, image->getImageTags())
        {
            if(tag.toLower().contains(tagFilterSubstring.toLower()))
            {// don't be case sensitive, it's annoying
                tagMatch = true;
                break;
            }
        }
    }

    return pruningFilterOk && tagMatch;
}
