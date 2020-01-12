#include "trianglemeshshapeplugin.h"

TriangleMeshShapePlugin::TriangleMeshShapePlugin()
{
}

TriangleMeshShapePlugin::~TriangleMeshShapePlugin()
{
}

const Shape* TriangleMeshShapePlugin::fromXML(const QString& xml)
{
    TriangleMeshShape* tms = new TriangleMeshShape();
    bool result = tms->loadFromXML(xml);

    if( !result )
    {
        delete tms;
        return NULL;
    }

    return (Shape*) tms;
}

