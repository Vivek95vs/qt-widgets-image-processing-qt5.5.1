#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QGraphicsItem"
#include "imageenhancementnew.h"
//#include <itkImage.h>
//#include <itkImageFileReader.h>
//#include <itkGDCMImageIO.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    unsigned short *radbuf;
    int ImgWidth=3072;
    int ImgHeight=3072;
    int width ;
    int height;

private slots:
    void on_PB_Load_clicked();

private:
    Ui::MainWindow *ui;
    unsigned char *dispImg=NULL;
    unsigned short *img=NULL;
    ImageEnhancementNew *enhance;
    QImage myImage;
    QGraphicsScene *Scene;
    QGraphicsItem *item;
    QGraphicsView *view;
};

#endif // MAINWINDOW_H
