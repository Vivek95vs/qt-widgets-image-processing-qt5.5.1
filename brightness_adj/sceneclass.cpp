#include "sceneclass.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QCursor>

sceneclass::sceneclass()
{

}

void sceneclass::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button()== Qt::RightButton){
        mousepress_pos = event->scenePos();
        //        qDebug()<<"pressed---->"<<mousepress_pos<<1072/30<<"orig"<<orig<<endl<<mousepress_pos<<"divide"<<mousepress_pos/30;
    }
    QGraphicsScene::mousePressEvent(event);
}

void sceneclass::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    currentmouse_pos = event->scenePos();
    angle = atan2(mousepress_pos.y() - currentmouse_pos.y(), mousepress_pos.x() - currentmouse_pos.x());
    angle_f = (angle*180)/3.14;
    qDebug()<<"angle of  line---->"<<angle_f<<"scenepositon"<<event->scenePos();
    bool move_vertical = false;

    if (45<angle_f)
    {
//        move_vertical = true;
//        qDebug()<<"vertical_done"<<angle_f;
        if (angle_f<135)
        {
            move_vertical = true;
//            qDebug()<<"vertical_done"<<angle_f;
        }
    }
    else if (angle_f<-45)
    {
//        move_vertical = true;
//        qDebug()<<"vertical_done"<<angle_f;
        if (angle_f>-135)
        {
            move_vertical = true;
//            qDebug()<<"vertical_done"<<angle_f;
        }
    }

    else
    {
        move_vertical = false;
        qDebug()<<"horizontal_done";
    }
    if (move_vertical == false)
    {
//        qDebug()<<"1st entering.....";
//        QPointF temp = (event->scenePos() - mousepress_pos);
        if (event->scenePos().x() - mousepress_pos.x() > 0)
        {
            b = ((event->scenePos().x() - mousepress_pos.x())/3072)*20;
            brightness = b;
//            temp_bright = brightness.x();

            if (brightness > 30)
            {
//                temp_bright = 100;
                brightness = 30;
            }
        }
        if((event->scenePos().x()- mousepress_pos.x())<0)
        {
//            qDebug()<<"second condition----->";
            c = (mousepress_pos.x() - event->scenePos().x())/30;
            brightness= b-c;

            if (brightness <0)
            {
                brightness = 0;
//                brightness = QPointF(temp_bright,brightness.y());
                //                QCursor::setPos(temp_bright,brightness.y());
            }
            if (brightness >0)
            {
                //                brightness.x() = temp_bright;
//                brightness = QPointF(brightness.x(),brightness.y());
                brightness=brightness;
            }
        }
    }
    if (move_vertical==true)
    {
        if ((event->scenePos().y() - mousepress_pos.y()) > 0)
        {
            b1 = ((event->scenePos().y() - mousepress_pos.y())/3072)*20;
            contrast = b1;
            qDebug()<<"ccccc--->"<<b1<<"contrast---->"<<contrast;

            if (contrast > 30)
            {
                contrast = 30;
            }
        }

        if((event->scenePos().y()- mousepress_pos.y())<0)
        {
            c1 = (mousepress_pos.y() - event->scenePos().y())/30;
            contrast = b1-c1;
             qDebug()<<"ccccc11--->"<<b1<<"contrast---->"<<contrast;
            if (contrast<0)
            {
                contrast = 0;
            }
            if (contrast>0)
            {
                contrast = contrast;
            }

            qDebug()<<"ccccc-contrast---->"<<contrast;
        }
    }
    qDebug()<<"move--->"<<"contrast.."<<contrast<<endl<<"brightness.."<<brightness;

    emit rightbuttonclicked();

        QGraphicsScene::mouseMoveEvent(event);
}


void sceneclass::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    b = QPointF(0,0);
//    c = QPointF(0,0);
    brightness = brightness;
    contrast = contrast;
    mouserelease_pos = event->scenePos();
    qDebug()<<"release--->"<<"contrast.."<<contrast<<endl<<"brightness.."<<brightness;
    QGraphicsScene::mouseReleaseEvent(event);
}
