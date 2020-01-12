#include "phongshader.h"

PhongShader::PhongShader()
    :
      m_diffuse_shader(NULL),
      m_specular_shader(NULL),
      m_speculardecay(10)

{
}

Color PhongShader::shade(const Ray& ray, const HitRecord &result, const Light *light) const
{
    // slican Lambertu

    // uzimamo upadni vektor svjetlosti
    vec3 LV = light->incidence(result.intersection_point);

    // racunamo prirodu ugla
    double _dot = dot(result.normal, LV);

    if( _dot > 0 )
    {
        // vektor refleksije
        //vec3 R = 2 * _dot * result.normal - LV;
        vec3 R = sl::reflect(_dot, LV, result.normal);
        R.normalize(); // moguce da ne treba ova linija

        // ostatak formule
        double RV = dot(R, ray.direction.normalized());
        RV = pow((double)RV, (int)m_speculardecay) * _dot;

        //Color col(result.color);
        Color col(m_diffuse_color);
        if( m_diffuse_shader != NULL )
            col = Color(m_diffuse_shader->shade(ray, result, light));

        col *= light->color();
        col *= _dot;

        Color colR(m_specular_color);
        if( m_specular_shader != NULL )
            colR = Color(m_specular_shader->shade(ray, result, light));

        colR *= RV;

        Color final(0.f, 0.f, 0.f, 0.f);
        final += col;
        final += colR;

        if( m_refl_mat != NULL )
            final += m_refl_mat->shade(ray, result);

       // qDebug() << col << colR << final << " ---------------";
        return final;
    }

    return Color(rgb(0x00000000));
}

Color PhongShader::shade(const Ray &ray, const HitRecord &result) const
{
    return Color(QColor("green"));
}

/**
  Evaluates shader color parameter.
  */
void eval_shader_color(const QString& xml,
                       const QString& xpath,
                       const Shader*& shader, // mora biti ref na ptr
                       Color& color)
{
    QString _shaderid = xmlutil::attr(xmlutil::evaluate(xml, xpath), "shaderid");
    if( (shader = qScene->findShaderById(_shaderid)) != NULL )
        return;

    color = xmlutil::color(xmlutil::evaluate(xml, xpath));
}

bool PhongShader::loadFromXML(const QString& xml)
{
    QString shading = xmlutil::attr(xml, "shading").toLower();
    if( shading != "phong" )
        return false;

    Shader::loadID(xml);
    MaterialShader::loadFromXML(xml);

    bool ok = false;
    uint _speculardecay = xmlutil::attr(xmlutil::evaluate(xml, "/shader/specular"), "decay").trimmed().toUInt(&ok);
    m_speculardecay = ok ? _speculardecay : m_speculardecay;

    eval_shader_color(xml,
                      "/shader/diffuse",
                      m_diffuse_shader,
                      m_diffuse_color);

    eval_shader_color(xml,
                      "/shader/specular",
                      m_specular_shader,
                      m_specular_color);


//    //Scene* scene = ((Etfrenderer*) qvariant_cast<QObject*>(qApp->property("etfrenderer")))->scene();
//    const Scene* scene = qEtfrenderer->scene();

//    QString _shaderid = xmlutil::attr(xmlutil::evaluate(xml, "/shader/diffuse"), "shaderid");
//    const Shader* diffuse_shader = scene->findShaderById(_shaderid);

//    if( diffuse_shader != NULL )
//        m_diffuse_shader = diffuse_shader;

//    m_diffuse_color = xmlutil::color(xmlutil::evaluate(xml, "/shader/diffuse/color"));

//    QString _specularshaderid = xmlutil::attr(xmlutil::evaluate(xml, "/shader/specular"), "shaderid");
//    const Shader* specular_shader = scene->findShaderById(_specularshaderid);

//    if( specular_shader != NULL )
//        m_specular_shader = specular_shader;

//    m_specular_color = xmlutil::color(xmlutil::evaluate(xml, "/shader/specular/color"));

    //qDebug() << diffuse_shader << (diffuse_shader != NULL ? QString("%1").arg(diffuse_shader->id()) : "NULL") << m_diffuse_color;

    return true;

}
