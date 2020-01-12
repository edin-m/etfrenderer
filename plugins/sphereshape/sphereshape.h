#ifndef SPHERESHAPE_H
#define SPHERESHAPE_H

#include <QXmlQuery>
#include <QDebug>
#include <QColor>

#include "shape.h"
#include "xmlutil.h"
#include "scene.h"
#include "etfrenderer.h"
#include "mapping.h"
#include "mapping/sphericalmapping.h"

class SphereShape : public Shape
{
public:
    SphereShape();

    bool hit(const Ray&, HitRecord&, bool isShadowRay = false) const;

    const vec3& center() const;

    bool loadFromXML(const QString& xml);

private:
    float m_radius;
    Color m_color;
};

#endif // SPHERESHAPE_H
