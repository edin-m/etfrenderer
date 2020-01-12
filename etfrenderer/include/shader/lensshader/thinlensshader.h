#ifndef THINLENSSHADER_H
#define THINLENSSHADER_H

#include "etfrenderer.h"
#include "shader/lensshader.h"

class ThinLensShader : public LensShader
{
public:
    ThinLensShader();
    ~ThinLensShader();

    bool loadFromXML(const QString &xml);

    Color shade(const Ray &ray) const;

    vec3 ray_direction(const vec3& pixel_point,
                       const vec2& lens_point) const;
private:
    float m_focalLength;
};

#endif // THINLENSSHADER_H
