#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QDebug>
#include <QColor>
#include <QMessageBox>

#include "etfrenderer.h"
#include "renderer.h"
#include "shape.h"
#include "structs.h"
#include "camera.h"
#include "sampler.h"

class Raytracer : public Renderer
{
//    bool checkForShadows(HitRecord& result, const Light* _light);
//    Color trace(const Ray& ray, int depth = 5);
public:
    Raytracer();

    void init(const Etfrenderer* etfrenderer)
    {
        this->etfrenderer = etfrenderer;
    }

    bool render(const FrameBuffer* framebuffer, const QPoint& start, const QSize& render_size);

    void abort()
    {

    }

    void setUpdateCallback(renderer_update_callback& update_callback)
    {
        m_update_callback = update_callback;
    }

private:

    const Etfrenderer* etfrenderer;
    renderer_update_callback m_update_callback;


};

#endif // RAYTRACER_H
