#include "lambertshader.h"

LambertShader::LambertShader() :
    m_diffuse_color(Color())
{
}

Color LambertShader::shade(const Ray& ray, const HitRecord& result, const Light* light) const
{
    // uzimamo upadni ugao svjetlosti (za point-light ovo ovisi o intersection_point
    vec3 LV = light->incidence(result.intersection_point);

    // racunamo prirodu ugla normale i vektora svjetla
    double _dot = dot(result.normal, LV);

    // ukoliko je < 90°
    if( _dot > 0 )
    {
        // rezultirajuca boja je boja shadera (objekta kojem je shader dodijeljen)
        // pomnozen bojom svjetla
        // pomnozeno prirodom ugla

        Color col(result.color);

        col *= light->color();
        col *= _dot;

//        if( m_refl_mat != NULL )
//            col += m_refl_mat->shade(ray, result);

        return col;
    }

    Color col(rgb(0x00000000));
    return col;

}

bool LambertShader::loadFromXML(const QString& xml)
{
    QString shading = xmlutil::attr(xml, "shading").toLower();
    if( shading != "lambert" && shading != "lambertian" )
        return false;

    Shader::loadID(xml);
    MaterialShader::loadFromXML(xml);

    m_diffuse_color = xmlutil::color(
                xmlutil::evaluate(xml, "/shader/diffuse"),
                m_diffuse_color);

    return true;
}
