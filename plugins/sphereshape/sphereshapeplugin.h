#ifndef SPHERESHAPEPLUGIN_H
#define SPHERESHAPEPLUGIN_H

#define PLUGIN_FILENAME sphereshapeplugin
#define PLUGIN_CLASSNAME SphereShapePlugin

#include <QtPlugin>

#include "plugin/shapeplugin.h"
#include "shape.h"
#include "shader.h"
#include "types.h"
#include "structs.h"

#include "sphereshape.h"

class SphereShapePlugin : public QObject, public ShapePlugin
{
    Q_OBJECT
    Q_INTERFACES(ShapePlugin)
    Q_PLUGIN_METADATA(IID "com.etfrenderer.SphereShape" FILE "sphereshape.json")
public:
    SphereShapePlugin();
    ~SphereShapePlugin();

    QString name() const { return "SphereShapePlugin"; }
    QString author() const { return ""; }
    QString version() const { return "1.0"; }

    const Shape* fromXML(const QString&);
private:
    QList<const Shape*> m_shapes;
};

#endif // SPHERESHAPEPLUGIN_H
