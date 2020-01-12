#ifndef STRUCTS_H
#define STRUCTS_H

#include <QColor>

#include "types.h"
#include "color.h"

/**
 linija - zraka svjetlosti
 u literaturi poznatija kao R = O + tD | O = origin, D = direction, t = distance
 t je sadrzan u HitRecord
 */
struct Ray{
    Ray() {}
    Ray(const vec3& _origin, const vec3& _direction, bool normalizeDirection = true) :
        origin(_origin), direction(_direction)
    {
        //if( normalizeDirection )
        direction = _direction.normalized();

        invdir = vec3(1.0 / direction.x(), 1.0 / direction.y(), 1.0 / direction.z());
//        sign[0] = (invdir.x() < 0);
//        sign[1] = (invdir.y() < 0);
//        sign[2] = (invdir.z() < 0);
    }

    inline const vec3& o() const { return origin; }
    inline const vec3& d() const { return direction; }

    void setOrigin(const vec3& _origin) { origin = _origin; }
    void setDirection(const vec3& _direction) { direction = _direction; }

//    int sign[3];
    float tmin, tmax;
    vec3 invdir;

    vec3 direction;
    vec3 origin;

    friend QDebug operator<<(QDebug dbg, const Ray& ray)
    {
        dbg.nospace() << "Ray(" << ray.origin << ray.direction << ")";
        return dbg.space();
    }
};

/**
 HitRecord koji sadrzi podatke o pogotku zrake
 */
class Shape;
typedef struct {
    float t;
    vec3 normal;
    Color color;
    vec3 intersection_point;
    vec2 uv;
    const Shape* shape;
} HitRecord;


/**
 ortho-normal basis - u osnovi 3D-koord sistem definisan sa 3 vektora uvw
 */
class ONB
{
public:
    ONB() { }
    ONB(const vec3& u, const vec3& v, const vec3& w) { setU(u); setV(v); setW(w); }

    void normalize() { m_u.normalize(); m_v.normalize(); m_w.normalize(); }

    void setU(const vec3& u) { this->m_u = u; }
    void setV(const vec3& v) { this->m_v = v; }
    void setW(const vec3& w) { this->m_w = w; }

    const vec3& U() const { return m_u; }
    const vec3& V() const { return m_v; }
    const vec3& W() const { return m_w; }

    const vec3& u() const { return m_u; }
    const vec3& v() const { return m_v; }
    const vec3& w() const { return m_w; }

private:
    vec3 m_u, m_v, m_w;
};

#endif // STRUCTS_H
