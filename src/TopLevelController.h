#ifndef TOPLEVELCONTROLLER_H
#define TOPLEVELCONTROLLER_H

#include <QObject>

#include "AppModelPtr.h"
#include "ImageListModelPtr.h"
#include "ProjectPtr.h"

class TopLevelController
{
public:
    void setAppModel(AppModelPtr appModel);

protected:
    AppModelPtr appModel() const;
    ProjectPtr currentProject() const;

private:
    AppModelPtr appModelPrivate;
};

#endif // TOPLEVELCONTROLLER_H
