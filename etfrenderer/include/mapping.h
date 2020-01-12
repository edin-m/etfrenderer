#ifndef MAPPING_H
#define MAPPING_H

#include <cmath>

#include <QString>

#include "structs.h"

class Mapping
{
public:
    virtual vec2 uv(const vec3& hitPoint, const vec3& center) const = 0;
    virtual vec2 uv(const vec3& mappingNormal) const = 0;
};



#endif // MAPPING_H
