#include "pointlightplugin.h"

PointLightPlugin::PointLightPlugin()
{
}

PointLightPlugin::~PointLightPlugin()
{
    foreach(const Light* _light, m_lights)
    {
        delete _light;
    }

    m_lights.clear();
}

const Light *PointLightPlugin::fromXML(const QString& xml)
{
    PointLight* pointLight = new PointLight();
    bool result = pointLight->loadFromXML(xml);

    if( !result )
        return NULL;

    m_lights.append(pointLight);
    return (Light*) pointLight;
}
