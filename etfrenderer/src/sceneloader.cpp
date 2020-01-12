#include "sceneloader.h"

#include "camera/perspcamera.h"

#include "shader/lensshader/thinlensshader.h"
#include "shader/textureshader/checker2dtextureshader.h"

#include "shape/planeshape.h"
#include "shape/triangleshape.h"

SceneLoader::SceneLoader(Etfrenderer* renderer)
    :
      scene(NULL),
      etfrenderer(renderer)
{
    pluginmanager = renderer->pluginManager();
    scene = renderer->scene();
}

const Shape* SceneLoader::findCoreShape(const QString& xml)
{
    const Shape* shape;

    shape = Triangle::fromXML(xml);
    if( shape != NULL )
        return shape;

    shape = Plane::fromXML(xml);
    if( shape != NULL )
        return shape;


    return NULL;
}

void SceneLoader::loadScene(const QString& path)
{
    scene->clear();

    QDir dir(QDir::currentPath());
    dir.cdUp();
    dir.cd("doc");
//    qDebug() << "DIR: " << dir.filePath("scene.ers");

    QString fileName;

    if( path == "" )
        fileName = dir.filePath("scene.ers");
    else
        fileName = path;

    QUrl url = QUrl::fromLocalFile(fileName);

    QString evaluateTo;
    QString xpath;
    QXmlQuery query;

    query.setFocus(url);

    qDebug() << "load from xml ";

    // load sphere
//    const Shape* shape = plugin->fromXML(evaluateTo);
//    scene->add(shape);


    loadShaders(query);
    loadShapes(query);
    loadLights(query);
    loadCameras(query);

//    query.setQuery("//camera[1]");
//    query.evaluateTo(&evaluateTo);

//    qDebug() << evaluateTo;

//    PerspCamera* pc = new PerspCamera();
//    pc->loadFromXML(evaluateTo);

//    scene->add(pc);

    scene->setLoaded(true);
}

void SceneLoader::loadLights(QXmlQuery& query)
{
    const QList<LightPlugin*>& lightPlugins = pluginmanager->getLightPlugins();
    uint count = xmlutil::count(query, "//lights/*");

    QString evaluateTo;

    for(unsigned i = 0; i < count; i++)
    {
        QString _xpath(QString("//lights/light[%1]").arg(i + 1));
//        qDebug() << _xpath;

        query.setQuery(_xpath);
        query.evaluateTo(&evaluateTo);

        foreach(LightPlugin* plugin, lightPlugins)
        {
            const Light* _light = plugin->fromXML(evaluateTo);
            if( _light != NULL )
            {
                scene->add(_light);
                break;
            }
        }
    }

    qDebug() << "Ucitano lighs:" << etfrenderer->scene()->lights().count();

}

void SceneLoader::loadCameras(QXmlQuery &query)
{
    uint count = xmlutil::count(query, "/project/cameras/*");

    QString evaluateTo;

    for(unsigned i = 0; i < count; i++)
    {
        PerspCamera* pcam = new PerspCamera();
        QString _xpath(QString("//cameras/camera[%1]").arg(i+1));

        query.setQuery(_xpath);
        query.evaluateTo(&evaluateTo);

        if( pcam->loadFromXML(evaluateTo) )
        {
            scene->add(pcam);
            continue;
        }
        else
            delete pcam;

        //TODO: dodati za ortho cameru
    }

    qDebug() << "Ucitano kamera: " << scene->cameras().count();
}

void SceneLoader::loadShapes(QXmlQuery& query)
{
    const QList<ShapePlugin*>& shapePlugins = pluginmanager->getShapePlugins();
    uint count = xmlutil::count(query, "//objects/*");

    QString evaluateTo;

    for(unsigned i = 0; i < count; i++)
    {
        QString _xpath(QString("//objects/object[%1]").arg(i + 1));

        query.setQuery(_xpath);
        query.evaluateTo(&evaluateTo);

        bool added = false;
        foreach(ShapePlugin* plugin, shapePlugins)
        {
            const Shape* _shape = plugin->fromXML(evaluateTo);
            if( _shape != NULL )
            {
                scene->add(_shape);
                added = true;
                break;
            }
        }

        // ukoliko nije nijedan od pluginovanih shapeova
        // provjerimo je li jedan od core (triangle, plane)
        if( !added )
        {
            const Shape* coreShape = findCoreShape(evaluateTo);
            if( coreShape != NULL )
                scene->add(coreShape);
        }


    }

    qDebug() << "Ucitano shapeova: " << etfrenderer->scene()->shapes().count();
}

bool SceneLoader::loadFromShaderPlugins(const QString& xml)
{
    const QList<ShaderPlugin*>& plugins = pluginmanager->getShaders();

    foreach(const ShaderPlugin* plugin, plugins)
    {
        Shader* shader = plugin->fromXML(xml);

        if( shader != NULL )
        {
            scene->add(shader);
            qDebug() << "Ucitao" << plugin->name() << "shader";
            return true;
        }
    }

    return  false;
}

bool SceneLoader::loadFromBuiltInShader(const QString& xml)
{
    Shader* shader;

    // ThinLensShader
    {
        shader = new ThinLensShader;
        if( shader->loadFromXML(xml) )
        {
            scene->add(shader);
            qDebug() << "Ucitao ThinLensShader";
            return true;
        }
        else
            delete shader;
    }

    // Checker2D
    {
        shader = new Checker2DTextureShader;
        if( shader->loadFromXML(xml) )
        {
            scene->add(shader);
            qDebug() << "Ucitao Checker2DTextureShader";
            return true;
        }
        else
            delete shader;
    }

    return false;
}

void SceneLoader::loadShaders(QXmlQuery& query)
{
    QList<Shader*> shaders;

    const QList<ShaderPlugin*>& plugins = pluginmanager->getShaders();
    uint count = xmlutil::count(query, "/project/shaders/*");

    QString evaluateTo;

    // pass 1 - ucitavanje bilokakvo iz nekog Shadera
    for(uint i = 0; i < count; i++)
    {
        QString _xpath(QString("/project/shaders/shader[%1]").arg(i + 1));

        query.setQuery(_xpath);
        query.evaluateTo(&evaluateTo);

        if( loadFromShaderPlugins(evaluateTo) )
            continue;

        if( loadFromBuiltInShader(evaluateTo) )
            continue;

        qDebug() << "Failed to load shader: " << xmlutil::attr(evaluateTo, "id");

    }

//    for(uint i = 0; i < count; i++)
//    {
//        QString _xpath(QString("/project/shaders/shader[%1]").arg(i + 1));

//        query.setQuery(_xpath);
//        query.evaluateTo(&evaluateTo);

//        Shader* _shader = shaders[i];
//        _shader->loadFromXML(evaluateTo);

//        scene->add(_shader);
//    }

//    qDebug() << "Ucitano" << scene->shaders().count() << "shadera";
}
