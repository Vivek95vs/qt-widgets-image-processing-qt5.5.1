#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customscene.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QImage myImage;
    const int w=3072,h=3072;
    unsigned char* arr=new unsigned char[w*h];
    bool Pressed;
    QGraphicsView *view;
    QGraphicsItem *item;
    QGraphicsPixmapItem *p1=NULL;
    QGraphicsPixmapItem *p2=NULL;
    ~MainWindow();

private slots:
    void on_PB_Rect_clicked();

    void on_PB__Load_Image_clicked();

private:
    Ui::MainWindow *ui;
    customscene *scene;
};

#endif // MAINWINDOW_H
