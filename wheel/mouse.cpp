#include "mouse.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

mouse::mouse()
{

}

void mouse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {
        qDebug()<<"mouse press point"<<event->scenePos();
        startingpoint = event->scenePos();

    }
     QGraphicsScene::mousePressEvent(event);

}

void mouse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"in mouse move - outside if";


    if(event->buttons() == Qt::RightButton)
    {
        qDebug()<<"mouse dragging happening";
//            startingpoint= event->scenePos();


            deltaX  = event->scenePos().x() - startingpoint.x();
            deltaY  = event->scenePos().y() - startingpoint.y();



            qDebug()<<"delta values"<<deltaX<<deltaY;
//            brg=(deltaY/3072)*100;
//            qDebug()<<"mouse brg"<<brg;
//            qDebug()<<"points"<<startingpoint.x()<< startingpoint.y();
            qDebug()<<"ending"<<event->scenePos().x()<<event->scenePos().y();
//            qDebug()<<"delta values"<<deltaX<<deltaY;
            angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.141;
//            qDebug()<<"angleInDegrees "<<angleInDegrees ;




//            if(angleInDegrees >=45)
//            {
//                if(angleInDegrees<=135)
//                {
//                    vartical = true;
//                    qDebug()<<"vretical value1"<<vartical<<"horizantal value1"<<horizantal;
//                }
//                else
//                {
//                   vartical=false;
//                }

//            }

//            if(angleInDegrees>=0)
//            {
//                if(angleInDegrees<=44)
//                {
//                    horizantal= true;

//                    qDebug()<<"horizantal value1"<<horizantal<<"vretical value1"<<vartical;
//                }
//                else
//                 {
//                    horizantal=false;
//                 }
//            }
//            if(angleInDegrees >=136)
//            {
//                if(angleInDegrees <=180)
//                {
//                    horizantal= true;
//                    qDebug()<<"horizantal value2"<<horizantal<<"vretical value2"<<vartical;
//                }
//                else
//                 {
//                    horizantal=false;
//                 }

//            }





            if(angleInDegrees>=-179)
            {
                if(angleInDegrees<=-136)
                {
                    horizantal = true;
                    widh = (deltaX/3072.0)*4;
                    qDebug()<<"contrast - hr"<<widh;
                    qDebug()<<"horizantal value3"<<horizantal<<"vretical value2"<<vartical;
                }
                else
                 {
                    horizantal=false;
                 }
           }
            if(angleInDegrees>=-135)
            {
                if(angleInDegrees<=-45)
                {
                    vartical = true;
                    heigh = (deltaY/3072.0)*100;
                    qDebug()<<"brightness - hr"<<heigh;
                    qDebug()<<"vretical value2"<<vartical<<"horizantal value1"<<horizantal;
                }

                else
                 {
                    vartical=false;
                 }
            }
            if(angleInDegrees >=-44)
            {
                if(angleInDegrees<0)
                {
                    horizantal = true;
                    widh = (deltaX/3072.0)*4;
                    qDebug()<<"contrast - hr"<<widh;;

                    qDebug()<<"horizantal value4"<<horizantal<<"vretical value4"<<vartical;
                }
                else
                 {
                    horizantal=false;
                 }
            }


            heigh = heigh +  deltaY;
            widh = widh +  deltaX;



            emit buttonclick();


    }
    QGraphicsScene::mouseMoveEvent(event);

}

void mouse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

}

void mouse::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

     if(event->buttons() == Qt::RightButton)
     {
        qDebug()<<"double click";
        emit doubleclick();
     }



    QGraphicsScene::mouseDoubleClickEvent(event);

}
