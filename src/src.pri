HEADERS += \
    $$PWD/ProjectImage.h \
    $$PWD/ProjectImagePtr.h \
    $$PWD/StringSet.h \
    $$PWD/ProjectPtr.h \
    $$PWD/Project.h

SOURCES += \
    $$PWD/ProjectImage.cpp \
    $$PWD/Project.cpp


!test {
    SOURCES += $$PWD/main.cpp \
}
