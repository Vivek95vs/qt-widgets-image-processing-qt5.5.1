#include "customitem.h"

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
    QPointF newPos;
    if (change == ItemPositionChange && scene()) {

        // value is the new position.
        newPos = value.toPointF();

        //        QRectF rect = scene()->sceneRect();
        //        //        qDebug()<<"sceneRect"<<rect;
        //        if (!rect.contains(newPos)) {
        //            // Keep the item inside the scene rect.
        //            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
        //            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
        //            return newPos;
        //        }
        //                qDebug()<<"newPos"<<newPos;
        emit itemChanged(newPos);

    }

    return QGraphicsItem::itemChange(change, value);
}


