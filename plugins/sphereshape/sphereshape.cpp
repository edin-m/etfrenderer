#include "sphereshape.h"

SphereShape::SphereShape()
{
}

bool SphereShape::hit(const Ray& in_ray, HitRecord& out_record, bool isShadowRay) const
{
    vec3 temp = in_ray.origin - m_center;
    double a  = dot( in_ray.direction, in_ray.direction );
    double b  = 2 * dot(in_ray.direction, temp);
    double c  = dot(temp, temp) - m_radius * m_radius;

    double discriminant = b*b - 4*a*c;

    if( discriminant > 0 )
    {
        discriminant = er_sqrt( discriminant );
        double t = ( -b - discriminant ) / ( 2 * a );

        out_record.t = t;
        out_record.intersection_point = vec3(in_ray.origin + t * in_ray.direction);

        if( isShadowRay )
            return true;

        out_record.normal = vec3(out_record.intersection_point - m_center).normalized();
        out_record.color  = m_color; // obsolete

        // sad za sad
        SphericalMapping sm;
        out_record.uv = sm.uv(out_record.normal);

        return true;
    }


    return false;

}

const vec3& SphereShape::center() const
{
    return m_center;
}

bool SphereShape::loadFromXML(const QString& xml)
{
    // reading type attribute
    QString l_type = xmlutil::attr(xml, "type");
    type = Shape::str2type(l_type);

    if( type != SPHERE )
        return false;

    // reading id
    QString l_id = xmlutil::attr(xml, "id");
    id = l_id.toUInt();

    // reading name attribute
    m_name = xmlutil::attr(xml, "name");

    // reading radius attribute
    QString l_strRadius = xmlutil::attr(xml, "radius");
    m_radius = l_strRadius.toFloat();

    // reading position data
    m_center = xmlutil::xml2vec3(xmlutil::evaluate(xml, "/object/pos"));

    // get object color
    QString color_str = xmlutil::attr(xml, "color");
    m_color = Color(QColor(color_str));

    // sphere loaded
    uint shaderid = xmlutil::evaluate(xml, "/object/shader/@id/data(.)").trimmed().toUInt();
    m_shader = qEtfrenderer->scene()->findShaderById(shaderid);

//    qDebug() << m_name
//             << m_center
//             << m_radius
//             << m_shader
//             << (m_shader != NULL ? m_shader->id() : 0)
             ;

    return true;
}


