#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsView"
#include "QGraphicsItem"
#include "QGraphicsScene"

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
    unsigned char* dispImg2;
    unsigned short *radbuf;
    unsigned char *intensity;
    unsigned char *RowPix;
//    unsigned char *x;
    QGraphicsPixmapItem *item;

private slots:
    void on_LoadRaw_clicked();

    void on_Inverting_clicked();

    void on_PixCal_clicked();

    void on_Rowpixel_clicked();

    void on_Smothening_clicked();

    void on_Folder_clicked();

    void on_Smooth_disp_clicked();

    void on_Load_clicked();

    void on_Dicom_raw_clicked();

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
    unsigned short *Invert=NULL;
    QGraphicsScene *Scene;

};

#endif // MAINWINDOW_H
