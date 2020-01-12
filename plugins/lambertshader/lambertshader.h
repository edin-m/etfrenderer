#ifndef LAMBERTSHADER_H
#define LAMBERTSHADER_H

#include "shader.h"
#include "shader/materialshader.h"
#include "types.h"
#include "light.h"
#include "xmlutil.h"
#include "util/sl.h"

class LambertShader : public MaterialShader
{
public:
    LambertShader();

    Color shade(const Ray&, const HitRecord&, const Light*) const;

    bool loadFromXML(const QString& xml);
private:
    Color m_diffuse_color;
};

#endif // LAMBERTSHADER_H
