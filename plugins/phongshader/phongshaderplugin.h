#ifndef PHONGSHADERPLUGIN_H
#define PHONGSHADERPLUGIN_H

#define PLUGIN_FILENAME phongshaderplugin
#define PLUGIN_CLASSNAME PhongShaderPlugin

#include <QtPlugin>

#include "plugin/shaderplugin.h"
#include "shader.h"
#include "phongshader.h"

class PhongShaderPlugin : public QObject, public ShaderPlugin
{
    Q_OBJECT
    Q_INTERFACES(ShaderPlugin)
    Q_PLUGIN_METADATA(IID "com.etfrenderer.PhongShaderPlugin" FILE "phongshader.json")
public:
    PhongShaderPlugin();

    QString name() const { return "PhongShaderPlugin"; }
    QString author() const { return ""; }
    QString version() const { return "1.0"; }

    Shader* fromXML(const QString &xml) const;
};

#endif // PHONGSHADERPLUGIN_H
