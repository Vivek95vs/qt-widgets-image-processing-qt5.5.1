#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsView"
#include "QGraphicsItem"
#include "QGraphicsScene"
#include "disp_evt.h"
#include "qcustomplot.h"

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
    unsigned char *intensity;
    unsigned char *RowPix;
//    unsigned char *x;
    QGraphicsPixmapItem *item;
    void plotgraph(QCustomPlot *customPlot);

private slots:
    void on_Load_Image_clicked();

    void on_Select_ROI_clicked();

    void on_Pix_Cal_clicked();

    void on_Graph_plot_clicked();

    void on_smoothening_clicked();

    void on_Invert_clicked();


    void on_Row_clicked();

    void on_pix_clicked();

private:
    Ui::MainWindow *ui;
    QImage myImage;
    QImage image;
    QImage q_image2;
    uchar* imgOut1;
    int row;
    int col;
//    QGraphicsScene *scene;
    QGraphicsView *view;
    unsigned short *img=NULL;
    unsigned short *smooth=NULL;
    Disp_Evt *Evt;
};

#endif // MAINWINDOW_H
