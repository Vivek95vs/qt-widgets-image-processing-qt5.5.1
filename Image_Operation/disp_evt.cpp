#include "disp_evt.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsItem>

Disp_Evt *scene;
extern double ValueDia;

Disp_Evt::Disp_Evt(QObject *parent) : QGraphicsScene(parent)
{

    ellipse = new QGraphicsEllipseItem();
    isocenterrect=new QGraphicsRectItem();

}

Disp_Evt::~Disp_Evt()
{

}

void Disp_Evt::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

//        ellipse = new QGraphicsEllipseItem();
        qDebug()<<"bvalue"<<ValueDia;
        ellipse->setPen(QPen(Qt::red,5));
        this->addItem(ellipse);
        ellipse->setZValue(1);
        ellipse->setRect(600,500,ValueDia,ValueDia);
        ellipse->setFlag(QGraphicsItem::ItemIsSelectable,true);
        ellipse->setFlag(QGraphicsItem::ItemIsMovable,true);
        break;

    case 3:

        mypath =new QGraphicsPathItem();
        p=new QPainterPath;
        y=event->scenePos();
        p->moveTo(y);
        mypath->setPath(*p);
        mypath->setPen(QPen(Qt::red,5));
        this->addItem(mypath);
        qDebug()<<"Starting Pos:"<<y;
        break;

//    case 4:

    }

    QGraphicsScene::mousePressEvent(event);
}

void Disp_Evt::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    yt=event->scenePos();
//    qDebug()<<"Pos yt:"<<yt;
//    y=event->scenePos();
    pressed = true;
    if(selectedTool==1)
    {

        QRectF newrect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
        rect->setRect(newrect);
//        rect->setBrush(QBrush(Qt::black, Qt::SolidPattern));
        rect->setFlag(QGraphicsItem::ItemIsSelectable);


    }


    else if(selectedTool==2)
    {
        ellipse->setRect(600,500,ValueDia,ValueDia);
        ellipse->setFlag(QGraphicsItem::ItemIsSelectable);

    }

    else if(selectedTool==3)
    {
//        QPainterPath path=mypath->path();



        y=event->scenePos();
        p->lineTo(y);
        mypath->setPath(*p);
        mypath->setFlag(QGraphicsItem::ItemIsSelectable);
        mypath->setBrush(QBrush(Qt::black, Qt::SolidPattern));


    }


    QGraphicsScene::mouseMoveEvent(event);


}


void Disp_Evt::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
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
    if(selectedTool==2)
    {
//        ellipse->setBrush(Qt::white);
//        isocenterrect= new QGraphicsRectItem();
        isocenterrect->setRect(ellipse->sceneBoundingRect().center().rx(),ellipse->sceneBoundingRect().center().ry(),5,5);
        isocenterrect->setPen(QPen(Qt::green, 2, Qt::SolidLine));

        isocenterrect->setBrush(QBrush(Qt::green, Qt::SolidPattern));

        this->addItem(isocenterrect);

        emit sendtohide();

    }

    else if(selectedTool==3)
    {
//        QPainterPath path=mypath->path();

        pressed = false;

        qDebug()<<"Enter value";
        // Finalize the path by drawing a line to the last recorded position
        p->lineTo(y);
        mypath->setPath(*p);


    }
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

    QGraphicsScene::mouseReleaseEvent(event);
}

void Disp_Evt::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
   case Qt::Key_Left:
//       if(selectedTool==1)
//       {
//    rect->setPos(rect->x()-10,rect->y());
//    qDebug()<<"pressed left key";
//       }
//       else if(selectedTool==2)
//       {
//    ellipse->setPos(ellipse->x()-10,ellipse->y());
//    qDebug()<<"pressed left key";
//       }
//       else if(selectedTool==3)
//       {
//    mypath->setPos(mypath->x()-10,mypath->y());
//    qDebug()<<"pressed left key";
//       }

        emit positionLeftchanges();
       break;

   case Qt::Key_Right:
//       if(selectedTool==1)
//       {
//    rect->setPos(rect->x()+10,rect->y());
//    qDebug()<<"pressed right key";
//       }
//       else if(selectedTool==2)
//       {
//    ellipse->setPos(ellipse->x()+10,ellipse->y());
//    qDebug()<<"pressed right key";
//       }
//       else if(selectedTool==3)
//       {
//    mypath->setPos(mypath->x()+10,mypath->y());
//    qDebug()<<"pressed right key";
//       }
    emit positionRightchanges();
       break;

   case Qt::Key_Up:
//       if(selectedTool==1)
//       {
//    rect->setPos(rect->x(),rect->y()-10);
//    qDebug()<<"pressed Up key";
//       }
//       else if(selectedTool==2)
//       {
//    ellipse->setPos(ellipse->x(),ellipse->y()-10);
//    qDebug()<<"pressed Up key";
//       }
//       else if(selectedTool==3)
//       {
//    mypath->setPos(mypath->x(),mypath->y()-10);
//    qDebug()<<"pressed Up key";
//       }
//       scene->items().at(itemTrackAP)->moveBy(posChanged.x(),posChanged.y()-10);
        emit positionUpchanges();
       break;

   case Qt::Key_Down:
//       if(selectedTool==1)
//       {
//    rect->setPos(rect->x(),rect->y()+10);
//    qDebug()<<"pressed Down key";
//       }
//       else if(selectedTool==2)
//       {
//    ellipse->setPos(ellipse->x(),ellipse->y()+10);
//    qDebug()<<"pressed Down key";
//       }
//       else if(selectedTool==3)
//       {
//    mypath->setPos(mypath->x(),mypath->y()+10);
//    qDebug()<<"pressed Down key";
//       }
        emit positionDownchanges();
       break;
   }
   QGraphicsScene::keyPressEvent(event);
}


