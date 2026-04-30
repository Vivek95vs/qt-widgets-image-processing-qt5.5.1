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

void Dialog::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    //Make a Polygon
    QPolygon poly;
    poly<<QPoint(50,50);
    poly<<QPoint(50,200);
    poly<<QPoint(200,50);
    poly<<QPoint(200,200);

    //Make a pen
    QPen linepen;
    linepen.setWidth(8);
    linepen.setColor(Qt::darkCyan);
//    linepen.setJoinStyle(Qt::RoundJoin);
//    linepen.setJoinStyle(Qt::MiterJoin);
//    linepen.setStyle(Qt::DotLine);
    painter.setPen(linepen);

    //Make a Brush
    QBrush fillbrush;
    fillbrush.setColor(Qt::darkGreen);
    fillbrush.setStyle(Qt::CrossPattern);

    //Fill the polygon
    QPainterPath path;
    path.addPolygon(poly);
    painter.fillPath(path,fillbrush);

    //Draw a Polygon
    painter.drawPolygon(poly);
}
