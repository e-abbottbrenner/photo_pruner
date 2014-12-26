#ifndef PRUNINGPROJECT_H
#define PRUNINGPROJECT_H

#include <QObject>

class PruningProject : public QObject
{
    Q_OBJECT
public:
    explicit PruningProject(QObject *parent = 0);
    ~PruningProject();

signals:

public slots:
};

#endif // PRUNINGPROJECT_H
