#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QtXml>
#include <QtXmlPatterns>
#include <QtXmlPatterns/QXmlQuery>

/** ovo je beze funkcija za update render progresa */
void __cdecl progress_callback(int percent)
{
    mainWindow->ui->label->setText(QString("%1%").arg(percent));
    mainWindow->ui->imageLabel->setPixmap(QPixmap::fromImage(*mainWindow->fb->qimage()));
    qApp->processEvents();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fb(NULL)
{
    ui->setupUi(this);
    ui->imageLabel->setMouseTracking(true);
    ui->imageLabel->installEventFilter(this);
    ui->imageLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    pluginmanager = new PluginManager();
    scene = new Scene();

    etfrenderer = &Etfrenderer::instance();
    etfrenderer->set(scene);
    etfrenderer->set(pluginmanager);

    // postavljamo dijeljenu varijablu kako bi pluginovi mogli pristupiti etfrendereru
    qApp->setProperty("etfrenderer", qVariantFromValue(qobject_cast<QObject*>(etfrenderer)));

    loadPlugins();

    renderer_callback = progress_callback;
    mainWindow = this;

    region_start = QPoint(0, 0);
    region_size  = QSize(500, 500);
    region_resize = false;

//    this->loadPlugins();



//    Ray ray(qvec3(1,2,3), qvec3(2,3,4));
//    double var = (double)ray.direction().x();
//    std::cout << var << std::endl;

}

MainWindow::~MainWindow()
{
    delete ui;

    delete scene;
    delete pluginmanager;
    //delete etfrenderer;
}

void MainWindow::loadPlugins()
{
    QDir pluginsDir = QDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        qDebug() << "fileName"<<fileName;
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            ShaderPlugin* shader = qobject_cast<ShaderPlugin*>(plugin);
            ShapePlugin*  shape  = qobject_cast<ShapePlugin*>(plugin);
            RendererPlugin* rend = qobject_cast<RendererPlugin*>(plugin);
            LightPlugin* light = qobject_cast<LightPlugin*>(plugin);

            if(shader){
                qDebug() << "shader: " << shader->name();
                pluginmanager->add(shader);
            }
            if(shape){
                qDebug() << "shape:" << shape->name();
                pluginmanager->add(shape);
            }
            if(rend){
                qDebug() << "renderer:" << rend->name();
                pluginmanager->add(rend);
            }
            if(light)
            {
                qDebug() << "light:" << light->name();
                pluginmanager->add(light);
            }



        } else {
            qDebug()<<"Plugin"<<fileName<<"error:"<<loader.errorString();
        }
    }

}


void MainWindow::on_renderBtn_clicked()
{
    QTime time;
    time.start();

    Renderer* renderer;

    bool testirajDrugiRenderer = false;

    if( testirajDrugiRenderer )
    {

        renderer = pluginmanager->getRenderers().size() > 1 ?
                    pluginmanager->getRenderers()[1]->renderer() :
                    pluginmanager->getRenderer()->renderer();

    }
    else
        renderer = pluginmanager->getRenderer()->renderer();

//    qDebug() << renderer->name();
//    qDebug() << etfrenderer->pluginManager()->getRenderer()->name();

    if( fb != NULL )
        delete fb;

    fb = new FrameBuffer(800,600);

//    rgb boja = 0x00ffffff;

//    fb->set(10,10,boja);

    qDebug() << "pt:" << etfrenderer->scene()->shapes();
    renderer->init( etfrenderer );
    renderer->setUpdateCallback(renderer_callback);
//    renderer->render(fb, QPoint(0, 130), QSize(350, 200));
    //renderer->render(fb, QPoint(150, 100), QSize(200, 200));
    //renderer->render(fb, QPoint(0, 0), QSize(500, 500));


    renderer->render(fb, region_start, region_size);
    fb->qimage()->save("wicked.png");

    const QImage* image = fb->qimage();
    QImage img(*image);

    QPainter painter;
    painter.begin(&img);
    int fontSize = 9;
    QFont font("Arial", fontSize);

    QRectF rect(0, fb->qimage()->height() - QFontMetrics(font).height(), fb->qimage()->width(), QFontMetrics(font).height());

    font.setWeight(QFont::Bold);
    painter.setFont(font);

    painter.fillRect(rect, QBrush(QColor(240, 240, 240, 180)));

    painter.setPen(QColor(10, 10, 10));
    painter.drawText(rect, Qt::AlignLeft, QString("Rendered with ETF Renderer. Time: %1 sec").arg(time.elapsed() / 1000.0f));


    ui->imageLabel->setPixmap(QPixmap::fromImage(img));
    ui->label->setText("100%");

    img.save("wicked.png");

    //delete fb;

    qDebug() << "finished";
}

void MainWindow::on_actionPlugins_2_triggered()
{
    PluginsWindow* pw = new PluginsWindow(this);
    pw->show();
}


void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionXmlTest_triggered()
{
}

void MainWindow::on_actionSphereFromXmlTest_triggered()
{

}
void MainWindow::loadScene()
{
    SceneLoader::instance(etfrenderer).loadScene();

}

void MainWindow::on_loadSceneBtn_clicked()
{
    ui->renderBtn->setEnabled(false);
    loadScene();
    ui->renderBtn->setEnabled(true);

}


#include "color.h"
void testColor()
{
    Color col(0.2f, 1.0f, 0.2f, 1.0f);
    col.multiply_rgb(0.5f);
    qDebug() << col;
}

void MainWindow::on_actionTest1_triggered()
{
//    testEmdobject();
}

void MainWindow::on_actionRun_all_tests_triggered()
{
    // color test

//    float a = 0.0;
//    float b = 100.0;
//    float t = 0.5;

//    float r = util::linear(a, b, t);
//    qDebug() << "Linear interpolation: " << r;

    // bbox test

//    BoundingBox bbox(vec3(0, 0, -200), vec3(50, 50, -250));

//    Ray ray2(vec3(250, 230, 80), vec3(-0.56, -0.161, -0.807));
//    bool r;
//    r = bbox.hit(ray2);
//    // treba biti FALSE
//    qDebug() << r;

//    Ray ray1(vec3(-115.171, 26.2343, -350), vec3(0.64, 0.0602, 0.7603));
//    r = bbox.hit(ray1);
//    // treba biti TRUE
//    qDebug() << r;

//    Ray ray3(vec3(250, 230, 80), vec3(-0.536354, -0.477133, -0.696181));
//    r = bbox.hit(ray3);
//    // treba biti TRUE, sigurno ?
//    qDebug() << r;

    vec3 v0, v1, v2;

    Ray ray;
    HitRecord rec;

    v0 = vec3(0, 0, -200);
    v1 = vec3(0, 50, -200);
    v2 = vec3(50, 0, -200);

    ray.setOrigin(vec3(10, 10, 0));
    ray.setDirection(vec3(0, 0, -1));

    qDebug() << "Prvi slucaj: " << ray.origin << ray.direction << TriangleShape::hitStatic(v0, v1, v2, ray, rec, false, true);

    v0 = vec3(0, 0, -200);
    v1 = vec3(0, 50, -200);
    v2 = vec3(-50, 0, -200);

    ray.setOrigin(vec3(-10, 10, 0));
    ray.setDirection(vec3(0, 0, -1));

    qDebug() << "Drugi slucaj: " << ray.origin << ray.direction << TriangleShape::hitStatic(v0, v1, v2, ray, rec, false, true);

    v0 = vec3(25, 25, -200);
    v1 = vec3(5, 25, -200);
    v2 = vec3(25, 5, -200);

    ray.setOrigin(vec3(20, 20, 0));
    ray.setDirection(vec3(0, 0, -1));

    qDebug() << "Treci slucaj: " << ray.origin << ray.direction << TriangleShape::hitStatic(v0, v1, v2, ray, rec, false, true);
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    static bool resize_started = false;

    if( object == ui->imageLabel )
    {
        if( event->type() == QEvent::MouseMove )
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));

            if( region_resize && resize_started)
            {
                QPoint tmp = QPoint(static_cast<QMouseEvent*>(event)->pos());
                region_size = QSize(tmp.x() - region_start.x(),
                                    tmp.y() - region_start.y());
                paintRegion();
            }

            return true;
        }
        else if( event->type() == QEvent::MouseButtonPress )
        {
            if( region_resize )
            {
                region_start = QPoint(static_cast<QMouseEvent*>(event)->pos());
                resize_started = true;
            }
        }
        else if( event->type() == QEvent::MouseButtonRelease )
        {
            if( region_resize )
            {
                QPoint tmp = QPoint(static_cast<QMouseEvent*>(event)->pos());
                region_size = QSize(tmp.x() - region_start.x(),
                                    tmp.y() - region_start.y());
                region_resize = false;
                resize_started = false;
                paintRegion();
            }
        }
        else
            return false;
    }
    else
    {
        return QMainWindow::eventFilter(object, event);
    }
}

void MainWindow::paintRegion()
{
    //QPixmap* pmap = new QPixmap(*ui->imageLabel->pixmap());
    static const QImage* image = NULL;
    if( image == NULL )
        image = fb->qimage();

    QPixmap pmap = QPixmap::fromImage(*image);
    QPainter p(&pmap);

    QPen   pen;
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2.0f);
    pen.setColor(QColor("purple"));

    p.setPen(pen);
    p.drawRect(QRectF(region_start, region_size));
    p.end();

    ui->imageLabel->setPixmap(pmap);
}

void MainWindow::on_actionSet_triggered()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Wicked sick");
    msgBox.setText("Povucite sa LMB region za renderisanje.");
    msgBox.exec();
    region_resize = true;

}

void MainWindow::on_actionReset_triggered()
{
    region_start = QPoint(0, 0);
    region_size  = QSize(500, 500);
}

void MainWindow::on_actionSampler_triggered()
{
    qDebug() << "Testing samplers";

    Sampler* sampler = new RandomSampler;
    sampler->generate(100);

    QImage image(100, 100, QImage::Format_ARGB32);
    sampler->testOutput(image);
    image = image.scaled(QSize(500, 500));
    image.save(sampler->name() + ".test1.jpg");

    delete sampler;
}

void MainWindow::on_actionCamera_triggered()
{
    qDebug() << "Testing camera";

    Camera* cam = new PerspCamera;
    cam->loadFromXML("<camera id=\"1\" name=\"camera1\" type=\"perspective\">"
                     "<pos x=\"250\" y=\"230\" z=\"280\" />"
                      "<dir x=\"0\" y=\"0\" z=\"-1\" />"
                      "<d>1600</d>"
                      "<up x=\"0\" y=\"1\" z=\"0\" />"
                      "<lookat x=\"0\" y=\"0\" z=\"0\" />"
                      "</camera>");

    const Ray& ray = cam->cast(vec2(0, 0), 500, 500);
    qDebug() << ray;

    delete cam;
}

void MainWindow::on_actionScene_Listing_triggered()
{
    // TODO: napraviti scene listing u scenelistingwindow-u

}
