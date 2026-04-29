#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QWidget>
#include <QtWidgets>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "enhanceimage.h"
#include "sceneclass.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QImage q_image;
    int Rows;
    int Cols;
    int w=3072;
    int h=3072;
    unsigned char *dispImg;
    sceneclass *mousescene;
    ~MainWindow();


private slots:
    void on_Load_Image_clicked();

    void on_Brightness_clicked();

    void on_Contrast_clicked();

    void on_Window_width_clicked();

    void on_Window_center_clicked();


    void getbrightness();
    void on_brightness_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    cv::Mat imgMat;
    QGraphicsView *view;
    QGraphicsItem *item;
    QGraphicsPixmapItem *item1;
};

#endif // MAINWINDOW_H
