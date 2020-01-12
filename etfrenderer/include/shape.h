#ifndef SHAPE_H
#define SHAPE_H

#include "structs.h"
#include "shader.h"
#include "types.h"
#include "util/bbox.h"

// DEPRECATED - ovo treba izbaciti i sve sto ga koristi
enum ShapeType
{
    SPHERE,
    PLANE,
    TRIANGLE,
    TRIMESH,


    NONE
};

class Shape
{
public:
    virtual ~Shape(){}

    QString name() const { return m_name; }
    unsigned Id() const { return id; }
    const Shader* shader() const { return m_shader; }

    /** Vrsi hit test Ray sa Shape-om.
      Vraca bool i popunjava HitRecord. */
    virtual bool hit(const Ray&, HitRecord&, bool isShadowRay = false) const = 0;

    /** Ucitava Shape parametre iz XML-a.
      Vraca bool; false u slucaju neuspjeha. */
    virtual bool loadFromXML(const QString& xml) = 0;

    virtual const vec3& center() const { return m_center; }

    /** DEPRECATED ovu funkciju treba izbaciti i sve sto je koristi */
    static ShapeType str2type(const QString& typeName)
    {
        QString _name = typeName.toLower();

        if( _name == "sphere" )
            return SPHERE;
        else if( _name == "plane" )
            return PLANE;
        else if( _name == "triangle" )
            return TRIANGLE;
        else if( _name == "trimesh" )
            return TRIMESH;

        return NONE;
    }
protected:
    // radi efikasnije implementacije predvidjen je Shader
    const Shader* m_shader;

    // ovo i nije potrebno
    ShapeType type;

    // naziv shape-a
    QString m_name;

    vec3 m_center;

    // id shape-a
    uint id;
};

#endif // SHAPE_H
