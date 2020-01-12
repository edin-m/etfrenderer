#include "camera/perspcamera.h"
#include "sampler/randomsampler.h"
#include "shader/lensshader/thinlensshader.h"

PerspCamera::PerspCamera()
{

}

PerspCamera::~PerspCamera()
{
    delete sampler;
}

Ray PerspCamera::cast(const vec2 &xy, int width, int height) const
{
    const ONB& onb = m_onb;

    // getting x, y from point on image plane and sampling it
    float x = xy.x() - width  * 0.5/* + sampler->sample().x()*/;
    float y = height * 0.5 - xy.y()/* + sampler->sample().y()*/;

    // camera has lens ?
    if( lensShader != NULL )
    {
        vec2 v = sampler->sample();
        x += v.x();
        y += v.y();

        // lens sampling
        vec2 lens_point = sampler->sample() * lensShader->radius();

        Ray ray;

        // ray originates from lens
        ray.origin = m_position +
                     lens_point * onb.u() +
                     lens_point * onb.v();

        // lens calculate direction
        vec3 dir = lensShader->ray_direction(vec3(x, y, distance), lens_point);
        ray.direction = dir.x() * onb.u() +
                        dir.y() * onb.v() +
                        dir.z() * onb.w();

        // TODO: normalize direction
        return ray;
    }
    else
    {
        Ray ray;
        ray.origin = m_position;

        vec3 dir = x * onb.u() + y * onb.v() - distance * onb.w();
        ray.direction = dir;

        // TODO: normalize direction
//        ray.direction.normalize();

        return ray;
    }
}

Color PerspCamera::shade(const Ray& ray) const
{
    // shade (trace) ray with lens if [camera] has one
    if( lensShader != NULL )
    {
        return lensShader->shade(ray);
    }
    else
    {
        return qEtfrenderer->scene()->traceRay(ray);
    }
}

bool PerspCamera::loadFromXML(const QString &xml)
{
    QString xpath;

    bool ok = false;
    int _cameraid = xmlutil::attr(xml, "id").toUInt(&ok);
    m_cameraid = ok ? _cameraid : 0;

    m_name = xmlutil::attr(xml, "name");

    xpath = "/camera/pos";
    m_position = xmlutil::xml2vec3(xmlutil::evaluate(xml, xpath));

    xpath = "/camera/up";
    m_upvec = xmlutil::xml2vec3(xmlutil::evaluate(xml, xpath));

    xpath = "/camera/distance/data(.)";
    QString eval = xmlutil::evaluate(xml, xpath);

    distance = eval.toFloat();

    xpath = "/camera/lookat";
    m_lookat = xmlutil::xml2vec3(xmlutil::evaluate(xml, xpath));

//        qDebug() << m_position
//                 << distance
//                 << m_upvec;

    calculate_onb();



    sampler = new RandomSampler;
    sampler->generate(100);

    // binding shader using <shader id="..">
    QString _shaderid = xmlutil::attr(xmlutil::evaluate(xml, "/camera/shader"), "id");
    lensShader = dynamic_cast<const LensShader*>(qEtfrenderer->scene()->findShaderById(_shaderid));

    if( lensShader != NULL )
        const_cast<LensShader*>(lensShader)->sampler(sampler);

    return true;
}

void PerspCamera::calculate_onb()
{
    vec3 w = m_position - m_lookat;
    w.normalize();

    vec3 u = cross(m_upvec, w);
    u.normalize();

    vec3 v = cross(w, u);
    v.normalize();

    m_onb.setU(u);
    m_onb.setV(v);
    m_onb.setW(w);
    m_onb.normalize();
}
