#ifndef SHAPEPLUGIN_H
#define SHAPEPLUGIN_H

#include <QtPlugin>

#include "shape.h"

class ShapePlugin
{
public:
    virtual ~ShapePlugin(){}

    virtual QString name() const = 0;
    virtual QString author() const { return "ETF"; }
    virtual QString version() const { return "1.0"; }

    virtual const Shape* fromXML(const QString&) = 0;
};

Q_DECLARE_INTERFACE(ShapePlugin, "mms.etfrenderer.ShapePlugin/1.0")

#endif // SHAPEPLUGIN_H
