#include "raytracer.h"
#include "sampler/randomsampler.h"
#include "shader/materialshader.h"

Raytracer::Raytracer()
{
}

bool checkForShadows(HitRecord& result,
                     const Light* _light)
{
    const Scene* scene = qEtfrenderer->scene();

    const vec3 LV = _light->incidence(result.intersection_point);

    Ray shadowRay(result.intersection_point, -LV * 9999);
    HitRecord shadowRayResult;

    // definisemo d kao udaljenost izmedju objekta odakle je krenula
    // shadow zraka i svjetla
    float d = _light->distance(result.intersection_point);

    foreach(const Shape* shape, scene->shapes())
    {
        // ignorisemo provjeru sjencenja samoga sebe mada bi ovo trebalo omoguciti
        // i testirati
        if( shape == result.shape ) continue;

        bool res = shape->hit(shadowRay, shadowRayResult, true);

        if( !res )
            continue;

        bool tmp = false;

        // posto se zraka moze presjeci sa objektima koji zapravo ne stoje izmedju
        // hitShape i _light, potrebna je dodatna provjera
        tmp = (result.intersection_point - shadowRayResult.intersection_point).length() < d;
        tmp = tmp && (_light->distance(shadowRayResult.intersection_point) < d);

        if( tmp )
        {
            return true;
        }

    }

    return false;
}

#include "util/sl.h"
#include "shader/materialshader.h"
Color trace(const Ray& ray, int depth)
{
    if( depth == 0 )
        return Color(); // TODO: treba vratiti boju pozadine

    depth--;

    const Scene* scene = qEtfrenderer->scene();

    HitRecord result;
    const Shape* hitShape = scene->findHitShape(result, ray);

    if( hitShape == NULL )
        return Color(); // TODO: treba vratiti boju pozadine

    Color refl_color;
    float refl_factor = 0.5f;

    if( hitShape->Id() == 111 ){
//        return Color(rgb(0xffff0000));


        //MaterialShader::ReflectionMaterial refl_mat;

        //refl_color = refl_mat.shade(ray, result);
//        Ray refl_ray;
//        refl_ray.origin = result.intersection_point;
////        refl_ray.direction = (ray.direction - 2 * dot(ray.direction, result.normal) * result.normal)
//////                .normalized()
////                ;

////        const vec3& in = ray.direction;
////        const vec3& normal = result.normal;

//        refl_ray.direction = sl::reflect(ray.direction, result.normal);
////        refl_ray.direction = sl::reflect(ray.direction, result.normal);

////        refl_color = trace(refl_ray, depth);
//        refl_color = qEtfrenderer->scene()->traceRay(refl_ray, depth);

//        refl_color *= refl_factor;

//        HitRecord _result;
//        const Shape* shp = scene->findHitShape(_result, refl_ray);
//        foreach(const Light* _l, scene->lights())
//        {
//            ret_color += hitShape->shader()->shade(ray, result, _l);
//            if( shp != NULL && shp->shader() != NULL )
//                ret_color += shp->shader()->shade(refl_ray, _result, _l);
//        }
//        return ret_color;
    }

    Color final;

    if( hitShape->shader() != NULL )
        hitShape->shader()->shade(ray, result);

    foreach(const Light* light, scene->lights())
    {
        bool inshadow = checkForShadows(result, light);
        if( inshadow ) continue;

        const Shader* shader = hitShape->shader();
        if( shader != NULL )
        {
            Color col;
            col = shader->shade(ray, result, light);

            final += col;
        }
    }

    final += refl_color;

    return final;
}

bool Raytracer::render(const FrameBuffer* framebuffer,
                       const QPoint& start,
                       const QSize& render_size)
{
    const Scene* scene = qEtfrenderer->scene();

    int width = start.x() + render_size.width();
    int height = start.y() + render_size.height();

    int max_width = framebuffer->qimage()->width();
    int max_height = framebuffer->qimage()->height();

    width = std::max(width, max_height);
    height = std::max(height, max_height);

    if( !scene->isLoaded() )
    {
        QMessageBox msg;
        msg.setText("Scene not loaded");
        msg.exec();
        return false;
    }

    // trenutno samo za testiranje persp proj.
    const Camera* pc = scene->cameras()[0];

    int num_samples = 1;

    // for each row
    for( int j = start.y(); j < height; j++ )
    {
        //qDebug() << "red: " << (i+1);
        if( j % 20 == 0 )
            m_update_callback((j+1) * 100.0f / height);

        // for each pixel in a row
        for( int i = start.x(); i < width; i++ )
        {
            Color final_boja;
            for(int k = 0; k < num_samples; k++)
            {
//                qDebug() << "tracing " << ij;
                Ray ray = pc->cast(vec2(i, j), max_width, max_height);

                //pc->shader()->shade()
                //boja = trace(ray/*, result*/).toQColor().rgb();

//                Color final = trace(ray, 1);

                final_boja += trace(ray, 3);
//                final_boja += pc->shade(ray);


                // priprema za upis pixela
//                boja = (Color(boja) + final).clamp();
//                final_boja += final;

            }

            final_boja = final_boja / num_samples;
//            operator<<(qDebug(), final_boja);
            framebuffer->set(i, j, final_boja.clamp());
        }
    }
    return true;
}


/**
  Code below is deprecated
  */

//bool Raytracer::checkForShadows(HitRecord& result,
//                                const Light* _light)
//{
//    const Scene* scene = qEtfrenderer->scene();

//    const vec3 LV = _light->incidence(result.intersection_point);

//    Ray shadowRay(result.intersection_point, -LV * 9999);
//    HitRecord shadowRayResult;

//    // definisemo d kao udaljenost izmedju objekta odakle je krenula
//    // shadow zraka i svjetla
//    float d = _light->distance(result.intersection_point);

//    foreach(const Shape* shape, scene->shapes())
//    {
//        // ignorisemo provjeru sjencenja samoga sebe mada bi ovo trebalo omoguciti
//        // i testirati
//        if( shape == result.shape ) continue;

//        bool res = shape->hit(shadowRay, shadowRayResult, true);

//        if( !res )
//            continue;

//        bool tmp = false;

//        // posto se zraka moze presjeci sa objektima koji zapravo ne stoje izmedju
//        // hitShape i _light, potrebna je dodatna provjera
//        tmp = (result.intersection_point - shadowRayResult.intersection_point).length() < d;
//        tmp = tmp && (_light->distance(shadowRayResult.intersection_point) < d);

//        if( tmp )
//        {
//            return true;
//        }

//    }

//    return false;
//}
