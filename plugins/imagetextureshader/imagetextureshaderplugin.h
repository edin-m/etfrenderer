#ifndef IMAGETEXTURESHADERPLUGIN_H
#define IMAGETEXTURESHADERPLUGIN_H

#define PLUGIN_FILENAME imagetextureshaderplugin
#define PLUGIN_CLASSNAME ImageTextureShaderPlugin

#include <QtPlugin>

#include "shader.h"
#include "plugin/shaderplugin.h"

#include "imagetextureshader.h"

class ImageTextureShaderPlugin : public QObject, public ShaderPlugin
{
    Q_OBJECT
    Q_INTERFACES(ShaderPlugin)
    Q_PLUGIN_METADATA(IID "com.etfrenderer.ImageTextureShaderPlugin" FILE "imagetextureshader.json")
public:
    ImageTextureShaderPlugin();
    ~ImageTextureShaderPlugin();

    QString name() const { return "ImageTextureShaderPlugin"; }
    QString author() const { return ""; }
    QString version() const { return "1.0"; }

    Shader* fromXML(const QString& xml) const;
};

#endif // IMAGETEXTURESHADERPLUGIN_H
