#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsView>

#include "myitem.h"
#include "customscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QImage myImage;
//    const int w=3072,h=3072;
    QGraphicsView *view;
    QGraphicsItem *item;
    const size_t  radSize=3072;
    float rTheta=0,dTheta=0;
    float imaginPixelSpacing=0.1;
    double detectorxShift=5;
    double detectoryShift=4;
    double imagerXCurrentPosition=2;
    double imagerYCurrentPosition=4;
    double kVxShift=0;
    double kVyShift=0;
    float isoCentreX,isoCentreY;
    double rx1,ry1,rx2,ry2,cx1;
    double Rx1,Ry1,Rx2,Ry2,Cx1;

    QRectF *JawRect;
    double colliThetaCurrentPosition=360;
    double jawX1CurrentPosition=-50;
    double jawX2CurrentPosition=80;

    double jawY1CurrentPosition=-80;
    double jawY2CurrentPosition=50;

    double wireX1CurrentPosition=-50.5;
    double wireX2CurrentPosition=80.5;

    double wireY1CurrentPosition=-80.5;
    double wireY2CurrentPosition=50.5;

    float imgSizeBoundary;
    double rotatorStep=0;

    customitem* rectDefault1;
    customitem* rectDefault2;
    QGraphicsRectItem* centerDefault1;
    QGraphicsRectItem *isocenterRect;
    int n=0;
    int q=-1;
    int p;
    int ToggleScale;
    myitem *itemRuler;
    int dMode=0;
    int mode = 0;


//    float cTheta;
    ~MainWindow();


private slots:
    void on_PB_Load_Image_clicked();

    void on_PB_Clockwise_Rotate_clicked();

    void on_PB_Anticlockwise_Rotate_clicked();

//    void on_PB_Draw_Anlgle_clicked();

    void on_PB_Ruler_Horizontal_clicked();

    void on_PB_Vertical_Ruler_clicked();

    void on_PB_Drawline_clicked();
    
private:
    Ui::MainWindow *ui;
    customscene *scene;
    void cropExposureRegion(unsigned short *img, float theta, float isoX, float isoY, float mPixSpacing, size_t imgSize);
    void updateDilineatorInfo(size_t imgSize);
};

#endif // MAINWINDOW_H
