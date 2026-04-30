#include "drawit.h"
#include<QDebug>
drawit::drawit(QWidget *parent):QGraphicsScene(parent)
{
    selected=0;
    itemtodraw=0;
    itemtodrawrect=0;
    itemtodrawellipse=0;
    itemdrawfree=0;
    scale=false;
    pressed=false;
    makeItemsControllable(true);
}

void drawit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        pressed=true;
    }
    if(pressed){
       makeItemsControllable(true);
    if(selected==1){
        origPoint=event->scenePos();
    }
    if(selected==2){
        origPointr=event->scenePos();
        rectangle.append(origPointr);

        qDebug()<<"pacho";
    }
    if(selected==3){
        origPointe=event->scenePos();
        qDebug()<<"macho";
    }
    if(selected==4){
        itemdrawfree=new QGraphicsPathItem();//pathitem p-painterpath
        origPointf=event->scenePos();
        p.moveTo(origPointf);
        itemdrawfree->setPath(p);
        this->addItem(itemdrawfree);

//          drawnPaths.clear();
    }
}
    QGraphicsScene::mousePressEvent(event);

}
void drawit::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    makeItemsControllable(false);
    if(selected==1 && pressed){
        if(!itemtodraw){
        itemtodraw=new QGraphicsLineItem;
        this->addItem(itemtodraw);
        itemtodraw->setPen(QPen(Qt::black,13,Qt::SolidLine));
        itemtodraw->setPos(origPoint);
    }
    itemtodraw->setLine(0,0,event->scenePos().x()-origPoint.x(),event->scenePos().y()-origPoint.y());
}
    if(selected==2  && pressed){
         QBrush my(Qt::white,Qt::NoBrush);
         if(!itemtodrawrect){
         qDebug()<<"hello";
         itemtodrawrect=new QGraphicsRectItem;
         this->addItem(itemtodrawrect);
         itemtodrawrect->setBrush(my);
    }
          itemtodrawrect->setRect(origPointr.x(),origPointr.y(),event->scenePos().x()-origPointr.x(),event->scenePos().y()-origPointr.y());

         rectangle.append(QPointF(event->scenePos().x(),event->scenePos().y()));
}
   if(selected==3  && pressed){
       if(!itemtodrawellipse){
         itemtodrawellipse=new QGraphicsEllipseItem;
         this->addItem(itemtodrawellipse);
         itemtodrawellipse->setBrush(Qt::white);
         itemtodrawellipse->setPen(Qt::NoPen);
   }
       itemtodrawellipse->setRect(origPointe.x(),origPointe.y(),event->scenePos().x()-origPointe.x(),event->scenePos().y()-origPointe.y());
 }
   if(selected==4  && pressed){
       qDebug()<<"hola";
       if(itemdrawfree){
           QPainterPath path=itemdrawfree->path();
           origPointf=event->scenePos();
           path.lineTo(origPointf);
           path.setFillRule(Qt::WindingFill);
           itemdrawfree->setPen(QPen(Qt::white,7));
           itemdrawfree->setPath(path);
           pathcoord.append(origPointf);
       }

   }
   else{
          QGraphicsScene::mouseMoveEvent(event);
      }

}
void drawit::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
 {
     makeItemsControllable(true);
 if(pathcoord.size()>0){
     QPainterPath path=itemdrawfree->path();
     path.lineTo(pathcoord.at(0));
     path.setFillRule(Qt::WindingFill);
     itemdrawfree->setPen(QPen(Qt::white,7));
     itemdrawfree->setPath(path);
     itemdrawfree=0;
     for(auto j=pathcoord.begin();j!=pathcoord.end();++j){
             pathcoord.erase(j);
           }

     drawnPaths.append(path);
    }
 //qDebug()<<c;
    pressed=false;
    itemtodraw1=0;
    itemtodraw=0;
    itemtodrawrect=0;
    itemtodrawellipse=0;
    QGraphicsScene::mouseReleaseEvent(event);

}

void drawit::redrawPaths()
{
    // Clear the scene before redrawing
//    clear();

    // Iterate through the stored paths and redraw them
    for (const auto& path : drawnPaths) {
        QGraphicsPathItem* newPathItem = new QGraphicsPathItem();
        newPathItem->setPath(path);
        newPathItem->setPen(QPen(Qt::white, 7));
        addItem(newPathItem);
    }
}

void drawit::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_P){

        foreach (QGraphicsItem* item, selectedItems()) {
            qDebug()<<"hello";
            removeItem(item);
            delete item;
        }
    }
    else{
        QGraphicsScene::keyPressEvent(event);
    }
}

void drawit::makeItemsControllable(bool areControllable)
{
    foreach (QGraphicsItem* item, items()) {
        QGraphicsRectItem *node=qgraphicsitem_cast<QGraphicsRectItem*>(item);
        QGraphicsEllipseItem *node1=qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        QGraphicsLineItem *node2=qgraphicsitem_cast<QGraphicsLineItem*>(item);
        QGraphicsPathItem *node3=qgraphicsitem_cast<QGraphicsPathItem*>(item);
        if(node || node1 || node2 || node3){
        item->setFlag(QGraphicsItem::ItemIsSelectable,areControllable);
}
}
}
