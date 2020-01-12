#ifndef TYPES_H
#define TYPES_H

typedef unsigned int uint;

#include <QRgb>
typedef QRgb qrgb;
typedef qrgb rgb;

/* ------------- QVector typedefs --------------- */
// ukoliko se ne zele koristiti Qtovi vektori kao vec2 vec3 itd
// definise se _NO_USE_QVEC
#ifndef _NO_USE_QVEC

    #include <QVector2D>
    typedef QVector2D qvec2;
    typedef qvec2 vec2;

    #include <QVector3D>
    typedef QVector3D qvec3;
    typedef qvec3 vec3;

    #include <QVector4D>
    typedef QVector4D qvec4;
    typedef qvec4 vec4;

    /* ------------- vector functions defs --------------- */
    #define qdot2 QVector2D::dotProduct
    #define qdot3 QVector3D::dotProduct
    #define qdot4 QVector4D::dotProduct
    #define dot qdot3

    #define qcross2 QVector2D::crossProduct
    #define qcross3 QVector3D::crossProduct
    #define qcross4 QVector4D::crossProduct
    #define cross qcross3

    #define qnormal QVector3D::normal

#endif

/* ------------- math function defs --------------- */
#include "math.h"
#define  er_sqrt sqrt

const double PI = 3.1415926535;
const double invPI = 1.0 / PI;
const double PI_under_180 = 180.0f / PI;
const double PI_over_180 = PI / 180.0f;

#include <QApplication>
class Etfrenderer;
#define qEtfrenderer ((Etfrenderer*) qvariant_cast<QObject*>(qApp->property("etfrenderer")))
#define qScene qEtfrenderer->scene()

#endif // TYPES_H
