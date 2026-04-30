#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "sceneclass.h"
#include <QAbstractButton>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    sceneclass *s1;
    ~MainWindow();

private slots:
    void getbrightness();

    void getcontrast();

    void on_Load_PB_clicked();

private:
    Ui::MainWindow *ui;
    int w = 3072;
    int h = 3072;
    int numbers_x[3073];
    int numbers_y[3073];
    unsigned char *opdata;
    cv::Mat imgMat;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item ;
    int t = 0;

};

#endif // MAINWINDOW_H
