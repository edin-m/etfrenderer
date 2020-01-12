#ifndef SCENE_H
#define SCENE_H

#include <QList>

#include "types.h"
#include "shape.h"
#include "shader.h"
#include "light.h"
#include "camera.h"

class Scene
{
    static uint ID;

public:
    struct info
    {
        int width;
        int height;
        QString output_filename;
        rgb bgcolor;
    };

    Scene();

    uint id();

    void add(const Shape*   shape);
    void add(const Shader* shader);
    void add(const Light* light);
    void add(const Camera* camera);

    const QList<const Shape*>&      shapes()  const;
    const QList<const Shader*>&     shaders() const;
    const QList<const Light*>&      lights() const { return m_lights; }
    const QList<const Camera*>&     cameras() const { return m_cameras; }

    /**
      Returns Shader* with id as specified as unsigned or QString.
              NULL    if doesn't find it.
      */
    const Shader* findShaderById(unsigned id) const;
    const Shader* findShaderById(const QString& id) const;

    bool isLoaded() const { return m_loaded; }
    void setLoaded(bool _loaded) { m_loaded = _loaded; }

    const Shape* findHitShape(HitRecord& result,
                              const Ray& ray) const;

    Color traceRay(const Ray& ray, int depth = 1) const;
    void clear();
private:

    bool m_loaded;
    QList<const Shape*>     m_shapes;
    QList<const Shader*>    m_shaders;
    QList<const Light*>     m_lights;
    QList<const Camera*>    m_cameras;

};

#endif // SCENE_H
