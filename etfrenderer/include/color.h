#ifndef COLOR_H
#define COLOR_H

#include <QColor>
#include <QDebug>

#include "types.h"

class Color
{
public:
    Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

    Color(const Color& color)
    {
        set(color.red(), color.green(), color.blue(), color.alpha());
    }

    Color(float r, float g, float b, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}

    Color(const QColor& color)
    {
        r = color.redF();
        g = color.greenF();
        b = color.blueF();
        a = color.alphaF();
    }

    Color(const rgb& _rgb)
    {
        *this = Color(QColor(_rgb));
    }

    Color(const char* name)
    {
        *this = Color(QColor(name));
    }

    void set(float red, float green, float blue, float alpha = 1.0f)
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    QColor toQColor() const { return QColor(r * 255, g * 255, b * 255, a * 255); }
    float red() const { return r; }
    float green() const { return g; }
    float blue() const { return b; }
    float alpha() const { return a; }

    Color& multiply_rgb(float value)
    {
        float alpha = a;
        this->operator *=(value);
        a = alpha;
        return *this;
    }

    friend QDebug operator<<(QDebug dbg, const Color& color)
    {
        dbg.nospace() << "Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
        return dbg.space();
    }

    Color& operator =(const Color& color)
    {
        set(color.red(), color.green(), color.blue(), color.alpha());
        return *this;
    }

    Color& operator+=(const Color& color)
    {
        r += color.red();
        b += color.blue();
        g += color.green();
        a += color.alpha();

        return *this;
    }

    friend Color operator+(const Color& c1, const Color& c2)
    {
        Color c(c1);
        c += c2;
        return c;
    }

    Color& operator*=(const Color& color)
    {
        r *= color.red();
        g *= color.green();
        b *= color.blue();
        a *= color.alpha();

        return *this;
    }

    Color& operator*=(float value)
    {
        r *= value;
        g *= value;
        b *= value;
        a *= value;

        return *this;
    }

    friend Color operator*(const Color& c1, const Color& c2)
    {
        Color c(c1);
        c *= c2;
        return c;
    }

    friend Color operator*(const Color& c1, float value)
    {
        Color c(c1);
        c *= value;
        return c;
    }

    Color& operator/=(float value)
    {
        r /= value;
        g /= value;
        b /= value;
        a /= value;

        return *this;
    }

    friend Color operator/(const Color& c1, float value)
    {
        Color c(c1);
        c /= value;

        return c;
    }

    Color operator/=(int value)
    {
        return *this /= (float) value;
    }

    friend Color operator/(const Color& c1, int value)
    {
        return c1 / (float) value;
    }


    Color& clamp() { clamp(r); clamp(g); clamp(b); clamp(a); return *this; }

    operator rgb() { return this->toQColor().rgb(); }

private:
    inline void clamp(float& val) { clamp(val, 0.0f, 1.0f); }
    inline void clamp(float& val, float _min, float _max) { val = std::max(_min, std::min(_max, val)); }

    float r, g, b, a;
};

#endif // COLOR_H
