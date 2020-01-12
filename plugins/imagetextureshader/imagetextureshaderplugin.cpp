#include "imagetextureshaderplugin.h"

ImageTextureShaderPlugin::ImageTextureShaderPlugin()
{
}

ImageTextureShaderPlugin::~ImageTextureShaderPlugin()
{
    foreach(Shader* shader, shaders)
    {
        delete shader;
    }
}

Shader *ImageTextureShaderPlugin::fromXML(const QString& xml) const
{
    ImageTextureShader* shader = new ImageTextureShader;
    bool result = shader->loadFromXML(xml);

    if( !result )
    {
        delete shader;
        return NULL;
    }

    shaders.append((Shader*)shader);
    return (Shader*)shader;
}

