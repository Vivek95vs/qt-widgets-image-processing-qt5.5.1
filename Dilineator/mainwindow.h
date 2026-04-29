#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>

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
    QImage myImage1;
    const int w=3072,h=3072;

//    Operation *opt;
    unsigned char* arr=new unsigned char[w*h];
    unsigned char* arr1=new unsigned char[w*h];
    unsigned char* arr2=new unsigned char[w*h];
    unsigned char* arr3=new unsigned char[w*h];
    bool Pressed;

//    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsItem *item;
    QGraphicsPixmapItem *p1=NULL;
    QGraphicsPixmapItem *p2=NULL;

    ~MainWindow();

private slots:
    void on_PB_Load1_clicked();

    void on_PB_load2_clicked();

    void on_PB_overlay_clicked();

    void on_PB_Quadrant_clicked();

    void on_PB_checker_clicked();

    void on_PB_toggle_clicked();

    void on_PB_Rectangle_clicked();

    void on_PB_clearall_clicked();

    void on_PB_Rect_clicked();

private:
    Ui::MainWindow *ui;
    customscene *scene;
};

#endif // MAINWINDOW_H
