#include "framebuffer.h"

FrameBuffer::FrameBuffer(int width, int height)
{
    image = new QImage(width, height, QImage::Format_ARGB32);
    image->fill(Qt::black);
}

FrameBuffer::~FrameBuffer()
{
    delete image;
}
