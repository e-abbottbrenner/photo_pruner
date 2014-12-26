QT += gui widgets

include(src/src.pri)

INCLUDEPATH += $$PWD/include

LIBS += -L$$PWD/lib

test {
  LIBS += -lgtestd -lgtest_main-mdd

  include(test/test.pri)
}
