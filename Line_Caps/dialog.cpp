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
    QPen pen(Qt::darkRed);
    pen.setWidth(10);

    QPoint startpoint(20,50);
    QPoint endpoint(200,50);

    pen.setCapStyle(Qt::FlatCap);
    painter.setPen(pen);
    painter.drawLine(startpoint,endpoint);

    startpoint.setY(100);
    endpoint.setY(100);
    pen.setCapStyle(Qt::SquareCap);
    painter.setPen(pen);
    painter.drawLine(startpoint,endpoint);

    startpoint.setY(150);
    endpoint.setY(150);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.drawLine(startpoint,endpoint);
}
