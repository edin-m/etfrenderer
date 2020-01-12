#ifndef LIGHTPLUGIN_H
#define LIGHTPLUGIN_H

#include <QtPlugin>

#include "light.h"

class LightPlugin
{
public:
    virtual ~LightPlugin() {}

    virtual QString name() const = 0;
    virtual QString author() const { return "ETF"; }
    virtual QString version() const { return "1.0"; }

    virtual const Light* fromXML(const QString&) { return NULL; }
};

Q_DECLARE_INTERFACE(LightPlugin, "mms.etfrenderer.LightPlugin/1.0")

#endif // LIGHTPLUGIN_H
