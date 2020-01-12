#ifndef BBOX_H
#define BBOX_H

#include <cmath>

#include <limits>
#include <algorithm>

#include "structs.h"

class BoundingBox
{
public:
    vec3 p0, p1;
    BoundingBox(const vec3& _p0, const vec3& _p1);

    void append(const vec3& vec);
    bool hit(const Ray& ray) const;
};

#endif // BBOX_H
