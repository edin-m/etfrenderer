#ifndef SLFUNCTIONS_H
#define SLFUNCTIONS_H

#include "types.h"
#include "structs.h"

// shader language functions
namespace sl
{

inline
vec3 reflect(const vec3& in, const vec3& normal);

inline
vec3 reflect(double _dot, const vec3& in, const vec3& normal);

inline
vec3 refract(const vec3& in, float index_of_refraction);


// ------------------ implementation ------------------------

vec3 reflect(const vec3 &in, const vec3& normal)
{
    return reflect(dot(in, normal), in, normal);
}

vec3 reflect(double _dot, const vec3 &in, const vec3 &normal)
{
    return in - 2 * _dot * normal;
}

vec3 refract(const vec3 &in, float index_of_refraction)
{

}

}


#endif // SLFUNCTIONS_H
