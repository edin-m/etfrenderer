#ifndef LIGHT_H
#define LIGHT_H

#include "types.h"
#include "structs.h"

enum LightType
{
    POINT,
    UNKNOWN
};

class Light
{
public:
    virtual ~Light() {}

    QString name() const { return m_name; }

    static LightType str2type(const QString& typeName)
    {
        QString _name = typeName.toLower();

        if( _name == "point" )
            return POINT;

        return UNKNOWN;
    }

    float intensity() const { return m_intensity; }
    Color color() const { return m_color; }

    virtual float distance(const vec3& point) const = 0;
    virtual vec3 incidence(const vec3& vec) const = 0;

protected:
    LightType type;
    QString m_name;
    uint id;

    float m_intensity;
    Color m_color;
};

#endif // LIGHT_H
