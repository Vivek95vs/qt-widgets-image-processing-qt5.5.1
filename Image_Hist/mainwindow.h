#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    const int w=3072,h=3072;
    const int ImageSize=3072;
    int numPixIntile;
    int dimTile[2];
    QImage myImage;
    unsigned short* tile;
    int nbins=65536;
    int rowS=3072;
    int colS=3072;
    float* aLut;
    int* Histogram;
    float mapping1;
    int* histSum;
    int imgCol,imgRow;
    float * gauss_Data;
    ~MainWindow();

private slots:
    void on_PB_Load_clicked();

private:
    Ui::MainWindow *ui;
     QGraphicsItem *item;
     QGraphicsScene *scene;
     QGraphicsView *view;
};

#endif // MAINWINDOW_H
