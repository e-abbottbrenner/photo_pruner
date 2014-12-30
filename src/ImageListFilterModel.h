#ifndef IMAGELISTFILTERMODEL_H
#define IMAGELISTFILTERMODEL_H

#include <QSortFilterProxyModel>

#include "ImageListFilterModelPtr.h"
#include "ImageListModelPtr.h"
#include "PruningFilters.h"

class ImageListFilterModel : public QSortFilterProxyModel
{
public:
    static ImageListFilterModelPtr createImageListFilterModel(ImageListModelPtr baseModel);

    void setPruningFilter(PruningFilter filter);
    PruningFilter getPruningFilter() const;

protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &) const;

private:
    ImageListFilterModel(ImageListModelPtr baseModel);

    ImageListModelPtr baseModel;

    PruningFilter pruningFilter;
};

#endif // IMAGELISTFILTERMODEL_H
