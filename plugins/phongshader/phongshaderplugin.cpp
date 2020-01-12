#include "phongshaderplugin.h"

PhongShaderPlugin::PhongShaderPlugin()
{
}

Shader *PhongShaderPlugin::fromXML(const QString &xml) const
{
    PhongShader *shader = new PhongShader();
    bool result = shader->loadFromXML(xml);

    if( !result )
    {
        delete shader;
        return NULL;
    }

    return (Shader*) shader;
}

