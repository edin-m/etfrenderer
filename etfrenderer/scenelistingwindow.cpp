#include "scenelistingwindow.h"
#include "ui_scenelistingwindow.h"

SceneListingWindow::SceneListingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneListingWindow)
{
    ui->setupUi(this);
}

SceneListingWindow::~SceneListingWindow()
{
    delete ui;
}
