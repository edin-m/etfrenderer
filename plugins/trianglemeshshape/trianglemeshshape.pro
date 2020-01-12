IME = trianglemeshshape
APP_SRC = ../../etfrenderer/src

HEADERS += trianglemeshshapeplugin.h \
    trianglemeshshape.h \
    emdobject.h

SOURCES += trianglemeshshapeplugin.cpp \
    trianglemeshshape.cpp \
    emdobject.cpp

TEMPLATE = lib

DEFINES += ETR_DEVELOPMENT

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
    trianglemeshshape.json
