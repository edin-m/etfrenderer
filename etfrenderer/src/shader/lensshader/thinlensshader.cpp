#include "shader/lensshader/thinlensshader.h"
#include "xmlutil.h"

ThinLensShader::ThinLensShader()
    :
      m_focalLength(99999.0f)
{

}

ThinLensShader::~ThinLensShader()
{
}

bool ThinLensShader::loadFromXML(const QString& xml)
{
    if( xmlutil::attr(xml, "type").toLower() != "thinlens" )
        return false;

    bool ok = false;
    unsigned _shaderid = xmlutil::attr(xml, "id").toUInt(&ok);
    m_id = ok ? _shaderid : m_id;

    float _focalLength = xmlutil::evaluate(xml, "/shader/focal-length/data(.)").toFloat(&ok);
    m_focalLength = ok ? _focalLength : m_focalLength;

    float _radius = xmlutil::evaluate(xml, "/shader/lens-radius/data(.)").toFloat(&ok);
    m_radius = ok ? _radius : m_radius;

    qDebug() << "ThinLensShader"
             << m_id
             << m_focalLength
             << m_radius;

    return true;
}

Color ThinLensShader::shade(const Ray &ray) const
{
    return qEtfrenderer->scene()->traceRay(ray);
}

vec3 ThinLensShader::ray_direction(const vec3& pixel_point,
                                   const vec2& lens_point) const
{
    const float& f = m_focalLength; // focal length
    float d = pixel_point.z(); // distance

    float invd = 1.0f / d;

    float px = pixel_point.x() * f * invd;
    float py = pixel_point.y() * f * invd;

    vec3 dir = vec3(px, py, -f) - lens_point;
    dir.normalize();

    return dir;

}


