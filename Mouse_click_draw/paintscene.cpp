#include "paintscene.h"
#include "paint.h"

#include <QString>
#include <QFile>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsPixmapItem>

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}

QRectF paintScene::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

//    addEllipse(event->scenePos().x() - 5,event->scenePos().y() - 5,10,10,QPen(Qt::NoPen),QBrush(Qt::red));
//    previousPoint = event->scenePos();
//    QGraphicsScene::mousePressEvent(event);

    pressed = true;
    y = event->scenePos();
//    qDebug()<<"Pos X : "<<y.x() <<endl;
//    qDebug()<<"Pos Y : "<<y.y() <<endl;

    switch(selectedTool)
    {

    case 1:

//        Circle = new QGraphicsEllipseItem(QRectF(event->scenePos(),event->scenePos()));
//        Circle->setPen(QPen(Qt::red,5));
//        addItem(Circle);
//        Circle->setFlag(QGraphicsEllipseItem::ItemIsSelectable);
        Circle=new QGraphicsEllipseItem;


        break;

    case 2:

         line = new QGraphicsLineItem(QLineF(event->scenePos(),event->scenePos()));
         line->setPen(QPen(Qt::black,5));
         addItem(line);

        break;

    case 3:

        rect = new QGraphicsRectItem(QRectF(event->scenePos(),event->scenePos()));
        rect->setPen(QPen(Qt::blue,5));
        addItem(rect);
        rect->setFlag(QGraphicsRectItem::ItemIsSelectable);
        break;

    case 4:

        mypath =new QGraphicsPathItem();
        QPainterPath p;
        y=event->scenePos();
        p.moveTo(y);
        mypath->setPath(p);
        mypath->setPen(QPen(Qt::red,5));
        this->addItem(mypath);
        break;


//    default:
//               ;
    }

    QGraphicsScene::mousePressEvent(event);

    }

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    pressed = true;
    if(selectedTool==1)
    {
//        addEllipse(event->scenePos().x()-50,event->scenePos().y()-50,100,100);
//        Circle->setPos(y);
        QRectF newcircle(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
        Circle->setRect(newcircle);
    }

    else if(selectedTool==2)
    {
        QLineF newline(line->line().p1(),event->scenePos());
        line->setLine(newline);
        line->setFlag(QGraphicsLineItem::ItemIsSelectable);
    }

    else if(selectedTool==3)
    {
        //addRect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y(),QPen(Qt::blue,2));
        QRectF newrect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
        rect->setRect(newrect);
    }

    else if(selectedTool==4)
    {
        QPainterPath path=mypath->path();
        y=event->scenePos();
        path.lineTo(y);
        mypath->setPath(path);
        mypath->setFlag(QGraphicsPathItem::ItemIsSelectable);
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void paintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

