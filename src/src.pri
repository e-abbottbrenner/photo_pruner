HEADERS += \
    $$PWD/ProjectImage.h \
    $$PWD/PrunerWindow.h \
    $$PWD/ProjectImagePtr.h \
    $$PWD/StringSet.h \
    $$PWD/ProjectPtr.h \
    $$PWD/Project.h

    !test {
      $$PWD/main.cpp \
    }

SOURCES += \
    $$PWD/ProjectImage.cpp \
    $$PWD/PrunerWindow.cpp \
    $$PWD/Project.cpp
