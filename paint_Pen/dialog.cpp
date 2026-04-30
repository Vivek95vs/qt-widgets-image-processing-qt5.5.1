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

void Dialog:: paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen pointpen(Qt::blue);
    pointpen.setWidth(15);

    QPen linepen(Qt::gray);
    linepen.setWidth(20);

    QPoint p1;
    p1.setX(1);
    p1.setY(25);

    QPoint p2;
    p2.setX(100);
    p2.setY(200);

    painter.setPen(linepen);
    painter.drawLine(p1,p2);
    painter.setPen(pointpen);
    painter.drawPoint(p1);
    painter.drawPoint(p2);
}
