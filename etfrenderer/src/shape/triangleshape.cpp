#include "shape/triangleshape.h"

TriangleShape::TriangleShape()
{

}

void TriangleShape::set(const vec3& p1, const vec3& p2, const vec3& p3)
{
    m_points[0] = p1;
    m_points[1] = p2;
    m_points[2] = p3;
}

bool TriangleShape::hitStatic(
            const vec3& point0,
            const vec3& point1,
            const vec3& point2,
            const Ray&  in_ray,
            HitRecord&  out_record,
            bool isShadowRay,
            bool debug
        )
{
    // ray triangle intersection
    // preuzeto iz Realistic Ray Tracing

    const vec3& P0 = point0;
    const vec3& P1 = point1;
    const vec3& P2 = point2;

    float tval;
    float A = P0.x() - P1.x();
    float B = P0.y() - P1.y();
    float C = P0.z() - P1.z();

    float D = P0.x() - P2.x();
    float E = P0.y() - P2.y();
    float F = P0.z() - P2.z();

    float G = in_ray.direction.x();
    float H = in_ray.direction.y();
    float I = in_ray.direction.z();

    float J = P0.x() - in_ray.origin.x();
    float K = P0.y() - in_ray.origin.y();
    float L = P0.z() - in_ray.origin.z();

    float EIHF = E*I - H*F;
    float GFDI = G*F - D*I;
    float DHEG = D*H - E*G;

    float denom = (A*EIHF + B*GFDI + C*DHEG);
    float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

    if( beta <= 0.0f || beta >= 1.0f )
        return false;

    float AKJB = A*K - J*B;
    float JCAL = J*C - A*L;
    float BLKC = B*L - K*C;

    float gama = ( I*AKJB + H*JCAL + G*BLKC) / denom;
    if( gama <= 0.0f || beta + gama >= 1.0f)
        return false;

    tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    out_record.t = tval;
    out_record.intersection_point = in_ray.origin + tval * in_ray.direction;

    // ako stavimo
    // if( isShadowRay )
    //     return true;
    // onda ce neki od polygona koji nece biti prikazan zbog back face cullinga
    // biti prepreka shadow ray-u od nekog svijetla iza tog objekta
    // stoga treba izostaviti ovaj kod ako zelimo da objekat koji nije vidljiv zbog
    // back face cullinga NE ucestvuje u shadowingu tj. da zraka prolazi kroz njega
    // iako je objektova zadnja strana blokira

    out_record.normal = cross(P1 - P0, P2 - P0).normalized();

    out_record.uv = vec2(beta, gama);
    // drugi nacin
    // http://gamedev.stackexchange.com/questions/7331/ray-plane-intersection-to-find-the-z-of-the-intersecting-point

    //back face culling
    if( dot(-out_record.normal, in_ray.direction) > 0 )
        return true;
    else
        return false;

    //if( !isShadowRay && debug )
    //    qDebug() << "TriangleShape: " << in_ray.origin << in_ray.direction << point0 << point1 << point2;

    return true;
}

bool TriangleShape::hitStatic(const vec3* pointsArray, const Ray& in_ray, HitRecord& out_record, bool isShadowRay)
{
    return TriangleShape::hitStatic(
                pointsArray[0],
                pointsArray[1],
                pointsArray[2],
                in_ray,
                out_record,
                isShadowRay
              );
}

bool TriangleShape::hit(const Ray& in_ray, HitRecord& out_record, bool isShadowRay) const
{
    out_record.color = m_color;
    return TriangleShape::hitStatic(m_points[0], m_points[1], m_points[2], in_ray, out_record, isShadowRay);
}

bool TriangleShape::loadFromXML(const QString &xml)
{
    QString l_type = xmlutil::attr(xml, "type");
    type = Shape::str2type(l_type);

    if( type != TRIANGLE )
        return false;

    qDebug() << "triangle" << xml;

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

const Shape* TriangleShape::fromXML(const QString& xml)
{
    TriangleShape* triShape = new TriangleShape();
    bool result = triShape->loadFromXML(xml);

    if( !result )
    {
        delete triShape;
        return NULL;
    }

    return (Shape*) triShape;
}
