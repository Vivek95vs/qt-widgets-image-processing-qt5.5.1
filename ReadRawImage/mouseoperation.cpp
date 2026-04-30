#include "mouseoperation.h"

MouseOperation::MouseOperation()
{
//    qDebug()<<"Mouse Event";
}

void MouseOperation::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    qDebug()<<"MousePress";
    mouseRelesed = false;
    firstPoint = ev->scenePos();
//    firstPoint = ev->lastPos();
    qDebug()<<"firstPosint "<<firstPoint;
}

//void MouseOperation::mouseMoveEvent(QGraphicsSceneMouseEvent *ev)
//{
//    if(mouseRelesed == false)
//        firstPosint = ev->pos();
//    qDebug()<<"firstPosint "<<firstPosint;
//}

void MouseOperation::mouseReleseEvent(QGraphicsSceneMouseEvent *ev)
{
    lastPoint = ev->scenePos();
//    lastPoint = ev->lastPos();
    mouseRelesed = true;
    qDebug()<<"lastPoint "<<lastPoint;
    QPen pen(Qt::blue);
}
