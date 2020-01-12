#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <QDir>
#include <QDebug>
#include <QXmlQuery>

#include "types.h"
#include "structs.h"
#include "etfrenderer.h"
#include "pluginmanager.h"

#include "camera.h"
#include "shape.h"
#include "shader.h"

const Shape* findCoreShape(const QString& xml);

/**
  Singleton klasa za ucitavanje scena.
  */
class SceneLoader
{
    Scene* scene;
    Etfrenderer* etfrenderer;
    const PluginManager* pluginmanager;

    /**
      Try to load xml shader using plugins.
      */
    bool loadFromShaderPlugins(const QString& xml);

    /**
      Try to load xml shader using built in shaders.
      */
    bool loadFromBuiltInShader(const QString& xml);

    /**
      Load shaders
      */
    void loadShaders(QXmlQuery& query);

    const Shape* findCoreShape(const QString& xml);
    void loadShapes(QXmlQuery& query);

    void loadLights(QXmlQuery& query);
    void loadCameras(QXmlQuery& query);

    SceneLoader(Etfrenderer* renderer);
public:
    static SceneLoader& instance(Etfrenderer* renderer)
    {
        static SceneLoader loader(renderer);
        return loader;
    }

    void loadScene(const QString& path = QString(""));
private:
    SceneLoader(SceneLoader const&);
    void operator=(SceneLoader const&);
};

#endif // SCENELOADER_H
