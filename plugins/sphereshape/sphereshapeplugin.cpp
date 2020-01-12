#include "sphereshapeplugin.h"

SphereShapePlugin::SphereShapePlugin()
{

}

SphereShapePlugin::~SphereShapePlugin()
{
    foreach(const Shape* shape, m_shapes)
    {
        delete shape;
    }

    m_shapes.clear();
}

const Shape* SphereShapePlugin::fromXML(const QString &xml)
{
    SphereShape* sphereShape = new SphereShape();
    bool result = sphereShape->loadFromXML(xml);

    if( !result )
    {
        delete sphereShape;
        return NULL;
    }

    m_shapes.append(sphereShape);
    return (Shape*) sphereShape;
}

