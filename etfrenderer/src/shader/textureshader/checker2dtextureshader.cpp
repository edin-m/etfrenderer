#include "shader/textureshader/checker2dtextureshader.h"

#include <cmath>
#include "xmlutil.h"

Checker2DTextureShader::Checker2DTextureShader() :
    m_color1(Color(rgb(0xff000000))),
    m_color2(Color(rgb(0xffffffff))),
    m_size(10.0f)
{

}

bool Checker2DTextureShader::loadFromXML(const QString &xml)
{
    if( xmlutil::attr(xml, "type").toLower() != "checker2d" )
        return false;

    bool ok = false;
    unsigned _shaderid = xmlutil::attr(xml, "id").toUInt(&ok);
    m_id = ok ? _shaderid : m_id;

    m_color1 = xmlutil::color(xmlutil::evaluate(xml, "/shader/color1"));
    m_color2 = xmlutil::color(xmlutil::evaluate(xml, "/shader/color2"));

    float _size = xmlutil::evaluate(xml, "/shader/size/data(.)").toFloat(&ok);
    m_size = ok ? _size : m_size;

    return true;
}

Color Checker2DTextureShader::shade(const Ray &ray,
                                    const HitRecord& result,
                                    const Light *) const
{
    const float& size = m_size;

    int _x = (int)floor(result.uv.x() * size);
    int _y = (int)floor(result.uv.y() * size);

    if( (int)(_x + _y) % 2 == 0 )
        return m_color1;

    return m_color2;
}
