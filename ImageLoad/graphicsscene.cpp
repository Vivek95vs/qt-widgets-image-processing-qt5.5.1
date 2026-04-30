#include "graphicsscene.h"
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QtDebug>

GraphicsScene::GraphicsScene()
{

}

void GraphicsScene::temp(Mode m2)
{
    m1=m2;
}

void GraphicsScene::clr()
{
//    qDebug()<<"Entering clear"<<list.length()<<list1.length()<<list2.length();
////    list.clear();
////    list1.clear();
////    list2.clear();
//    for(i=0;i<list.length();i++)
//    {

//    }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//   addLine(event->scenePos().x(),
//    event->scenePos().y(),
//    event->scenePos().x(),
//    event->scenePos().y(),
//    QPen(Qt::red,10,Qt::SolidLine));

//     previousPoint = event->scenePos();
     QGraphicsScene::mousePressEvent(event);
//     qDebug()<<"mouse press point"<<previousPoint;
}
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    addLine(previousPoint.x(),previousPoint.y(),
//            event->scenePos().x(),
//            event->scenePos().y(),
//             QPen(Qt::red,10,Qt::SolidLine));
//     previousPoint = event->scenePos();

    qDebug()<<"Entering";

    switch (m1) {
    case Line:

        if(!itemToDraw)
        {
            itemToDraw = new QGraphicsLineItem();
            previousPoint = event->scenePos();
            itemToDraw->setPos(previousPoint);
            itemToDraw->setPen(QPen(Qt::red,3,Qt::SolidLine));

            qDebug()<<"entering to switch";
            this->addItem(itemToDraw);

        }


        itemToDraw->setLine(0,0,
                            event->scenePos().x() - previousPoint.x(),
                            event->scenePos().y() - previousPoint.y());

        break;
//        itemToDraw->setFlag(QGraphicsItem::ItemIsSelectable,true);

    case Ellipse:
        if(!itemellipse)
        {
            itemellipse = new QGraphicsEllipseItem();
            previousPoint = event->scenePos();
            itemellipse->setPos(previousPoint);
            itemellipse->setPen(QPen(Qt::green,3,Qt::SolidLine));
            this->addItem(itemellipse);
        }
        itemellipse->setRect(0,0,
                             event->scenePos().x()-previousPoint.x(),
                             event->scenePos().y()-previousPoint.y());
        break;
    case Rectangle:

        if(!itemrect)
        {
            itemrect= new QGraphicsRectItem();
            previousPoint = event->scenePos();
            itemrect->setPos(previousPoint);
            itemrect->setPen(QPen(Qt::blue,3,Qt::SolidLine));

            this->addItem(itemrect);
        }
        itemrect->setRect(0,0,
                          event->scenePos().x()-previousPoint.x(),
                          event->scenePos().y()-previousPoint.y());
        break;


    default:
        break;
    }/*(){
    case :
        if(!itemToDraw)
        {
            itemToDraw = new QGraphicsLineItem();
            previousPoint = event->scenePos();
            itemToDraw->setPos(previousPoint);
            itemToDraw->setPen(QPen(Qt::red,3,Qt::SolidLine));


            this->addItem(itemToDraw);

        }


        itemToDraw->setLine(0,0,
                            event->scenePos().x() - previousPoint.x(),
                            event->scenePos().y() - previousPoint.y());
        break;

    case Ellipse:
        if(!itemellipse)
        {
            itemellipse = new QGraphicsEllipseItem();
            previousPoint = event->scenePos();
            itemellipse->setPos(previousPoint);
            itemellipse->setPen(QPen(Qt::red,3,Qt::SolidLine));
            this->addItem(itemellipse);
        }
        itemellipse->setRect(0,0,
                             event->scenePos().x()-previousPoint.x(),
                             event->scenePos().y()-previousPoint.y());
        break;


    case Rectangle:
        if(!itemrect)
        {
            itemrect= new QGraphicsRectItem();
            previousPoint = event->scenePos();
            itemrect->setPos(previousPoint);
            itemrect->setPen(QPen(Qt::red,3,Qt::SolidLine));

            this->addItem(itemrect);
        }
        itemrect->setRect(0,0,
                          event->scenePos().x()-previousPoint.x(),
                          event->scenePos().y()-previousPoint.y());
        break;

    default:
        break;
    }*/
    QGraphicsScene::mouseMoveEvent(event);

    qDebug()<<"mouse move point"<<event->scenePos();



}
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

      emit measuredrawn(itemToDraw);
      emit measuredrawn(itemellipse);
//    list.append(itemToDraw);
//    list1.append(itemellipse);
//    list2.append(itemrect);

        itemToDraw=NULL;
        itemellipse=NULL;

//    switch (m3) {
//    case Line:
////        if(!itemToDraw)
////        {
////        list12.append(itemToDraw);
////        }
//        emit measuredrawn(itemToDraw);

//            itemToDraw = 0;
//        break;
//    case Ellipse:
//        if(!itemellipse)
//        {
//            list1.append(itemellipse);
//        }
//            itemellipse =0;

//        break;
//    case Rectangle:
//        if(!itemrect)
//        {
//            list2.append(itemrect);
//        }
//            itemrect=0;

//        break;
//    default:
//        break;
//    }





        QGraphicsScene::mouseReleaseEvent(event);
}
