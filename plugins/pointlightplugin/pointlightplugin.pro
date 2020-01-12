IME = pointlightplugin
APP_SRC = ../../etfrenderer/src

HEADERS += $${IME}.h \
    pointlight.h

SOURCES += $${IME}.cpp \
    pointlight.cpp

TEMPLATE = lib

QT +=	core gui xml xmlpatterns widgets

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
    pointlightplugin.json
