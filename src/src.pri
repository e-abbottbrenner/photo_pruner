HEADERS += \
    $$PWD/ProjectImage.h \
    $$PWD/ProjectImagePtr.h \
    $$PWD/StringSet.h \
    $$PWD/ProjectPtr.h \
    $$PWD/Project.h \
    $$PWD/ImageListModel.h \
    $$PWD/ImageListModelPtr.h

SOURCES += \
    $$PWD/ProjectImage.cpp \
    $$PWD/Project.cpp \
    $$PWD/ImageListModel.cpp


!test {
    SOURCES += $$PWD/main.cpp \
}
