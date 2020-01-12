#ifndef RAYTRACERPLUGIN_H
#define RAYTRACERPLUGIN_H

#define PLUGIN_FILENAME raytracerplugin
#define PLUGIN_CLASSNAME RaytracerPlugin

#include <QtPlugin>

#include "plugin/rendererplugin.h"
#include "raytracer.h"

class RaytracerPlugin : public QObject, public RendererPlugin
{
    Q_OBJECT
    Q_INTERFACES(RendererPlugin)
    Q_PLUGIN_METADATA(IID "com.etfrenderer.Raytracer" FILE "raytracer.json")
public:
    RaytracerPlugin();

    QString name() const { return "etf raytracer"; }
    QString author() const { return QString::fromUtf8("Edin Mujagić, "); }
    QString version() const { return "1.0"; }

    void init(const Etfrenderer*) { }
private:
};

#endif // RAYTRACERPLUGIN_H
