IME = softwarerendererplugin
APP_SRC = ../../etfrenderer/SRCMOC

HEADERS += softwarerendererplugin.h \
    softwarerenderer.h

SOURCES += softwarerendererplugin.cpp \
    softwarerenderer.cpp

TEMPLATE = lib

QT += core xml xmlpatterns widgets

Debug{
    LIBS += -L../../build/ -llibetfrendererd
} else {
    LIBS += -L../../build/ -llibetfrenderer
}

OBJECTS_DIR = ../../dump/$$IME
MOC_DIR = ../../dump/$$IME
RCC_DIR = ../../dump/$$IME

INCLUDEPATH += ../../etfrenderer/include
INCLUDEPATH += E:\glm-0.9.4.4\glm-0.9.4.4

DESTDIR = ../../build/plugins

TARGET = $$qtLibraryTarget($$IME)

CONFIG += plugin

DISTFILES += \
    softwarerenderer.json
