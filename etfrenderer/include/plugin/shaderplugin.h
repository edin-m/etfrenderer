#ifndef SHADERPLUGIN_H
#define SHADERPLUGIN_H

#include <QtPlugin>

#include "shader.h"

class ShaderPlugin
{
public:
    virtual QString name() const = 0;
    virtual QString author() const { return "ETF"; }
    virtual QString version() const { return "1.0"; }

    virtual Shader* fromXML(const QString& xml) const = 0;

protected:
    mutable QList<Shader*> shaders;
};

Q_DECLARE_INTERFACE(ShaderPlugin, "mms.etfrenderer.ShaderPlugin/1.0")

#endif // SHADERPLUGIN_H
