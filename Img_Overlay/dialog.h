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

    QImage myImage;
    QImage myImage1;
    const int w=3072,h=3072;
    unsigned char* arr=new unsigned char[w*h];
    unsigned char* arr1=new unsigned char[w*h];
    unsigned char* arr2=new unsigned char[w*h];

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsPixmapItem *item1,*item2,*item3;
    QGraphicsScene *scene,*scene1,*scene2;
    QGraphicsView *view,*view1,*view2;
    QGraphicsPixmapItem *p1=NULL;
    QGraphicsPixmapItem *p2=NULL;

};

#endif // DIALOG_H
