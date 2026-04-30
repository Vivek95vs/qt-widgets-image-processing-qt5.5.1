#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QImage>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    bool pressed;
    QImage myImage;
    QImage myImage1;
    const int w=3072,h=3072;

//    Operation *opt;
    unsigned char* arr=new unsigned char[w*h];
    unsigned char* arr1=new unsigned char[w*h];
    unsigned char* arr2=new unsigned char[w*h];
    unsigned char* arr3=new unsigned char[w*h];
    bool Pressed;

private slots:

    void on_PB_LoadImage1_clicked();

    void on_PB_LoadImage2_clicked();

    void on_PB_Overlay_clicked();

    void on_PB_Quad_clicked();

    void on_PB_CheckerBoard_clicked();

    void on_PB_Toggle_clicked();

    void on_pushButton_toggled(bool checked);

    void on_PB_Togglecheck_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsPixmapItem *item1,*item2,*item3;
    QGraphicsScene *scene;
    QGraphicsView *view1,*view2,*view3;
    QGraphicsPixmapItem *p1=NULL;
    QGraphicsPixmapItem *p2=NULL;
};

#endif // DIALOG_H
