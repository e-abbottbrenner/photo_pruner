QT += testlib

INCLUDEPATH += $$PWD/../src/

SOURCES += \
    $$PWD/ProjectImageTest.cpp \
    $$PWD/PrintHelpers.cpp \
    $$PWD/ProjectTest.cpp \
    $$PWD/ImageListModelTest.cpp

HEADERS += \
    $$PWD/GoogleTest.h \
    $$PWD/PrintHelpers.h \
    $$PWD/ResourcePath.h
