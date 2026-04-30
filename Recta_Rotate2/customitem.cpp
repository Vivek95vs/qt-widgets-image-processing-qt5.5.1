#include "customitem.h"

customitem::customitem()
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

QVariant customitem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    QPointF newPos;
    if (change == ItemPositionChange && scene()) {

        // value is the new position.
        newPos = value.toPointF();

        emit itemChanged(newPos);

    }

    return QGraphicsItem::itemChange(change, value);
}

