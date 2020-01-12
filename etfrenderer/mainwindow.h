#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>

#include <QMainWindow>

#include <QVBoxLayout>
#include <QMainWindow>
#include <QPluginLoader>
#include <QDir>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QMenu>
#include <QFrame>
#include <QPoint>
#include <QList>
#include <QPainter>
#include <QTime>
#include <QFont>
#include <QFontMetrics>

#include <QDebug>

#include "pluginswindow.h"

#include "plugin/rendererplugin.h"
#include "plugin/shapeplugin.h"
#include "plugin/shaderplugin.h"
#include "plugin/lightplugin.h"

#include "pluginmanager.h"
#include "etfrenderer.h"
#include "renderer.h"
#include "shape/triangleshape.h"
#include "shape/planeshape.h"

#include "camera/perspcamera.h"

#include "sceneloader.h"

#include "sampler.h"
#include "sampler/randomsampler.h"

#include "util/interpolation.h"
#include "test/testinterpolation.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


    
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    const PluginManager* getPluginManager() const { return pluginmanager; }
    Ui::MainWindow *ui;
    FrameBuffer* fb;

    virtual bool eventFilter(QObject *, QEvent *);

private slots:

    void on_renderBtn_clicked();


    void on_actionPlugins_2_triggered();

    void on_actionOpen_triggered();

    void on_actionXmlTest_triggered();

    void on_actionSphereFromXmlTest_triggered();

    void on_loadSceneBtn_clicked();

    void on_actionTest1_triggered();

    void on_actionRun_all_tests_triggered();

    void on_actionSet_triggered();

    void on_actionReset_triggered();

    void on_actionSampler_triggered();

    void on_actionCamera_triggered();

    void on_actionScene_Listing_triggered();

private:
    void loadPlugins();
    void loadScene();
    void loadShaders(QXmlQuery&);
    void paintRegion();

    renderer_update_callback renderer_callback;

    Scene* scene;
    PluginManager* pluginmanager;
    Etfrenderer* etfrenderer;

    QPoint region_start;
    QSize  region_size;

    bool region_resize;
};

static MainWindow* mainWindow;

#endif // MAINWINDOW_H

