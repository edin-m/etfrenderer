#include "pluginswindow.h"
#include "ui_pluginswindow.h"

PluginsWindow::PluginsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PluginsWindow)
{
    ui->setupUi(this);

    MainWindow* mw = qobject_cast<MainWindow*>(parent);
    this->list(mw->getPluginManager());
}

PluginsWindow::~PluginsWindow()
{
    delete ui;
}

void PluginsWindow::list(const PluginManager* pm)
{
    const QList<RendererPlugin*>& renderers = pm->getRenderers();
    const QList<ShapePlugin*>& shapes = pm->getShapePlugins();
    const QList<ShaderPlugin*>& shaders = pm->getShaders();
    const QList<LightPlugin*>& lights = pm->getLightPlugins();

    int rowcount =  renderers.count() +
                    shapes.count() +
                    shaders.count() +
                    lights.count()
            ;

    ui->pluginsTable->setRowCount(rowcount);
    ui->pluginsTable->setColumnCount(4);

    QList<QString> row;
    int rowid = 0;
    foreach(RendererPlugin* renderer, renderers)
    {
        row.append("Renderer");
        row.append(renderer->name());
        row.append(renderer->author());
        row.append(renderer->version());

        addRow(row, rowid++);
        row.clear();
    }

    foreach(ShapePlugin* shape, shapes)
    {
        row.append("Shape");
        row.append(shape->name());
        row.append(shape->author());
        row.append(shape->version());

        addRow(row, rowid++);
        row.clear();
    }

    foreach(ShaderPlugin* shader, shaders)
    {
        row.append("Shader");
        row.append(shader->name());
        row.append(shader->author());
        row.append(shader->version());

        addRow(row, rowid++);
        row.clear();
    }

    foreach(LightPlugin* plugin, lights)
    {
        row.append("Lights");
        row.append(plugin->name());
        row.append(plugin->author());
        row.append(plugin->version());

        addRow(row, rowid++);
        row.clear();
    }
}

void PluginsWindow::addRow(QList<QString>& data, int row)
{
    QList<QTableWidgetItem*> tableItems;

    foreach(QString str, data)
    {
        QTableWidgetItem* item = new QTableWidgetItem(str);
        item->setFlags(Qt::ItemIsSelectable);
        tableItems.append(item);
    }

    int column = 0;
    foreach(QTableWidgetItem* item, tableItems)
    {
        ui->pluginsTable->setItem(row, column++, item);
    }
}
