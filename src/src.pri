HEADERS += \
    $$PWD/ProjectImage.h \
    $$PWD/ProjectImagePtr.h \
    $$PWD/StringSet.h \
    $$PWD/ProjectPtr.h \
    $$PWD/Project.h \
    $$PWD/ImageListModel.h \
    $$PWD/ImageListModelPtr.h \
    $$PWD/AppController.h \
    $$PWD/AppModel.h \
    $$PWD/AppModelPtr.h \
    $$PWD/ProjectController.h \
    $$PWD/ImageController.h \
    $$PWD/TopLevelController.h

SOURCES += \
    $$PWD/ProjectImage.cpp \
    $$PWD/Project.cpp \
    $$PWD/ImageListModel.cpp \
    $$PWD/AppController.cpp \
    $$PWD/AppModel.cpp \
    $$PWD/ProjectController.cpp \
    $$PWD/ImageController.cpp \
    $$PWD/TopLevelController.cpp


!test {
    SOURCES += $$PWD/main.cpp \
}
