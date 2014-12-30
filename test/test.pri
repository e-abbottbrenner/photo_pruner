QT += testlib

INCLUDEPATH += $$PWD/../src/

SOURCES += \
    $$PWD/ProjectImageTest.cpp \
    $$PWD/PrintHelpers.cpp \
    $$PWD/ProjectTest.cpp \
    $$PWD/ImageListModelTest.cpp \
    $$PWD/AppModelTest.cpp \
    $$PWD/AppControllerTest.cpp \
    $$PWD/ProjectControllerTest.cpp \
    $$PWD/ImageControllerTest.cpp \
    $$PWD/ImageListFilterModelTest.cpp

HEADERS += \
    $$PWD/GoogleTest.h \
    $$PWD/PrintHelpers.h \
    $$PWD/ResourcePath.h \
    $$PWD/TopLevelControllerFixture.h
