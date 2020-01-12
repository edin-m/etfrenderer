#ifndef TRIANGLESHAPE_H
#define TRIANGLESHAPE_H

#include <QXmlQuery>
#include <QDebug>

#include "types.h"
#include "structs.h"
#include "shape.h"
#include "xmlutil.h"
#include "etfrenderer.h"

class TriangleShape : public Shape
{
public:
    TriangleShape();

    void set(const vec3& p1, const vec3& p2, const vec3& p3);

    /**
      Funkcija koja uzima tri tacke i zraku i vraca bool da li je
      trokut pogodjen i popunjava HitRecord
      */
    static bool hitStatic(
            const vec3& point0,
            const vec3& point1,
            const vec3& point2,
            const Ray&,
            HitRecord&,
            bool isShadowRay,
            bool debug = false
           );

    /**
      Interfejs funkcija da podrzi vec3* niz od 3 clana.
      */
    static bool hitStatic(
            const vec3* array,
            const Ray&,
            HitRecord&,
            bool isShadowRay
           );

    /**
      Interfejs funkcija za ovu klasu.
      */
    bool hit(const Ray&, HitRecord&, bool isShadowRay) const;

    bool loadFromXML(const QString& xml);

    /**
      Creator funkcija koja kreira Shape.
      Vraca NULL u slucaju neuspjeha.
      */
    static const Shape* fromXML(const QString& xml);

private:
    vec3 m_points[3];
    rgb m_color;
};

typedef TriangleShape Triangle;
typedef Triangle triangle;

#endif // TRIANGLESHAPE_H
