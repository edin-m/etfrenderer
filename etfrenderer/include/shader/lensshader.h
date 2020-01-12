#ifndef LENSSHADER_H
#define LENSSHADER_H

#include "shader.h"
#include "sampler.h"

class LensShader : public Shader
{
public:
    LensShader() :
        m_sampler(NULL),
        m_radius(1.0f)
    {
    }

    virtual ~LensShader() {}

    virtual Color shade(const Ray &ray, const HitRecord &, const Light *) const { return Color(); }

    /**
      LensShader can use simplified shade() function.
      Shades ray - traces scene.
      */
    virtual Color shade(const Ray& ray) const = 0;

    /**
      Loading shader from xml.
      */
    virtual bool loadFromXML(const QString& xml) = 0;

    /**
      Determines ray direction for given points on view-plane and lens.
      */
    virtual vec3 ray_direction(const vec3& pixel_point,
                               const vec2& lens_point) const = 0;

    /**
      set/get sampler
      */
    void sampler(const Sampler* sampler) { m_sampler = sampler; }
    const Sampler* sampler() const { return m_sampler; }

    /**
      set/get radius
      */
    void radius(float radius) { m_radius = radius; }
    float radius() const { return m_radius; }

protected:
    const Sampler* m_sampler;
    float m_radius;
};

#endif // LENSSHADER_H
