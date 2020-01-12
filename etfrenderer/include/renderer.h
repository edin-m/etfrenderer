#ifndef RENDERER_H
#define RENDERER_H

#include <QPoint>
#include <QSize>

#include "framebuffer.h"

class Etfrenderer;

typedef void (*renderer_update_callback)(int percent);

class Renderer
{
public:
    virtual ~Renderer(){}

    virtual void init(const Etfrenderer*) = 0;
    virtual bool render(const FrameBuffer* framebuffer, const QPoint& start, const QSize& render_size) = 0;
    virtual void setUpdateCallback(renderer_update_callback&) = 0;
    virtual void abort() = 0;

};

#endif // RENDERER_H
