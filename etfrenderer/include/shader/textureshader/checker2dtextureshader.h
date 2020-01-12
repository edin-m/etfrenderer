#ifndef CHECKER2DTEXTURESHADER_H
#define CHECKER2DTEXTURESHADER_H

#include "shader/textureshader.h"

class Checker2DTextureShader : public TextureShader
{
public:
    Checker2DTextureShader();

    bool loadFromXML(const QString &xml);

    Color shade(const Ray &ray, const HitRecord &, const Light *) const;
private:
    Color m_color1, m_color2;
    float m_size;
};

#endif // CHECKER2DTEXTURESHADER_H
