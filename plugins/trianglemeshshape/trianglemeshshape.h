#ifndef TRIANGLEMESHSHAPE_H
#define TRIANGLEMESHSHAPE_H

#ifdef ETR_DEVELOPMENT
#include <QDebug>
#endif

#include <QDir>
#include <QUrl>
#include <QImage>

#include "structs.h"
#include "shape.h"
#include "shape/triangleshape.h"
#include "xmlutil.h"
#include "etfrenderer.h"
#include "util/bbox.h"
#include "mapping.h"
#include "mapping/sphericalmapping.h"

#include "emdobject.h"

class TriangleMeshShape : public Shape
{
public:
    TriangleMeshShape();
    ~TriangleMeshShape();

    bool hit(const Ray &, HitRecord &, bool isShadowRay = false) const;
    bool loadFromXML(const QString &xml);

private:
    EmdObject* createEmdObject();
    BoundingBox* generateBoundingBox();

    EmdObject* emdObject;
};

#endif // TRIANGLEMESHSHAPE_H
