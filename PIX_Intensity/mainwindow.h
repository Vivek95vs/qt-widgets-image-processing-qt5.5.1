#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsView"
#include "QGraphicsItem"
#include "QGraphicsScene"
#include "disp_evt.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int width;
    int height;
    unsigned char *dispImg;
    unsigned short *radbuf;
    QGraphicsPixmapItem *item;

public slots:
//    void mouse_call(int event,int x,int y,int,void*);

private slots:
    void on_pushButton_clicked();

    void on_Area_select_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QImage myImage;
//    QGraphicsScene *scene;
    QGraphicsView *view;
    unsigned short *img=NULL;
    Disp_Evt *Evt;
    unsigned char *intensity;
    unsigned short* rawImage;
    unsigned char* charImage;
    unsigned int imageSize[2];
};

#endif // MAINWINDOW_H
