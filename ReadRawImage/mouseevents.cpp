#include "mouseoperation.h"

MouseOperation::MouseOperation()
{

}

void MouseEvents::mousePressEvent(QMouseEvent *event)
{
    firstPos = event->pos();
}

void MouseEvents::mouseMoveEvent(QMoveEvent *event)
{
    if (event->type() == QEvent::MouseMove)
        lastPos = event->pos();
}

//void MouseEvents::mouseReleseEvent(QMouseEvent *event)
//{
//    mousePressed = false;
//}




