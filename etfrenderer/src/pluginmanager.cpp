#include "pluginmanager.h"

PluginManager::PluginManager()
{
}

void PluginManager::add(RendererPlugin* renderer)
{
    m_renderers.append(renderer);
}

void PluginManager::add(ShaderPlugin* shader)
{
    m_shaders.append(shader);
}

void PluginManager::add(ShapePlugin* shape)
{
    m_shapes.append(shape);
}

void PluginManager::add(LightPlugin* light)
{
    m_lights.append(light);
}

RendererPlugin* PluginManager::getRenderer() const
{
    if(m_renderers.count() > 0)
        return m_renderers[0];
    return NULL;
}
