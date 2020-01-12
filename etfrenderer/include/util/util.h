#ifndef UTIL_H
#define UTIL_H

#include <QtGlobal>

namespace util
{

    /**

      */
    template <typename T>
    inline
    T clamp(T min, T max, T value)
    {
        // alternativa: std::max(min, std::min(max, value))
        return std::min(std::max(min, value), max);
    }

    /**

      */
    template <typename T>
    inline
    T random(int low, int high, T multiplier = 1.0f)
    {
        return (qrand() % ((high + 1) - low) + low) * multiplier;
    }

}

#endif // UTIL_H
