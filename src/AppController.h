#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

#include "AppModelPtr.h"
#include "ImageListModelPtr.h"
#include "ProjectPtr.h"

#include <QUrl>

class QAbstractItemModel;

class AppController : public QObject
{
    Q_OBJECT

    /* Expose the following items via properties:
     * * The item model(s) for displaying and editing the photo list
     * * The project url to support standard save operation
     */

    Q_PROPERTY(QAbstractItemModel* projectModel READ getRawProjectModel NOTIFY projectModelChanged)
    Q_PROPERTY(QUrl projectUrl READ getProjectUrl NOTIFY projectUrlChanged)
    Q_PROPERTY(QUrl currentImageUrl READ getCurrentImageUrl NOTIFY currentImageUrlChanged)

public:
    AppController(QObject *parent = 0);

    QAbstractItemModel* getRawProjectModel() const;
    QUrl getProjectUrl() const;
    QUrl getCurrentImageUrl() const;

    void setAppModel(AppModelPtr appModel);

signals:
    // this is just for the sake of qml bindings, the model itself never changes so this is pointless otherwise
    void projectModelChanged(QAbstractItemModel* model);
    void projectUrlChanged(QUrl projectUrl);
    void currentImageUrlChanged(QUrl url);

    /* Expose the following functions via slots for qml usage
     * * Open project (path)
     * * Save project (path)
     * * Import images (path list)
     */
public slots:
    void openProject(const QUrl& projectUrl);
    void saveProject(const QUrl& projectUrl);

    void importImages(const QList<QUrl>& imageUrls);

    void determineCurrentImageUrl(int currentIndex);

private:
    AppModelPtr appModel;

    QUrl currentProjectUrl;
    QUrl currentImageUrl;
};

#endif // APPCONTROLLER_H
