QT += gui widgets qml quick

include(src/src.pri)
include(qml/qml.pri)

CONFIG += embed_manifest_exe

INCLUDEPATH += $$PWD/include

LIBS += -L$$PWD/lib

DEFINES += REPOSITORY_PATH=\\\"$$PWD\\\"

test {
  LIBS += -lgtestd -lgtest_main-mdd

  include(test/test.pri)
}

RESOURCES += \
    resources.qrc

HEADERS +=

SOURCES +=
