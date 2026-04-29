#include "customitemellipse.h"
//extern int tMode;
CustomItemEllipse::CustomItemEllipse()
{

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

//    setFlag(ItemSendsScenePositionChanges);
}

QVariant CustomItemEllipse::itemChange(GraphicsItemChange change, const QVariant &value)
{
    try
    {
    QPointF newPos;
//    setFlag(ItemIsMovable,true);
    if (change == ItemPositionChange && scene()) {

        // value is the new position.

        newPos = value.toPointF();
    //    QRectF rect = this->rect();


        //qDebug()<<"ssssssssss "<<change;
       // setFlag(ItemIsMovable,true);



//        if(rect.x()+newPos.x()>5 && rect.y()+newPos.y()>5 && rect.bottomRight().x()+newPos.x()<507 && rect.bottomRight().y()+newPos.y()<507)
//        {
//            setFlag(ItemIsMovable,true);
//            emit itemChanged(newPos);
//        }
//        else
//            setFlag(ItemIsMovable,false);



//        if(tMode==0)
//        {
//                if(this->sceneBoundingRect().x()+newPos.x()>5 && this->sceneBoundingRect().y()+newPos.y()>5 && this->sceneBoundingRect().bottomRight().x()+newPos.x()<507 && this->sceneBoundingRect().bottomRight().y()+newPos.y()<507)
//                {
//                    setFlag(ItemIsMovable,true);
//                    emit itemChanged(newPos);
//                }
////                else
////                {
////                    if(this->sceneBoundingRect().x()<5)
////                    {

////                        this->moveBy(1,0);
////                    }
////                    if(this->sceneBoundingRect().y()<5)
////                    {
////                        this->moveBy(0,1);
////                    }
////                    if(this->sceneBoundingRect().topRight().x()>507)
////                    {
////                        this->moveBy(-1,0);
////                    }
////                    if(this->sceneBoundingRect().y()>507)
////                    {
////                        this->moveBy(0,-1);
////                    }
////                    setFlag(ItemIsMovable,false);
////                }
//        }
//        else
//        {

//                    if(this->rect().x()+this->pos().x()/*+newPos.x()*/>5 && this->rect().y()+this->pos().y()/*+newPos.y()*/>5 && this->rect().bottomRight().x()+this->pos().x()/*+newPos.x()*/<940 && this->rect().bottomRight().y()+this->pos().y()/*+newPos.y()*/<940)
//                    {
//                        setFlag(ItemIsMovable,true);
//                        emit itemChanged(newPos);
//                    }
////                    else
////                    {
//////                        qDebug()<<"check rect"<<this->rect()<<newPos<<this->pos();
//////                        if(this->rect().x()+this->pos().x()<5)
//////                        {

//////                          //  this->setPos(this->pos().x()+5,this->pos().y());
//////                            this->moveBy(5,0);
//////                        }
//////                        if(this->rect().y()+this->pos().y()<5)
//////                        {
//////                            this->moveBy(0,5);
//////                          //  this->setPos(this->pos().x(),this->pos().y()+5);
//////                        }
//////                        if(this->rect().topRight().x()+this->pos().x()>940)
//////                        {
//////                          //  this->moveBy(-5,0);
//////                            qDebug()<<"this->rect().topRight().x()"<<this->rect().topRight().x();
//////                           // this->setPos(this->pos().x()-5,this->pos().y());
//////                        }
//////                        if(this->rect().bottomLeft().y()+this->pos().y()>940)
//////                        {
//////                           // this->setPos(this->pos().x(),this->pos().y()-5);
//////                            this->moveBy(0,-5);
//////                        }

////                      //  qDebug()<<"check rect"<<this->rect()<<newPos<<this->pos();

////                        setFlag(ItemIsMovable,true);
////                    }


//        }





////        qDebug()<<"newPos"<<newPos;

       emit itemChanged(newPos);

      }
    }
    catch(std::exception &err)
    {
         qDebug()<<"SizeGrip"<<err.what();
    }

    return QGraphicsItem::itemChange(change, value);
}
