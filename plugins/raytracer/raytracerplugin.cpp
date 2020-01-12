#include "raytracerplugin.h"

RaytracerPlugin::RaytracerPlugin()
{
    this->m_renderer = (Renderer*) new Raytracer();
}
