#include "trianglemeshshape.h"

TriangleMeshShape::TriangleMeshShape()
    :
      emdObject(NULL)
{

    m_name = "TriangleMesh";
}

TriangleMeshShape::~TriangleMeshShape()
{
    if( emdObject != NULL )
        delete emdObject;
}

bool TriangleMeshShape::hit(const Ray& in_ray, HitRecord& result, bool isShadowRay) const
{
    if( emdObject != NULL )
    {
        bool hit = emdObject->hit(in_ray, result, isShadowRay);

        return hit;
    }
}

bool TriangleMeshShape::loadFromXML(const QString& xml)
{
    QString type = xmlutil::attr(xml, "type");
    if( type.trimmed().toLower() != "trimesh" )
        return false;

    m_name = xmlutil::attr(xml, "name");

    QString _external = xmlutil::attr(xml, "external");
    if( _external.trimmed().length() > 0 )
    {
        emdObject = createEmdObject();
        emdObject->loadFromFile(_external);
    }
    else
    {
        // TODO: test this
        emdObject = createEmdObject();
        QString tmp = xmlutil::evaluate(xml, "/object/data/data/(.)");
        QTextStream tstream(&tmp);
        emdObject->loadFromStream(tstream);
    }

    m_center = emdObject->center();

    QString shaderid = xmlutil::attr(xmlutil::evaluate(xml, "/object/shader"), "id");
    m_shader = qEtfrenderer->scene()->findShaderById(shaderid);

    QString bbox = xmlutil::attr(xmlutil::evaluate(xml, "/object/bbox"), "use");
    if( bbox.toLower() == "yes" )
        if( emdObject != NULL )
            emdObject->generateBoundingBox();

    return true;
}

EmdObject *TriangleMeshShape::createEmdObject()
{
    if( emdObject != NULL )
        delete emdObject;

    emdObject = new EmdObject;
    return emdObject;
}
