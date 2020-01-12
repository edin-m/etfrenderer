#ifndef MATERIALSHADER_H
#define MATERIALSHADER_H

#include "shader.h"
#include "etfrenderer.h"
#include "util/sl.h"
#include "exception.h"

class MaterialShader : public Shader
{
public:
    class ReflectionMaterial;
protected:
    ReflectionMaterial* m_refl_mat;
public:
    MaterialShader() :
        m_refl_mat(NULL) {}
    virtual ~MaterialShader()
    {
        if( m_refl_mat != NULL )
            delete m_refl_mat;
    }

    /**
      TODO: implement or make pure virtual
      */
    virtual Color shade(const Ray &ray, const HitRecord &) const
    {
        return Color("pink");
        //throw MethodNotImplemented();
    };

    /**
        Loads material properties such as:
            reflection, refraction, transparency
      */
    virtual bool loadFromXML(const QString& xml);

    /**
      Reflection manuals models surface reflection.
      */
    class ReflectionMaterial : public Shader
    {
        float m_refl_factor;
        Color m_refl_color;
    public:
        ReflectionMaterial() :
            m_refl_factor(0.0f),
            m_refl_color(Color()) {}

        Color shade(const Ray&, const HitRecord&, const Light*) const
        {
            throw MethodNotImplemented();
        }

        /**
          Evaluates a shader.
          */
        Color shade(const Ray& ray, const HitRecord& result);

        /**
          Loads reflection tags.
          */
        bool loadFromXML(const QString &xml);
    };
};

#endif // MATERIALSHADER_H
