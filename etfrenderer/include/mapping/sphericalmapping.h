#ifndef SPHERICALMAPPING_H
#define SPHERICALMAPPING_H

#include "mapping.h"

extern const double PI;
extern const double invPI;

class SphericalMapping : public Mapping
{
public:
    vec2 uv(const vec3& hitPoint, const vec3& center) const;
    vec2 uv(const vec3& mappingNormal) const;
};

#endif // SPHERICALMAPPING_H
