#include "custumscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsItem>

//custumscene *scene;

custumscene::custumscene()
{

}

custumscene::~custumscene()
{

}

void custumscene::mousePressEvent(QMouseEvent *event)
{
//    qDebug()<<"mouse pressed----";
    pressed=true;
    //     qDebug()<<"Pos X : "<<y.x() <<endl;
    //     qDebug()<<"Pos Y : "<<y.y() <<endl;
    y=event->scenePos() ;

    qDebug()<<"Pos y:"<<y;
     group= this->items();
     qDebug()<<"items-----"<<group.size();

    switch(selectedTool)
    {

    case 1:

        y=event->scenePos();

        rect = new QGraphicsRectItem(QRectF(event->scenePos(),event->scenePos()));
        rect->setPen(QPen(Qt::blue,5));
        addItem(rect);
        qDebug()<<"Starting Pos:"<<y;


        break;

    case 2:

        ellipse = new QGraphicsEllipseItem(QRectF(event->scenePos(),event->scenePos()));
        ellipse->setPen(QPen(Qt::red,5));
        addItem(ellipse);
        qDebug()<<"Starting Pos:"<<y<<ellipse->x()<<ellipse->y();

        break;

    case 3:

        mypath =new QGraphicsPathItem();
        QPainterPath p;
        y=event->scenePos();
        p.moveTo(y);
        mypath->setPath(p);
        mypath->setPen(QPen(Qt::red,5));
        this->addItem(mypath);
        qDebug()<<"Starting Pos:"<<y;

        break;

//    case 4:

    }

//    QGraphicsScene::mousePressEvent(event);
    QVTKWidget::mousePressEvent(event);
}

void custumscene::mouseMoveEvent(QMouseEvent *event)
{
//    yt=event->scenePos();
//    qDebug()<<"Pos yt:"<<yt;
//    y=event->scenePos();
    pressed = true;
    if(selectedTool==1)
    {

        QRectF newrect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
        rect->setRect(newrect);
        rect->setFlag(QGraphicsItem::ItemIsSelectable);

    }


    else if(selectedTool==2)
    {
        QRectF newellipse(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
        ellipse->setRect(newellipse);
        ellipse->setFlag(QGraphicsItem::ItemIsSelectable);

    }

    else if(selectedTool==3)
    {
        QPainterPath path=mypath->path();
        y=event->scenePos();
        path.lineTo(y);
        mypath->setPath(path);
        mypath->setFlag(QGraphicsItem::ItemIsSelectable);


    }


//    QGraphicsScene::mouseMoveEvent(event);
    QVTKWidget::mouseMoveEvent(event);


}


void custumscene::mouseReleaseEvent(QMouseEvent *event)
{
//    pressed = true;
//    if(selectedTool==1)
//    {
//        QRectF newrect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
//        rect->setRect(newrect);
//        rect->setFlag(QGraphicsRectItem::ItemIsMovable);

//    }
//        QRectF newrect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
//        rect->setRect(newrect);
//        selectedTool=0;
       // this->removeItem(rect);

//        delete rect;
//        this->removeItem(rect);
//        rect = NULL;
//    y=event->scenePos();
//    pressed = true;

//    if(selectedTool==1)
//    {
//        rect = 0;
//        y=event->scenePos();
//        rect1 = new QGraphicsRectItem();
//        rect1->setRect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
//        rect1->setPen(QPen(Qt::red,5));
//        addItem(rect1);

//        output = rect->mapRectToScene(rect->rect());
//        delete rect;

//        w=event->scenePos().x() - y.x();
//        h=event->scenePos().y() - y.y();
//        rect = new QGraphicsRectItem();
//        rect->setRect(y.x(),y.y(),w,h);
//        qDebug()<<"Mouse Pos:"<<w<<h;
//        rect->setPen(QPen(Qt::red,5));
//        this->addItem(rect);

//        output = rect->mapRectToScene(rect->rect());
//        this->removeItem(rect);
//        rect =NULL;
//        delete rect;
//        if(group.size()<3)
//        {
//        newrect = rect->mapRectToScene(rect->rect());
// //        rect = new QGraphicsRectItem;
//        rect->setRect(QRectF(0,0,newrect.width(),newrect.height()));
//        rect->setPos(newrect.x(),newrect.y());
//        rect->setPen(QPen(Qt::red,5));
//        this->addItem(rect);
//        rect1 = rect->mapRectToScene(rect->rect());
//        }
//        else
//        {
// //            rect = 0;
//            rect->setFlag(QGraphicsItem::ItemIsMovable);
//        }

//        qDebug()<<group.size()<<"no_of_items";

//        rect1->setRect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());


//        rect1->setRect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
//        rect1->setRect(QRectF(0,0,output.width(),output.height()));
//        rect1->setRect(output.x(),output.y(),event->scenePos().x()-output.x(),event->scenePos().y()-output.y());
//        rect1->setPos(output.x(),output.y());
//        rect1->setPen(QPen(Qt::red,5));
//        addItem(rect1);
//        output= rect->mapRectToScene(rect->rect());
//        this->addRect(output);
//        this->addItem(rect);
//        qDebug()<<yt<<"yt---------"<<event->scenePos();
//        qDebug()<<y.y();
//        rect->setRect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
//        rect->setPen(QPen(Qt::red,5));
//        rect->setBrush(QBrush(Qt::red));


//    }
//    }

//    QGraphicsScene::mouseReleaseEvent(event);
    QVTKWidget::mouseReleaseEvent(event);
}



