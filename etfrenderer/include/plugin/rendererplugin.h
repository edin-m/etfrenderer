#ifndef RENDERERPLUGIN_H
#define RENDERERPLUGIN_H

#include <QtPlugin>
#include <QPoint>
#include <QSize>

#include "renderer.h"
#include "framebuffer.h"

#ifndef ETFRENDERER_H
class Etfrenderer;
#endif

class RendererPlugin
{
public:
    virtual ~RendererPlugin(){}

    virtual QString name() const = 0;
    virtual QString author() const { return "ETF"; }
    virtual QString version() { return "1.0"; }

    /** TODO: deprecate this */
    virtual void init(const Etfrenderer*) = 0;

    virtual Renderer* renderer()
    {
        return m_renderer;
    }
protected:
    Renderer* m_renderer;
};

Q_DECLARE_INTERFACE(RendererPlugin, "mms.etfrenderer.RendererPlugin/1.0")

#endif // RENDERERPLUGIN_H
