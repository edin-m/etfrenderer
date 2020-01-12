#ifndef ETFRENDERER_H
#define ETFRENDERER_H

#include <QApplication>
#include <QObject>

#include "scene.h"
#include "pluginmanager.h"
#include "sampler.h"
#include "sampler/randomsampler.h"

class Etfrenderer : public QObject {

public:
    Etfrenderer();

    void set(Scene* scene) { m_scene = scene; }
    void set(const PluginManager* pluginmanager) { m_pluginmanager = pluginmanager; }

    Scene* scene() const { return m_scene; }
    const PluginManager* pluginManager() const { return m_pluginmanager; }

    static Etfrenderer& instance()
    {
        static Etfrenderer etfrenderer;
        return etfrenderer;
    }

    Sampler* createSampler(QString name) const;

private:
    Scene* m_scene;
    const PluginManager* m_pluginmanager;

    // Etfrenderer ce trebati biti singleton (copy constr. i operator= ne smiju biti implementirani)
    Etfrenderer(Etfrenderer const&);
    void operator=(Etfrenderer const&);
};

#define qEtfrenderer ((Etfrenderer*) qvariant_cast<QObject*>(qApp->property("etfrenderer")))

#endif // ETFRENDERER_H
