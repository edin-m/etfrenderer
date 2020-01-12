#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <QImage>

#include "types.h"

class FrameBuffer
{
public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();

    void set(const QPoint& point, const rgb& color) const {
        image->setPixel(point, color);
    }

    void set(int x, int y, const rgb& color) const {
        image->setPixel(x, y, color);
    }

    const QImage* qimage() const { return image; }

private:
    QImage* image;
};

#endif // FRAMEBUFFER_H
