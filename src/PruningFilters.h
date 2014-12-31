#ifndef PRUNINGFILTERS
#define PRUNINGFILTERS

#include <QObject>

class PruningFilters : public QObject
{
    Q_OBJECT

    Q_ENUMS(PruningFilter)

public:
    enum PruningFilter
    {
        ShowAll,
        ShowPruned,
        ShowUnpruned
    };
};

typedef PruningFilters::PruningFilter PruningFilter;

#endif // PRUNINGFILTERS

