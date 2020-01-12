#ifndef LAMBERTSHADERPLUGIN_H
#define LAMBERTSHADERPLUGIN_H

#define PLUGIN_FILENAME lambertshaderplugin
#define PLUGIN_CLASSNAME LambertShaderPlugin

#include <QtPlugin>

#include "plugin/shaderplugin.h"
#include "shader.h"
#include "lambertshader.h"

class LambertShaderPlugin : public QObject, public ShaderPlugin
{
    Q_OBJECT
    Q_INTERFACES(ShaderPlugin)
    Q_PLUGIN_METADATA(IID "com.etfrenderer.LambertShaderPlugin" FILE "lambertshader.json")
public:
    LambertShaderPlugin();
    ~LambertShaderPlugin();

    QString name() const { return "LambertShaderPlugin"; }
    QString author() const { return ""; }
    QString version() const { return "1.0"; }

    Shader* fromXML(const QString &xml) const;
};

#endif // LAMBERTSHADERPLUGIN_H
