IME = raytracerplugin
APP_SRC = ../../etfrenderer/src

HEADERS += raytracerplugin.h \
    raytracer.h

SOURCES += raytracerplugin.cpp \
    raytracer.cpp

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

FORMS +=

#LIBS += -fopenmp
#QMAKE_CXXFLAGS += -fopenmp

DISTFILES += \
    raytracer.json
