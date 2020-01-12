#ifndef CAMERA_H
#define CAMERA_H

#include <QString>

#include "types.h"
#include "structs.h"
#include "shader/lensshader.h"

enum CameraType
{
    PERSPECTIVE,
    ORTHO
};

class Camera
{
public:

    virtual ~Camera(){}

    /**
      Casts ray for given view-plane point and size.
      Ray may pass through lenses.
      */
    virtual Ray cast(const vec2& xy, int width, int height) const = 0;

    /**
      Shades ray. Function is interface for LensShader::shade() Camera has LensShader.
      */
    virtual Color shade(const Ray& ray) const = 0;

    /**
      Loads this camera.
      */
    virtual bool loadFromXML(const QString& xml) = 0;

    const LensShader* shader() const { return lensShader; }

    /**
      @deprecated

      This function should not be used anymore.
      */
    static CameraType str2type(const QString& typeName)
    {
        QString _name = typeName.toLower();

        if( _name == "perspective" || _name == "persp" )
            return PERSPECTIVE;
        else if( _name == "ortho" || _name == "orthographic" )
            return ORTHO;

        return PERSPECTIVE;
    }

protected:
    // id kamere
    uint m_cameraid;

    // tip kamere
    CameraType type;

    // naziv kamere
    QString m_name;

    // lenses
    const LensShader* lensShader;
};

#endif // CAMERA_H
