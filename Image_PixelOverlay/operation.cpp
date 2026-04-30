#include "operation.h"
#include "dialog.h"

Operation::Operation(QObject *parent):QGraphicsScene(parent)
{

}

Operation::~Operation()
{

}
QRectF Operation::boundingRect() const
{
    return QRectF(0,0,3072,3072);
}


void Operation::paintEvent(QPaintEvent *)
{
    QPainter painter;

    QPixmap px1=QPixmap::fromImage(myImage);
    QPixmap px2=QPixmap::fromImage(myImage1);

    painter.begin(&px2);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(rect,Qt::transparent);
    painter.end;

    painter.begin(px1);
    painter.setCompositionMode(QPainter::CompositionMode_Overlay);
    painter.drawImage(0,0,px2);
    painter.end;

}
