#include "util/bbox.h"

#include <limits>

BoundingBox::BoundingBox(const vec3& _p0, const vec3& _p1)
    :
      p0(_p0),
      p1(_p1)
{
}

void BoundingBox::append(const vec3& vec)
{
    float delta = 0.00001f;

    if( p0.x() > vec.x() )
        p0.setX(vec.x());

    if( p1.x() < vec.x() )
        p1.setX(vec.x());


    if( p0.y() > vec.y() )
        p0.setY(vec.y());

    if( p1.y() < vec.y() )
        p1.setY(vec.y());


    if( p0.z() > vec.z() )
        p0.setZ(vec.z());

    if( p1.z() < vec.z() )
        p1.setZ(vec.z());
}

template <typename T>
bool ray_bbox2(const vec3& p0, const vec3& p1, const Ray& ray)
{
    // http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm

    T t1, t2;

    T tnear = -std::numeric_limits<T>::infinity();
    T tfar  = std::numeric_limits<T>::infinity();

    T xl = p0.x(), yl = p0.y(), zl = p0.z();
    T xh = p1.x(), yh = p1.y(), zh = p1.z();

    T xo = ray.origin.x(),    yo = ray.origin.y(),    zo = ray.origin.z();
    T xd = ray.direction.x(), yd = ray.direction.y(), zd = ray.direction.z();

    T invxd = 1.0 / xd, invyd = 1.0 / yd, invzd = 1.0 / zd;

    t1 = (xl - xo) * invxd;
    t2 = (xh - xo) * invxd;

    tnear = std::max(std::min(t1, t2), tnear);
    tfar  = std::min(std::max(t1, t2), tfar);

//    if( t1 > t2 )
//    {
//        double tmp = t1;
//        t1 = t2;
//        t2 = tmp;
//    }
//    if( t1 > tnear )
//        tnear = t1;
//    if( t2 < tfar )
//        tfar = t2;

    if( tnear > tfar )
        return false;

//    if( ray.invdir.x() > 0 )
//        std::swap(tnear, tfar);



    t1 = (yl - yo) * invyd;
    t2 = (yh - yo) * invyd;

    tnear = std::max(std::min(t1, t2), tnear);
    tfar  = std::min(std::max(t1, t2), tfar);

    if( tnear > tfar )
        return false;

//    if( ray.invdir.y() > 0 )
//        std::swap(tnear, tfar);



    t1 = (zl - zo) * invzd;
    t2 = (zh - zo) * invzd;

    tnear = std::max(std::min(t1, t2), tnear);
    tfar  = std::min(std::max(t1, t2), tfar);

    if( tnear > tfar )
        return false;

//    if( ray.invdir.z() > 0 )
//        std::swap(tnear, tfar);

    return true;
}

template <typename T>
bool ray_bbox3(const vec3& p0, const vec3& p1, const Ray& ray)
{
    // http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-box-intersection/

    using std::swap;

    T xl = p0.x(), yl = p0.y(), zl = p0.z();
    T xh = p1.x(), yh = p1.y(), zh = p1.z();

    T xo = ray.origin.x(),    yo = ray.origin.y(),    zo = ray.origin.z();
    T xd = ray.direction.x(), yd = ray.direction.y(), zd = ray.direction.z();

    T tmin, tmax;
    T tymin, tymax;
    T tzmin, tzmax;

    tmin = (xl - xo) / xd;
    tmax = (xh - xo) / xd;

    if (tmin > tmax)
        swap(tmin, tmax);

    tymin = (yl - yo) / yd;
    tymax = (yh - yo) / yd;

    if (tymin > tymax)
        swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (zl - zo) / xd;
    tzmax = (zh - zo) / xd;

    if (tzmin > tzmax)
        swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return true;


/**
    Postoji mogucnost da su sljedece grupe linija iz prethodne dvije
    funkcije ekvivalentne pa je u drugoj vise pisano [bespotrebno]

    tnear = std::max(std::min(t1, t2), tnear);
    tfar  = std::min(std::max(t1, t2), tfar);
    if( tnear > tfar )
        return false;

    i


    tzmin = std::min(t1, t2);
    tzmax  = std::max(t1, t2);

    if( tzmin > tzmax )
        std::swap(tzmin, tzmax);

    if( (tmin > tzmax) || (tzmin > tmax) )
        return false;

    if( tzmin > tmin )
        tmin = tzmin;
    if( tzmax < tmax )
        tmax = tzmax;

  */
}

bool BoundingBox::hit(const Ray& ray) const
{
    bool result = ray_bbox2<float>(p0, p1, ray);

    return result;
}
