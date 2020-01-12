#ifndef SOFTWARERENDERER_H
#define SOFTWARERENDERER_H

#include <QPoint>
#include <QSize>

#include "renderer.h"
#include "framebuffer.h"
#include "color.h"

class SoftwareRenderer : public Renderer
{
public:
    SoftwareRenderer();

    void init(const Etfrenderer *)
    {

    }

    bool render(const FrameBuffer *framebuffer,
                const QPoint &start,
                const QSize &render_size);

    void setUpdateCallback(renderer_update_callback &)
    {

    }

    void abort()
    {

    }
};

#endif // SOFTWARERENDERER_H
