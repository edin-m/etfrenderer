#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <algorithm>

#include "util.h"

namespace util
{
    // TODO: testirati
    template <typename T>
    inline
    T linear(T v0, T v1, float t)
    {
        t = util::clamp(0.0f, 1.0f, t);
        return (v0 * (1 - t) + v1 * t);
    }

    // TODO: testirati
    template <typename T>
    inline
    T bilinear( T p00,
                T p10,
                T p01,
                T p11,
                float tx,
                float ty
                )
    {
        tx = std::min(std::max(0.0f, tx), 1.0f);
        ty = std::min(std::max(0.0f, ty), 1.0f);

        T a = p00 * (T(1) - tx) + p10 * tx;
        T b = p01 * (T(1) - tx) + p11 * tx;
        return a * (T(1) - ty) + b * ty;
    }

    // TODO: trilinear interpolation
}

#endif // INTERPOLATION_H
