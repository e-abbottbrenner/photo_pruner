#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QObject>\

#include "TopLevelController.h"

#include <QList>
#include <QUrl>

class ProjectController : public QObject, public TopLevelController
{
    Q_OBJECT
public:
    explicit ProjectController(QObject *parent = 0);

    Q_INVOKABLE void importImages(const QList<QUrl>& imageUrls);
    Q_INVOKABLE void deletePrunedImages();
};

#endif // PROJECTCONTROLLER_H
