#ifndef SCENELISTINGWINDOW_H
#define SCENELISTINGWINDOW_H

#include <QDialog>

namespace Ui {
class SceneListingWindow;
}

class SceneListingWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit SceneListingWindow(QWidget *parent = 0);
    ~SceneListingWindow();
    
private:
    Ui::SceneListingWindow *ui;
};

#endif // SCENELISTINGWINDOW_H
