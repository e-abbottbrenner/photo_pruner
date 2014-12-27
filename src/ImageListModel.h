#ifndef IMAGELISTMODEL_H
#define IMAGELISTMODEL_H

#include <QAbstractListModel>

#include "ImageListModelPtr.h"
#include "ProjectImagePtr.h"
#include "ProjectPtr.h"

class ImageListModel : public QAbstractListModel
{
public:
    static ImageListModelPtr createImageListModel();

    void setProject(ProjectPtr project);
    ProjectPtr getProject() const;

    virtual int rowCount(const QModelIndex &) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

private slots:
    void refreshImagePaths();
    void onImageAdded(const QString& imagePath);
    void onImageRemoved(const QString& imagePath);

private:
    ImageListModel();

    ProjectPtr project;

    QStringList imagePaths;
};

#endif // IMAGELISTMODEL_H
