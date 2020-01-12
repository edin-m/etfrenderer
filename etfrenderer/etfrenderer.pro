#-------------------------------------------------
#
# Project created by QtCreator 2012-10-30T21:03:14
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns widgets

TARGET = etfrenderer
TEMPLATE = app

DESTDIR = ../build

INCLUDEPATH += include

CONFIG += testlib

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/framebuffer.cpp \
    src/scene.cpp \
    src/pluginmanager.cpp \
    pluginswindow.cpp \
    src/xmlutil.cpp \
    src/shape/triangleshape.cpp \
    src/shape/planeshape.cpp \
    src/camera/perspcamera.cpp \
    src/sceneloader.cpp \
    src/util/interpolation.cpp \
    test/testinterpolation.cpp \
    src/util/bbox.cpp \
    src/mapping/sphericalmapping.cpp \
    src/etfrenderer.cpp \
    src/shader/lensshader/thinlensshader.cpp \
    src/shader/textureshader/checker2dtextureshader.cpp \
    scenelistingwindow.cpp \
    src/shader/materialshader.cpp

HEADERS  += \
    mainwindow.h \
    include/*.h \
    include/plugin/* \
    include/shader.h \
    include/shape.h \
    include/renderer.h \
    include/scene.h \
    include/pluginmanager.h \
    include/etfrenderer.h \
    pluginswindow.h \
    include/xmlutil.h \
    include/plugin/lightplugin.h \
    include/light.h \
    include/shape/triangleshape.h \
    include/shape/planeshape.h \
    include/camera.h \
    include/camera/perspcamera.h \
    include/sceneloader.h \
    include/color.h \
    include/shader/textureshader.h \
    include/util/interpolation.h \
    test/testinterpolation.h \
    include/util/bbox.h \
    include/mapping.h \
    include/mapping/sphericalmapping.h \
    include/sampler.h \
    include/sampler/randomsampler.h \
    include/util/util.h \
    include/shader/lensshader.h \
    include/shader/lensshader/thinlensshader.h \
    include/util/quadtree.h \
    include/util/sl.h \
    include/shader/textureshader/checker2dtextureshader.h \
    scenelistingwindow.h \
    include/shader/materialshader.h \
    include/exception.h

FORMS    += \
    mainwindow.ui \
    pluginswindow.ui \
    scenelistingwindow.ui

OTHER_FILES += ../doc/*
