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
//        qDebug()<<"horizontal_done";
    }
    if (move_vertical == false)
    {
//        qDebug()<<"1st entering.....";
        QPointF temp = (event->scenePos() - mousepress_pos);
        if (temp.x() > 0)
        {
            b = (event->scenePos() - mousepress_pos)/30;
            brightness = b;
            temp_bright = brightness.x();
//            qDebug()<<"b--->"<<b<<endl<<"brightness"<<brightness<<"temp_bright"<<temp_bright;

            if (brightness.x() > 100)
            {
                temp_bright = 100;
                brightness = QPointF(temp_bright,brightness.y());
//                qDebug()<<"coming-----"<<temp_bright<<brightness;
                //                QCursor::setPos(temp_bright,numbers_y[3073]);
            }
        }
        //        if ((event->scenePos().x()-mousepress_pos.x())>100)
        //        {
        //            b = 100;
        //            brightness = b+brightness;
        //            if (brightness > 100)
        //            {
        //                brightness =100;
        //            }
        //        }
        if(temp.x() < 0)
        {
//            qDebug()<<"second condition----->";
            c = (mousepress_pos - event->scenePos())/30;
            brightness= b-c;

            if (brightness.x()<0)
            {
                temp_bright = 0;
                brightness = QPointF(temp_bright,brightness.y());
                //                QCursor::setPos(temp_bright,brightness.y());
            }
            if (brightness.x()>0)
            {
                //                brightness.x() = temp_bright;
                brightness = QPointF(brightness.x(),brightness.y());
            }
        }
    }
    if (move_vertical==true)
    {
        if ((event->scenePos().y() - mousepress_pos.y()) > 0)
        {
            b1 = ((event->scenePos().y() - mousepress_pos.y())/3072)*20;
            contrast = b1;
//            qDebug()<<"ccccc--->"<<b<<endl<<"contrast---->"<<contrast;

            if (contrast > 100)
            {
                contrast = 100;
            }
        }

        if((event->scenePos().y()- mousepress_pos.y())<0)
        {
            c1 = (mousepress_pos.y() - event->scenePos().y())/100;
            contrast = b1-c1;

            if (contrast<0)
            {
                contrast = 0;
            }
            if (contrast>0)
            {
                contrast = contrast;
            }
        }
    }
    qDebug()<<"move--->"<<"contrast.."<<contrast<<endl<<"brightness.."<<brightness.x();

    emit rightbuttonclicked();

    QGraphicsScene::mouseMoveEvent(event);
}

void sceneclass::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    b = QPointF(0,0);
    c = QPointF(0,0);
    brightness = brightness;
    contrast = contrast;
    mouserelease_pos = event->scenePos();
//    qDebug()<<"mouse_release--"<<brightness<<contrast/*<<"release_point"<<event->scenePos()<<"angle---->"<<angle_f*/;
    qDebug()<<"release--->"<<"contrast.."<<contrast<<endl<<"brightness.."<<brightness.x();
    QGraphicsScene::mouseReleaseEvent(event);
}
