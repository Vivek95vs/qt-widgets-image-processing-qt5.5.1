#include "customscene.h"

customscene::customscene(QObject *parent): QGraphicsScene(parent)
{

}

customscene::~customscene()
{

}

void customscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed=true;
    //     qDebug()<<"Pos X : "<<y.x() <<endl;
    //     qDebug()<<"Pos Y : "<<y.y() <<endl;
    y=event->scenePos() ;
    qDebug()<<"Pos y:"<<y;
     group= this->items();
     qDebug()<<"items-----"<<group.size();

    if(selectedTool==1)
    {

        y=event->scenePos();
        draw_item=true;

            if(group.size()<3)
            {
                draw_item==1;
//                rect->setFlag(QGraphicsItem::ItemIsMovable);
            }
            else
            {
                rect->setFlag(QGraphicsItem::ItemIsMovable);
            }

    }
    QGraphicsScene::mousePressEvent(event);
}
void customscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //    yt=event->scenePos();
    //    qDebug()<<"Pos yt:"<<yt;
    //    y=event->scenePos();
        pressed = true;
        if(selectedTool==1)
        {
            if (event->buttons() == Qt::RightButton)
            {
            if(!rect && draw_item==1){
    //            y = event->scenePos();
                rect = new QGraphicsRectItem(QRectF(event->scenePos(),event->scenePos()));
                rect->setPen(QPen(Qt::blue,5,Qt::SolidLine));
                this->addItem(rect);
                rect->setPos(y);
     //            rect->setFlag(QGraphicsItem::ItemIsMovable);
                //        QRectF newrect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());

            }
            rect->setRect(0,0,event->scenePos().x()-y.x(),event->scenePos().y()-y.y());

            }
            else
            {
                rect->setFlag(QGraphicsItem::ItemIsMovable);
                rect->setFlag(QGraphicsItem::ItemIsSelectable);



                qDebug()<<"rect-----"<<rect->boundingRect()<<rect->boundingRect().width()<<event->scenePos().x()-y.x()<<event->scenePos().y()-y.y();

    //           QRectF newrect(y.x(),y.y(),event->scenePos().x()-y.x(),event->scenePos().y()-y.y());
    //           rect->setRect(newrect);
    //        }
    //        else
    //        {
    //            rect->setFlag(QGraphicsRectItem::ItemIsMovable);
    //        }

        }
            }
        QGraphicsScene::mouseMoveEvent(event);
}

void customscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;

    if(selectedTool==1)
    {
        if(group.size()<3)
        {
        newrect = rect->mapRectToScene(rect->rect());
        rect = new QGraphicsRectItem;
        rect->setRect(QRectF(0,0,newrect.width(),newrect.height()));
        rect->setPos(newrect.x(),newrect.y());
        rect->setPen(QPen(Qt::red,5));
        this->addItem(rect);
//        rect1 = rect->mapRectToScene(rect->rect());
        }
        else
        {
//            rect = 0;
            rect->setFlag(QGraphicsItem::ItemIsMovable);
        }
        group = this->items();

        qDebug()<<group.size()<<"no_of_items";
    }

    QGraphicsScene::mouseReleaseEvent(event);
}
