#ifndef IMAGETEXTURESHADER_H
#define IMAGETEXTURESHADER_H

#include <QImage>

#include <QDebug>

#include "types.h"
#include "structs.h"
#include "shader/textureshader.h"
#include "xmlutil.h"

class ImageTextureShader : public TextureShader
{
public:
    ImageTextureShader();

    Color shade(const Ray &ray, const HitRecord &, const Light *) const;

    bool loadFromXML(const QString& xml);

private:
    QImage m_image;
};

#endif // IMAGETEXTURESHADER_H
