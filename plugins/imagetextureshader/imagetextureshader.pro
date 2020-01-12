IME = imagetextureshaderplugin

HEADERS += $${IME}.h \
    imagetextureshader.h

SOURCES += $${IME}.cpp \
    imagetextureshader.cpp

TEMPLATE = lib

QT += core gui xml xmlpatterns widgets

Debug{
    LIBS += -L../../build/ -llibetfrendererd
} else {
    LIBS += -L../../build/ -llibetfrenderer
}

OBJECTS_DIR = ../../dump/$${IME}
MOC_DIR = ../../dump/$${IME}
RCC_DIR = ../../dump/$${IME}

INCLUDEPATH = ../../etfrenderer/include
DESTDIR = ../../build/plugins

TARGET = $$qtLibraryTarget($$IME)

CONFIG += plugin

DISTFILES += \
    imagetextureshader.json
