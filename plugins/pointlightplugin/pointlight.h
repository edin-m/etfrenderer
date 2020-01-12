#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <QXmlQuery>
#include <QDebug>
#include <QColor>

#include "light.h"
#include "xmlutil.h"

class PointLight : public Light
{
public:
    PointLight();

    vec3 incidence(const vec3& point) const;
    float distance(const vec3& point) const;

    bool loadFromXML(const QString& xml);

private:
    vec3 m_location;
};

#endif // POINTLIGHT_H
