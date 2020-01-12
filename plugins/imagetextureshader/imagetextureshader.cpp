#include "imagetextureshader.h"

ImageTextureShader::ImageTextureShader()
{
}

Color ImageTextureShader::shade(const Ray&, const HitRecord& result, const Light* light) const
{
    // TODO: (optional) kada dodju filteri na djelo ovdje se trebaju iskoristiti

    int _x = (int)(result.uv.x() * m_image.width());
    int _y = (int)(result.uv.y() * m_image.height());

    //qDebug() << _x << _y << m_image.width() << result.uv;

    if( _x < 0 || _y < 0 || m_image.width() <= _x || m_image.height() <= _y )
        return Color("purple");

    return Color( QColor(m_image.pixel(_x, _y)) );
}

bool ImageTextureShader::loadFromXML(const QString& xml)
{
    bool ok;

    QString shading = xmlutil::attr(xml, "shading").toLower();
    if( shading != "image" )
        return false;

    uint _id = xmlutil::attr(xml, "id").trimmed().toUInt(&ok);
    if( ok )
        m_id = _id;

    QString location = xmlutil::attr(xmlutil::evaluate(xml, "/shader/image"), "location");
    bool result = m_image.isNull() && m_image.load(location);

    if( !result )
        return false;

    qDebug() << "Image shader\t" << "ImageTextureShader loaded image from" << location;

    return true;
}
