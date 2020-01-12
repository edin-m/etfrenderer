#ifndef TRIANGLEMESHSHAPEPLUGIN_H
#define TRIANGLEMESHSHAPEPLUGIN_H

#define PLUGIN_FILENAME trianglemeshshapeplugin
#define PLUGIN_CLASSNAME TriangleMeshShapePlugin

#include <QtPlugin>

#include "plugin/shapeplugin.h"
#include "shape.h"
#include "trianglemeshshape.h"

class TriangleMeshShapePlugin : public QObject, public ShapePlugin
{
    Q_OBJECT
    Q_INTERFACES(ShapePlugin)
    Q_PLUGIN_METADATA(IID "com.etfrenderer.TriangleMeshShapePlugin" FILE "trianglemeshshape.json")
public:
    TriangleMeshShapePlugin();
    ~TriangleMeshShapePlugin();

    QString name() const { return "TriangleMeshShapePlugin"; }

    const Shape* fromXML(const QString &);
};

#endif // TRIANGLEMESHSHAPEPLUGIN_H
