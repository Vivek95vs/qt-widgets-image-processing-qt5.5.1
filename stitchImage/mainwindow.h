#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsPixmapItem"
#include "qgraphicsscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QImage myImage;
    unsigned char* arr1;
    unsigned char* arr2;
    unsigned char* arr3;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *item;
//    QGraphicsPixmapItem *p1=NULL;


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
