#include "square.h"

square::square()
{
    pressed=false;
    setFlag(ItemIsMovable);
}

QRectF square::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec=boundingRect();
    QBrush brush(Qt::blue);
    if(pressed)
    {
        brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::green);
    }
    painter->fillRect(rec,brush);
    painter->drawRect(rec);
    painter->drawEllipse(rec);
}

void square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed=true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void square::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed=false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

