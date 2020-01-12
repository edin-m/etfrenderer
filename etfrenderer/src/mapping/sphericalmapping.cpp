#include "mapping/sphericalmapping.h"

vec2 SphericalMapping::uv(const vec3 &hitPoint, const vec3 &center) const
{
    return this->uv( (hitPoint - center).normalized() );
}

vec2 SphericalMapping::uv(const vec3 &mappingNormal) const
{
    const vec3& tmp = mappingNormal;

    float u = invPI * atan2(tmp.x(), tmp.z()) / 2.0f + 0.5f;
    float v = acos(tmp.y()) * invPI;

    return vec2(u, v);
}
