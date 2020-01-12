#ifndef PERSPCAMERA_H
#define PERSPCAMERA_H

#include <QDebug>
#include <QXmlQuery>

#include "structs.h"
#include "xmlutil.h"
#include "camera.h"
#include "sampler.h"
#include "shader/lensshader.h"

class PerspCamera : public Camera
{
public:
    PerspCamera();
    ~PerspCamera();

    /** camera.h */
    Ray cast(const vec2& xy, int width, int height) const;

    /** camera.h */
    Color shade(const Ray& ray) const;

    /** camera.h */
    bool loadFromXML(const QString &xml);

private:
    /**
      Racuna OrthoNormal Basis tj. koord sistem kamere.
      */
    void calculate_onb();

    // camera orthonormal basis / view / eye / coordinate system
    ONB  m_onb;

    // camera position
    vec3 m_position;

    // direction.z = onb.w() * distance
    float distance;

    // camera up vector
    vec3 m_upvec;

    // point camera is looking at
    vec3 m_lookat;

    // sampler - lens, point sampler
    Sampler* sampler;
};


#endif // PERSPCAMERA_H
