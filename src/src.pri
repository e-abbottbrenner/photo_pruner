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
    $$PWD/AppModelPtr.h

SOURCES += \
    $$PWD/ProjectImage.cpp \
    $$PWD/Project.cpp \
    $$PWD/ImageListModel.cpp \
    $$PWD/AppController.cpp \
    $$PWD/AppModel.cpp


!test {
    SOURCES += $$PWD/main.cpp \
}
