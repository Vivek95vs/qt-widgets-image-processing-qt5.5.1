#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>
#include <QFileDialog>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    const int w=1536,h=1536;
    QImage myImage;
    unsigned char* arr=new unsigned char[w*h];

private slots:
    void on_Load_image_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsPixmapItem *item;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *p1=NULL;

};

#endif // MAINWINDOW_H
