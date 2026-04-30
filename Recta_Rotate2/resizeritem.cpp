#include "resizeritem.h"
#include <QBrush>

int resizeUpdate=0;
int resizeState;
bool enableResize;

resizeritem::HandleItem::HandleItem(int positionFlags, resizeritem* parent)
    : QGraphicsRectItem(-10, -10, 20, 20, parent),
      positionFlags_(positionFlags),
      parent_(parent)
{
    setBrush(QBrush(Qt::lightGray));
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

}

int resizeritem::HandleItem::positionFlags() const
{
    return positionFlags_;

}

QVariant resizeritem::HandleItem::itemChange(GraphicsItemChange change,
                                              const QVariant &value)
{

    QVariant retVal = value;

//    QVariant retVal = value;

    if (change == ItemPositionChange)
    {
//        retVal = restrictPosition(value1);
        retVal = restrictPosition(value.toPointF());
    }
    else if (change == ItemPositionHasChanged)
    {
//        QPointF pos = value1;
        QPointF pos = value.toPointF();
        resizeUpdate=1;
//        qDebug() <<"possizegrip "<<pos;

        switch (positionFlags_)
        {
        case TopLeft:
            parent_->setTopLeft(pos);
            break;
        case Top:
            parent_->setTop(pos.y());
            break;
        case TopRight:
            parent_->setTopRight(pos);
            break;
        case Right:
            parent_->setRight(pos.x());
            break;
        case BottomRight:
            parent_->setBottomRight(pos);
            break;
        case Bottom:
            parent_->setBottom(pos.y());
            break;
        case BottomLeft:
            parent_->setBottomLeft(pos);
            break;
        case Left:
            parent_->setLeft(pos.x());
            break;
        }

        resizeState = positionFlags_;
//        qDebug() <<"resizeState "<<resizeState;
    }

    return retVal;

}

QPointF resizeritem::HandleItem::restrictPosition(const QPointF& newPos)
{

    QPointF retVal = pos();
//    retVal.setX(retVal.x()-accShiftX);
//    retVal.setY(retVal.y()-accShiftY);

//    qDebug()<<"rectVal1 "<<retVal;


    if (positionFlags_ & Top || positionFlags_ & Bottom)
        retVal.setY(newPos.y());

    if (positionFlags_ & Left || positionFlags_ & Right)
        retVal.setX(newPos.x());

    if (positionFlags_ & Top && retVal.y() > parent_->rect_.bottom())
        retVal.setY(parent_->rect_.bottom());
    else if (positionFlags_ & Bottom && retVal.y() < parent_->rect_.top())
        retVal.setY(parent_->rect_.top());

    if (positionFlags_ & Left && retVal.x() > parent_->rect_.right())
        retVal.setX(parent_->rect_.right());
    else if (positionFlags_ & Right && retVal.x() < parent_->rect_.left())
        retVal.setX(parent_->rect_.left());

    return retVal;
}

resizeritem::resizeritem(Resizer* resizer, QGraphicsItem* parent)
    : QGraphicsItem(parent),
      resizer_(resizer)
{

   // qDebug()<<"Entering resizer1.......";

    if (parentItem())
        rect_ = parentItem()->boundingRect();

  //  qDebug()<<"handleItems_"<<handleItems_.length();

    handleItems_.append(new HandleItem(TopLeft, this));
    handleItems_.append(new HandleItem(Top, this));
    handleItems_.append(new HandleItem(TopRight, this));
    handleItems_.append(new HandleItem(Right, this));
    handleItems_.append(new HandleItem(BottomRight, this));
    handleItems_.append(new HandleItem(Bottom, this));
    handleItems_.append(new HandleItem(BottomLeft, this));
    handleItems_.append(new HandleItem(Left, this));

    updateHandleItemPositions();
}

resizeritem::~resizeritem()
{
    if (resizer_)
        delete resizer_;
}

QRectF resizeritem::boundingRect() const
{

   // qDebug()<<"Entering resizer2.......";

    return rect_;
}

void resizeritem::paint(QPainter* painter,
                         const QStyleOptionGraphicsItem* option,
                         QWidget* widget)
{

//    emit itemChanged(rect_);

}

#define IMPL_SET_FN(TYPE, POS)                  \
    void resizeritem::set ## POS (TYPE v)      \
{                                           \
    rect_.set ## POS (v);                   \
    doResize();                             \
    }

IMPL_SET_FN(qreal, Top)
IMPL_SET_FN(qreal, Right)
IMPL_SET_FN(qreal, Bottom)
IMPL_SET_FN(qreal, Left)
IMPL_SET_FN(const QPointF&, TopLeft)
IMPL_SET_FN(const QPointF&, TopRight)
IMPL_SET_FN(const QPointF&, BottomRight)
IMPL_SET_FN(const QPointF&, BottomLeft)

void resizeritem::doResize()
{

    if (resizer_)
    {

      //  qDebug()<<"Entering resizer3.......";
        (*resizer_)(parentItem(), rect_);
        updateHandleItemPositions();
    }

}

void resizeritem::updateHandleItemPositions()
{

    emit itemChanged(rect_,1);


    foreach (HandleItem* item, handleItems_)
    {
        item->setFlag(ItemSendsGeometryChanges, false);

        switch (item->positionFlags())
        {
        case TopLeft:
            item->setPos(rect_.topLeft());
            break;
        case Top:
            item->setPos(rect_.left() + rect_.width() / 2 - 1,
                         rect_.top());
            break;
        case TopRight:
            item->setPos(rect_.topRight());
            break;
        case Right:
            item->setPos(rect_.right(),
                         rect_.top() + rect_.height() / 2 - 1);
            break;
        case BottomRight:
            item->setPos(rect_.bottomRight());
            break;
        case Bottom:
            item->setPos(rect_.left() + rect_.width() / 2 - 1,
                         rect_.bottom());
            break;
        case BottomLeft:
            item->setPos(rect_.bottomLeft());
            break;
        case Left:
            item->setPos(rect_.left(),
                         rect_.top() + rect_.height() / 2 - 1);
            break;
        }

        item->setFlag(ItemSendsGeometryChanges, true);
    }
}
