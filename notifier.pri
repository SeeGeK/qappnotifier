INCLUDEPATH += $$PWD

HEADERS += $$PWD/notifier.h \
           $$PWD/notifytypes.h


HEADERS += $$files($$PWD/include/*.h)
SOURCES += $$files($$PWD/src/*.cpp)
