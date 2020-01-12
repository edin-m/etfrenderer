#include "pointlight.h"

PointLight::PointLight()
{
}

vec3 PointLight::incidence(const vec3& point) const
{
    return (m_location - point).normalized();
}

float PointLight::distance(const vec3& point) const
{
    return (m_location - point).length();
}

bool PointLight::loadFromXML(const QString& xml)
{
    // reading type attribute
    QString l_type = xmlutil::attr(xml, "type");
    type = Light::str2type(l_type);

    if( type != POINT )
        return false;

    // reading id
    QString l_id = xmlutil::attr(xml, "id");
    id = l_id.toUInt();

    // reading name attribute
    m_name = xmlutil::attr(xml, "name");

    // reading position data
    QString xpath_pos("/light/pos");
    QString xml_pos = xmlutil::evaluate(xml, xpath_pos);
    m_location = xmlutil::xml2vec3(xml_pos);

    // read light color
    QString color_str = xmlutil::attr(xml, "color");
    m_color = Color(QColor(color_str));

    qDebug() << m_name
             << m_location
            ;

    return true;
}
