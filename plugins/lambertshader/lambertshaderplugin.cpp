#include "lambertshaderplugin.h"

LambertShaderPlugin::LambertShaderPlugin()
{
}

LambertShaderPlugin::~LambertShaderPlugin()
{
    foreach(Shader* shader, shaders)
    {
        delete shader;
    }
}

Shader* LambertShaderPlugin::fromXML(const QString& xml) const
{
    LambertShader* shader = new LambertShader();
    bool result = shader->loadFromXML(xml);

    if( !result )
    {
        delete shader;
        return NULL;
    }

    shaders.append((Shader*)shader);
    return (Shader*) shader;
}
