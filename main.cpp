#include <QApplication>

#include "PrunerWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    PrunerWindow mainWin;

    mainWin.showMaximized();

    return app.exec();
}
