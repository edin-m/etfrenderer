#ifndef POINTLIGHTPLUGIN_H
#define POINTLIGHTPLUGIN_H

#define PLUGIN_FILENAME pointlightplugin
#define PLUGIN_CLASSNAME PointLightPlugin

#include <QtPlugin>

#include "plugin/lightplugin.h"
#include "light.h"

#include "pointlight.h"

class PointLightPlugin : public QObject, public LightPlugin
{
    Q_OBJECT
    Q_INTERFACES(LightPlugin)
    Q_PLUGIN_METADATA(IID "com.etfrenderer.PointLightPlugin" FILE "pointlightplugin.json")
public:
    PointLightPlugin();
    ~PointLightPlugin();

    QString name() const { return "PointLightPlugin"; }

    const Light* fromXML(const QString &);

private:
    QList<const Light*> m_lights;
};

#endif // POINTLIGHTPLUGIN_H
