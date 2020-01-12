#ifndef PLUGINSWINDOW_H
#define PLUGINSWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

#include <QDebug>

#include "mainwindow.h"
#include "plugin/rendererplugin.h"
#include "pluginmanager.h"

namespace Ui {
    class PluginsWindow;
}

class PluginsWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PluginsWindow(QWidget *parent = 0);
    ~PluginsWindow();
private:
    void list(const PluginManager*);
    void addRow(QList<QString>&, int);

    Ui::PluginsWindow *ui;
};

#endif // PLUGINSWINDOW_H
