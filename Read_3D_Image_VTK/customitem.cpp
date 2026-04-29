#include "customitem.h"

extern int tMode;
volatile bool stopROI=0;
CustomItem::CustomItem()
{


    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    //    setFlag(ItemSendsScenePositionChanges);
}


//QVariant CustomItem::itemChange(GraphicsItemChange change, const QVariant &value)
//{
//    if (change == ItemPositionChange && scene()) {

//        update();

//        // value is the new position.
//        QPointF newPos = value.toPointF();

//        emit itemChanged(newPos);


//    }
//    return QGraphicsItem::itemChange(change, value);

//}


QVariant CustomItem::itemChange(GraphicsItemChange change, const QVariant &value)
{

    try
    {
    QPointF newPos;
    //    qDebug()<<"rectttt";
    //    setFlag(ItemIsMovable,true);
    //    qDebug()<<"rectttt";
    if (change == ItemPositionChange && scene() && stopROI==0) {

       // qDebug()<<"stopROI"<<stopROI;
        // value is the new position.
        newPos = value.toPointF();

        //        QRectF rect = this->rect();

        //   qDebug()<<"rectttt"<<rect;


//        if(tMode==0)
//        {
//            if(this->sceneBoundingRect().x()/*+newPos.x()*/>5 && this->sceneBoundingRect().y()/*+newPos.y()*/>5 && this->sceneBoundingRect().bottomRight().x()/*+newPos.x()*/<507 && this->sceneBoundingRect().bottomRight().y()/*+newPos.y()*/<507)
//            {
//                setFlag(ItemIsMovable,true);
//                emit itemChanged(newPos);
//            }
////            else
////            {
//////qDebug()<<"checccck for this";
//////                if(this->sceneBoundingRect().x()<5)
//////                {

//////                    this->moveBy(1,0);
//////                }
//////                if(this->sceneBoundingRect().y()<5)
//////                {
//////                    this->moveBy(0,1);
//////                }
//////                if(this->sceneBoundingRect().topRight().x()>507)
//////                {
//////                    this->moveBy(-1,0);
//////                }
//////                if(this->sceneBoundingRect().bottomLeft().y()>507)
//////                {
//////                    this->moveBy(0,-1);
//////                }
////                setFlag(ItemIsMovable,true);
////            }
//        }
//        else
//        {

//            // qDebug()<<"sssss"<<sceneBoundingRect().x()<<sceneBoundingRect().y()<<newPos.x()<<newPos.y()<<sceneBoundingRect().bottomRight();
//            if(this->sceneBoundingRect().x()/*+newPos.x()*/>5 && this->sceneBoundingRect().y()/*+newPos.y()*/>5 && this->sceneBoundingRect().bottomRight().x()/*+newPos.x()*/<940 && this->sceneBoundingRect().bottomRight().y()/*+newPos.y()*/<940)
//            {
//                setFlag(ItemIsMovable,true);
//                emit itemChanged(newPos);
//            }
////            else
////            {
////               // qDebug()<<"dddddddddddddddd"<<sceneBoundingRect().x()<<sceneBoundingRect().y()<< sceneBoundingRect().topRight().x()    <<sceneBoundingRect().bottomLeft().y();
////// qDebug()<<"new pos"<<newPos.x(),newPos.y();

//////                if(this->sceneBoundingRect().topRight().x()>940 && this->sceneBoundingRect().bottomLeft().y()>940 )
//////                {
//////                    qDebug()<<"hiiiiiii";
//////                    stopROI=1;
//////                    this->moveBy(935-this->sceneBoundingRect().topRight().x(),935-this->sceneBoundingRect().bottomLeft().y());
//////                }


//////                else if( this->sceneBoundingRect().y()<5 && this->sceneBoundingRect().topRight().x()>940)
//////                {
//////                     qDebug()<<"2nd";
//////                      stopROI=1;
//////                    this->moveBy(935-this->sceneBoundingRect().topRight().x(),-this->sceneBoundingRect().topRight().y()+10);
//////                }



//////                else if(this->sceneBoundingRect().x()<5 && this->sceneBoundingRect().bottomLeft().y()>940)
//////                {
//////                     qDebug()<<"3rd";
//////                      stopROI=1;
//////                    this->moveBy(-this->sceneBoundingRect().topLeft().x()+10,935-this->sceneBoundingRect().bottomLeft().y());
//////                }
//////                else if(this->sceneBoundingRect().x()<5 && this->sceneBoundingRect().y()<5)
//////                {
//////                     qDebug()<<"4rth";
//////                    stopROI=1;
//////                    this->moveBy(-this->sceneBoundingRect().topLeft().x()+10,-this->sceneBoundingRect().topRight().y()+10);
//////                }





//////                else if(this->sceneBoundingRect().x()<5)
//////                {
//////                    qDebug()<<"222";
//////                    stopROI=1;
//////                    this->moveBy(-this->sceneBoundingRect().topLeft().x()+10,0);

//////                }
//////                else if(this->sceneBoundingRect().y()<5)
//////                {
//////                    stopROI=1;
//////                    qDebug()<<"111";
//////                    this->moveBy(0,-this->sceneBoundingRect().topRight().y()+10);
//////                    //                    this->moveBy(0,5);
//////                }
//////                else if(this->sceneBoundingRect().topRight().x()>940)
//////                {
//////                    stopROI=1;
//////                    qDebug()<<"sssss";
//////                    this->moveBy(935-this->sceneBoundingRect().topRight().x(),0);

//////                    //return 0;

//////                }
//////                else if(this->sceneBoundingRect().bottomLeft().y()>940)
//////                {
//////                    qDebug()<<"333";
//////                    stopROI=1;
//////                    this->moveBy(0,935-this->sceneBoundingRect().bottomLeft().y());
//////                }


////                setFlag(ItemIsMovable,true);
////            }


//        }


//        //        //        qDebug()<<"sceneRect"<<rect;
//        //        if (!rect.contains(newPos)) {
//        //            // Keep the item inside the scene rect.
//        //            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
//        //            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
//        //            return newPos;
//        //        }
//        //                qDebug()<<"newPos"<<newPos;


//    }
        emit itemChanged(newPos);
    }
    }
    catch(std::exception &err)
    {
         qDebug()<<"SizeGrip"<<err.what();
    }

    return QGraphicsItem::itemChange(change, value);
}


