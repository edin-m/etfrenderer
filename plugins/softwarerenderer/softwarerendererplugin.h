#ifndef SOFTWARERENDERERPLUGIN_H
#define SOFTWARERENDERERPLUGIN_H

#define PLUGIN_FILENAME softwarerendererplugin
#define PLUGIN_CLASSNAME SoftwareRendererPlugin

#include "plugin/rendererplugin.h"
#include "softwarerenderer.h"

class SoftwareRendererPlugin : public QObject, public RendererPlugin
{
    Q_OBJECT
    Q_INTERFACES(RendererPlugin)
public:
    SoftwareRendererPlugin();
    ~SoftwareRendererPlugin();

    QString name() const { return "software renderer"; }
    QString author() const { return QString::fromUtf8("Edin Mujagiæ, "); }
    QString version() const { return "1.0"; }

    void init(const Etfrenderer *){};
};

#endif // SOFTWARERENDERERPLUGIN_H
