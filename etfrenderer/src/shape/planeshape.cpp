#include "shape/planeshape.h"

PlaneShape::PlaneShape()
{

}

bool PlaneShape::hit(const Ray& in_ray, HitRecord& out_record, bool isShadowRay) const
{
    Triangle t1, t2;
    t1.set(m_points[0], m_points[1], m_points[2]);
    t2.set(m_points[2], m_points[3], m_points[0]);

    bool hit = t1.hit(in_ray, out_record, isShadowRay) || t2.hit(in_ray, out_record, isShadowRay);

    if( !hit )
        return false;

    out_record.color = m_color;
    return true;
}

bool PlaneShape::loadFromXML(const QString& xml)
{
    QString l_type = xmlutil::attr(xml, "type");
    type = Shape::str2type(l_type);

    if( type != PLANE )
        return false;

    QString _id = xmlutil::attr(xml, "id");
    id = _id.toUInt();

    m_name = xmlutil::attr(xml, "name");

    QString xpath_point, xml_point;

    xpath_point = QString("/object/point1");
    xml_point = xmlutil::evaluate(xml, xpath_point);
    m_points[0] = xmlutil::xml2vec3(xml_point);

    xpath_point = QString("/object/point2");
    xml_point = xmlutil::evaluate(xml, xpath_point);
    m_points[1] = xmlutil::xml2vec3(xml_point);

    xpath_point = QString("/object/point3");
    xml_point = xmlutil::evaluate(xml, xpath_point);
    m_points[2] = xmlutil::xml2vec3(xml_point);

    xpath_point = QString("/object/point4");
    xml_point = xmlutil::evaluate(xml, xpath_point);
    m_points[3] = xmlutil::xml2vec3(xml_point);

    QString color_str = xmlutil::attr(xml, "color");
    m_color = QColor(color_str).rgba();

    QString shaderid = xmlutil::attr(xmlutil::evaluate(xml, "/object/shader"), "id");
    m_shader = qEtfrenderer->scene()->findShaderById(shaderid);
//    qDebug() << "WICKED SICK";
//    qDebug() << m_points[0]
//             << m_points[1]
//             << m_points[2]
//             ;

    return true;
}

const Shape* PlaneShape::fromXML(const QString& xml)
{
    PlaneShape* planeShape = new PlaneShape();
    bool result = planeShape->loadFromXML(xml);

    if( !result )
    {
        delete planeShape;
        return NULL;
    }

    return (Shape*) planeShape;
}
