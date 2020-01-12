#ifndef PLANESHAPE_H
#define PLANESHAPE_H

#include <QDebug>

#include "structs.h"
#include "shape.h"
#include "shape/triangleshape.h"
#include "etfrenderer.h"

class PlaneShape : public Shape
{
public:
    PlaneShape();

    bool hit(const Ray &, HitRecord &, bool isShadowRay = false) const;

    bool loadFromXML(const QString& xml);
    static const Shape* fromXML(const QString& xml);

private:
    vec3 m_points[4];
    rgb m_color;
};

typedef PlaneShape Plane;
typedef Plane plane;

#endif // PLANESHAPE_H
