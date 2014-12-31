#include "ImageListFilterModel.h"

#include "ImageListModel.h"
#include "Project.h"
#include "ProjectImage.h"

#include <cassert>

ImageListFilterModel::ImageListFilterModel(ImageListModelPtr baseModel)
    : baseModel(baseModel)
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
        pruningFilterOk = true == image->getWillBePruned();
        break;
    case PruningFilters::ShowUnpruned:
        // not to be pruned so show
        pruningFilterOk = false == image->getWillBePruned();
        break;
    case PruningFilters::ShowAll:
    default:
        // just show everything
        break;
    }

    // TODO: check tags later
    return pruningFilterOk;
}
