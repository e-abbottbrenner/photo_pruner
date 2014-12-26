HEADERS += \
    $$PWD/ProjectImage.h \
    $$PWD/PrunerWindow.h \
    $$PWD/PruningProject.h

    !test {
      $$PWD/main.cpp \
    }

SOURCES += \
    $$PWD/ProjectImage.cpp \
    $$PWD/PrunerWindow.cpp \
    $$PWD/PruningProject.cpp
