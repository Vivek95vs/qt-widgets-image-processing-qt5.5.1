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
//        qDebug()<<"angle of  line---->"<<angle_f<<"scenepositon"<<event->scenePos();
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
//            qDebug()<<"horizontal_done";
    }
    if (move_vertical == false)
    {
//        qDebug()<<"1st entering.....";
//        QPointF temp = (event->scenePos() - mousepress_pos);
        if (event->scenePos().x() - mousepress_pos.x() > 0)
        {
            b = ((event->scenePos().x() - mousepress_pos.x()));
            WC = b*5;
//            temp_bright = brightness.x();

            if (WC > 1000)
            {
//                temp_bright = 100;
                WC = 1000;
            }
//                qDebug()<<"WCfun"<<event->scenePos().x()<<mousepress_pos.x()<<event->scenePos().x() - mousepress_pos.x()<<WC;
        }
        if((event->scenePos().x()- mousepress_pos.x())<0)
        {
//            qDebug()<<"second condition----->";
            c = (mousepress_pos.x() - event->scenePos().x());
            WC= (b-c)*5;

            if (WC <-1000)
            {
                WC = -1000;
//                brightness = QPointF(temp_bright,brightness.y());
                //                QCursor::setPos(temp_bright,brightness.y());
            }
            if (WC >0)
            {
                //                brightness.x() = temp_bright;
//                brightness = QPointF(brightness.x(),brightness.y());
                WC=WC;
            }

//                qDebug()<<"WCfun---"<<event->scenePos().x()<<mousepress_pos.x()<<event->scenePos().x() - mousepress_pos.x()<<WW;
        }
    }
    if (move_vertical==true)
    {
        if ((event->scenePos().y() - mousepress_pos.y()) > 0)
        {
            b1 = (event->scenePos().y() - mousepress_pos.y());
            WW = b1*5;
//                qDebug()<<"ccccc--->"<<b1<<"WW---->"<<WW;

            if (WW > 2000)
            {
                WW = 2000;
            }

//                qDebug()<<"WWfun"<<event->scenePos().y()<<mousepress_pos.y()<<event->scenePos().y() - mousepress_pos.y()<<WW;
        }

        if((event->scenePos().y()- mousepress_pos.y())<0)
        {
            c1 = (mousepress_pos.y() - event->scenePos().y());
            WW = b1-c1;
//                 qDebug()<<"ccccc11--->"<<b1<<"WW---->"<<WW;
            if (WW<0)
            {
                WW = 0;
            }
            if (WW>0)
            {
                WW = WW;
            }
//                qDebug()<<"WWfun---"<<event->scenePos().y()<<mousepress_pos.y()<<event->scenePos().y() - mousepress_pos.y()<<WW;

//                qDebug()<<"ccccc-contrast---->"<<WW;
        }
    }

    emit rightbuttonclicked();

//        qDebug()<<"move--->"<<"WW.."<<WW<<endl<<"WC.."<<WC;

        QGraphicsScene::mouseMoveEvent(event);
}


void sceneclass::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    b = QPointF(0,0);
//    c = QPointF(0,0);
    WC = WC;
    WW = WW;
    mouserelease_pos = event->scenePos();
    qDebug()<<"release--->"<<"contrast.."<<contrast<<endl<<"brightness.."<<brightness;
    QGraphicsScene::mouseReleaseEvent(event);
}
