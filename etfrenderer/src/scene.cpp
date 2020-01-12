#include "scene.h"
#include "etfrenderer.h" // ovo se ne ukljucuje u .h zbog circular dependency
#include "util/sl.h"

uint Scene::ID = 1;

Scene::Scene() : m_loaded(false)
{

}

/**
  Ove dvije funkcije privremeno su ovdje i vrse traceing scene
  */
static bool checkForShadows(HitRecord& result,
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

/**
  Ove dvije funkcije privremeno su ovdje i vrse traceing scene
  */
static Color trace(const Ray& ray, int depth)
{
    if( depth == 0 )
        return Color(); // TODO: treba vratiti boju pozadine

    const Scene* scene = qEtfrenderer->scene();

    HitRecord result;
    const Shape* hitShape = scene->findHitShape(result, ray);

    if( hitShape == NULL )
        return Color(); // TODO: treba vratiti boju pozadine

    Color final;
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

    return final;
}

uint Scene::id()
{
    return Scene::ID++;
}

void Scene::add(const Shape *shape)
{
    m_shapes.append(shape);
}

void Scene::add(const Shader* shader)
{
    m_shaders.append(shader);
}

void Scene::add(const Light* light)
{
    m_lights.append(light);
}

void Scene::add(const Camera* camera)
{
    m_cameras.append(camera);
}

const QList<const Shape*>& Scene::shapes() const
{
    return m_shapes;
}

const QList<const Shader*>& Scene::shaders() const
{
    return m_shaders;
}

const Shader* Scene::findShaderById(unsigned id) const
{
    return findShaderById(QString("%1").arg(id));
}

const Shader* Scene::findShaderById(const QString& id) const
{
    foreach(const Shader* shader, m_shaders)
    {
        if( QString("%1").arg(shader->id()) == id )
            return shader;
    }

    return NULL;
}

/*!

    This function finds closest shape intersected with ray.
    Returns NULL if no shape is intersected.

*/
const Shape* Scene::findHitShape(HitRecord& result,
                                 const Ray& ray) const
{
    const Scene* scene = qEtfrenderer->scene();
    const Shape* hitShape = NULL;

    foreach(const Shape* shape, scene->shapes())
    {
        HitRecord new_result;
        bool hit = shape->hit(ray, new_result);

        if( hit && new_result.t > 0 )
        {
//            shape->hit(ray, new_result, false);
            // new_result.t < result.t omogucava odabir najblizeg pogodjenog objekta
            if( hitShape == NULL || ( new_result.t < result.t ) )
            {
                result       = new_result;
                hitShape     = shape;
                result.shape = shape;
            }

//            qDebug() << ray.origin() << ray.direction() << _shape->name() << _result.t << hitShape->name() << result.t;
        }
    }

    return hitShape;
}

Color Scene::traceRay(const Ray &ray, int depth) const
{
    return trace(ray, depth);
}

void Scene::clear()
{
    m_loaded = false;
    m_shapes.clear();
    m_shaders.clear();
    m_lights.clear();
    m_cameras.clear();
}



