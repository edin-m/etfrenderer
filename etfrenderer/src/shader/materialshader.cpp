#include "shader/materialshader.h"
#include <limits>
#include "xmlutil.h"


bool MaterialShader::loadFromXML(const QString &xml)
{
    if( m_refl_mat != NULL )
        delete m_refl_mat;

    m_refl_mat = new ReflectionMaterial;
    bool bRefl = m_refl_mat->loadFromXML(xml);

    if( !bRefl )
    {
        delete m_refl_mat;
        m_refl_mat = NULL;
    }

    if( !bRefl )
        return false;

    return true;
}

/**
  Generates reflaction ray and casts it into the scene.
  */
Color MaterialShader::ReflectionMaterial::shade(const Ray &ray,
                                                const HitRecord &result)
{
    const float& refl_factor = m_refl_factor;
    const Color& refl_color  = m_refl_color;

    const float epsilon = std::numeric_limits<float>::epsilon();

    if( refl_factor <= epsilon ||
            refl_color.red() <= epsilon ||
            refl_color.red() <= epsilon ||
            refl_color.red() <= epsilon)
        return Color();

    Color ret;

    Ray refl_ray;
    refl_ray.origin = result.intersection_point;
    refl_ray.direction = sl::reflect(ray.direction, result.normal);

    ret = qEtfrenderer->scene()->traceRay(refl_ray, 1);
    ret *= refl_color;
    ret *= refl_factor;

    return ret;
}

/**
  Reflection shader is defined internally (inside another shader)

  example:
  <shader ...>
    ...
    <reflection factor="0.5">
        <color ... />
    </reflection>
    ...
  </shader>
  */
bool MaterialShader::ReflectionMaterial::loadFromXML(const QString &xml)
{
    // we dont need ID for reflection

    QString _xml = xmlutil::evaluate(xml, "/shader/reflection");
    if( _xml == "" )
        return false;

    bool ok = false;
    float _factor = xmlutil::attr(_xml, "factor").toFloat(&ok);
    m_refl_factor = ok ? _factor : m_refl_factor;

    m_refl_color = xmlutil::color(_xml, m_refl_color);

    return true;
}
