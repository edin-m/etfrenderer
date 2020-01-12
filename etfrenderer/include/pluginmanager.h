#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QList>

#include "plugin/rendererplugin.h"
#include "plugin/shaderplugin.h"
#include "plugin/shapeplugin.h"
#include "plugin/lightplugin.h"

class PluginManager
{
public:
    PluginManager();

    void add(RendererPlugin*);
    void add(ShaderPlugin*);
    void add(ShapePlugin*);
    void add(LightPlugin*);

    RendererPlugin* getRenderer() const;

    const QList<RendererPlugin*>& getRenderers() const { return m_renderers; }
    const QList<ShapePlugin*>& getShapePlugins()      const { return m_shapes; }
    const QList<ShaderPlugin*>& getShaders()    const { return m_shaders; }
    const QList<LightPlugin*>&      getLightPlugins() const { return m_lights; }

private:
    QList<RendererPlugin*> m_renderers;
    QList<ShaderPlugin*>   m_shaders;
    QList<ShapePlugin*>    m_shapes;
    QList<LightPlugin*>    m_lights;
};

#endif // PLUGINMANAGER_H
