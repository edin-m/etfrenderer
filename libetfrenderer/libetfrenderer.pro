IME = libetfrenderer
APP_SRC = ../etfrenderer/src

DEFINES += ER_LIB

TEMPLATE = lib
CONFIG += static

QT += core gui xml xmlpatterns widgets

OBJECTS_DIR = ../dump/$${IME}
MOC_DIR = ../dump/$${IME}
RCC_DIR = ../dump/$${IME}

DESTDIR = ../build

TARGET = $$qtLibraryTarget($$IME)

INCLUDEPATH += include
INCLUDEPATH += ../etfrenderer/include

HEADERS += \
    testlib.h \
    shape/triangleshape.h \
    scene.h \
    xmlutil.h \
    util/bbox.h \
    util/sl.h \
    mapping.h \
    mapping/sphericalmapping.h \
    shader/materialshader.h

SOURCES += \
    $${APP_SRC}/shape/triangleshape.cpp \
    $${APP_SRC}/scene.cpp \
    $${APP_SRC}/xmlutil.cpp \
    $${APP_SRC}/util/bbox.cpp \
    $${APP_SRC}/mapping/sphericalmapping.cpp \
    $${APP_SRC}/shader/materialshader.cpp
