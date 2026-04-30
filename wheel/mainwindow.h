#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtWidgets>
#include <QWidget>
#include "mouse.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
//    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent = nullptr);
    unsigned short* buf=NULL;
    unsigned char* str=NULL;
    QImage Img;
    QPixmap Pix;
    QGraphicsPixmapItem *itm=NULL;
    unsigned short* buf1=NULL;
    unsigned char* str1=NULL;
    QImage Img1;
    QPixmap Pix1;
    QGraphicsPixmapItem *itm1=NULL;
    QGraphicsScene *sene;
    mouse *sne;
    int val;
    int wid;
    int cur;
//    int brg=NULL;
//    int con =1;
    QGraphicsPixmapItem *itm2=NULL;
    QPixmap Pix2;
    QGraphicsPixmapItem *itm3=NULL;
    QPixmap Pix3;
    int hei;
//    float heigh;
//    float widh;

    ~MainWindow();

protected:
     void wheelEvent(QWheelEvent *event);





private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void onRightClicked();
    void onDoubleClicked();




private:

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
