#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

//    QLinearGradient grad1(30,60,90,180);
//    grad1.setColorAt(0.0,Qt::darkBlue);
//    grad1.setColorAt(0.25,Qt::darkCyan);
//    grad1.setColorAt(0.5,Qt::darkGreen);
//    grad1.setColorAt(0.75,Qt::darkRed);
//    grad1.setColorAt(1.0,Qt::darkYellow);

//    QRect rec(25,25,200,200);
//    painter.fillRect(rec,grad1);

    QRadialGradient grad2(QPoint(100,100),100);
    grad2.setColorAt(0.0,Qt::darkBlue);
    grad2.setColorAt(0.25,Qt::darkCyan);
    grad2.setColorAt(0.5,Qt::darkGreen);
    grad2.setColorAt(0.75,Qt::darkRed);
    grad2.setColorAt(1.0,Qt::darkYellow);

    QRect rec(10,10,200,200);
    painter.fillRect(rec,grad2);

//    QConicalGradient grad3(QPoint(100,100),75);
//    grad3.setColorAt(0.0,Qt::darkBlue);
//    grad3.setColorAt(0.25,Qt::darkCyan);
//    grad3.setColorAt(0.5,Qt::darkGreen);
//    grad3.setColorAt(0.75,Qt::darkRed);
//    grad3.setColorAt(1.0,Qt::darkYellow);

//    QRect rec(10,10,200,200);
//    painter.fillRect(rec,grad3);
}
