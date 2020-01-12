#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include <QApplication>

#include <QDebug>

#include "shader.h"
#include "shader/materialshader.h"

#include "structs.h"
#include "xmlutil.h"
#include "util/sl.h"
#include "etfrenderer.h"
#include "scene.h"

class PhongShader : public MaterialShader
{
public:
    PhongShader();

    Color shade(const Ray &ray, const HitRecord &result, const Light *light) const;
    Color shade(const Ray &ray, const HitRecord &result) const;
    bool loadFromXML(const QString &xml);
private:
    uint m_speculardecay;

    const Shader* m_diffuse_shader;
    const Shader* m_specular_shader;

    Color m_diffuse_color;
    Color m_specular_color;
};

#endif // PHONGSHADER_H
