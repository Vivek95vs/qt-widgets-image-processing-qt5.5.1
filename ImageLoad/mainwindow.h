#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"graphicsscene.h"
#include <QFileDialog>
#include <QDebug>
#include <stdio.h>
#include <string.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QCheckBox>
#include <QGraphicsEllipseItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    unsigned short* buf=NULL;
    unsigned char* str=NULL;
    QImage Img;
    QPixmap Pix;
    QGraphicsPixmapItem *itm=NULL;

    QList <QGraphicsItem*> Graphicitemlist;
    QGraphicsScene *sene;
    GraphicsScene * scene;

    ~MainWindow();
private slots:
    void on_loadPushButton_clicked();

    void on_clearPushButton_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void Updatemeasuredrawn(QGraphicsItem *measureitem);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *square;
//    QGraphicsLineItem* itemToDraw;
//    QGraphicsEllipseItem *itemellipse;
//    QGraphicsRectItem *itemrect;
};
#endif // MAINWINDOW_H
