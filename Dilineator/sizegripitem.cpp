/*
 * SizeGripItem - A size grip QGraphicsItem for interactive resizing.
 *
 * Copyright (c) 2011 Cesar L. B. Silveira
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <QBrush>
#include "SizeGripItem.h"


int resizeUpdate=0;

int resizeState;

extern double accShiftX,accShiftY;

extern bool enableResize;

SizeGripItem::HandleItem::HandleItem(int positionFlags, SizeGripItem* parent)
    : QGraphicsRectItem(-10, -10, 20, 20, parent),
      positionFlags_(positionFlags),
      parent_(parent)
{
    setBrush(QBrush(Qt::lightGray));
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

}

int SizeGripItem::HandleItem::positionFlags() const
{
    return positionFlags_;

}

QVariant SizeGripItem::HandleItem::itemChange(GraphicsItemChange change,
                                              const QVariant &value)
{

   // qDebug()<<"Entering resizer.......";

   // qDebug()<<"position 1"<<parent_->rect_.x()<<parent_->rect_.y()<<parent_->rect_.width()<<parent_->rect_.height();

 //   qDebug()<<"value"<<value.toPointF();

//    value.toPointF().rx() = value.toPointF().rx()+accShiftX;
//    value.toPointF().ry() = value.toPointF().ry()+accShiftY;

//    QPointF value1;

//    value1.rx() = value.toPointF().rx()+accShiftX;
//    value1.ry() = value.toPointF().ry()+accShiftY;

    //qDebug()<<"value"<<value1;


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

QPointF SizeGripItem::HandleItem::restrictPosition(const QPointF& newPos)
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

//    qDebug()<<"rectVal2 "<<retVal;
//    qDebug()<<"position "<<parent_->rect_.x()<<parent_->rect_.y()<<parent_->rect_.width()<<parent_->rect_.height();



//    accShiftX=0;
//    accShiftY=0;

//    if(retVal.y()+accShiftY>3070)
//        retVal.setY(3070-accShiftY);
//    if(retVal.y()+accShiftY<2)
//        retVal.setY(2-accShiftY);
//    if(retVal.x()+accShiftX>3070)
//        retVal.setX(3070-accShiftX);
//    if(retVal.x()+accShiftX<2)
//        retVal.setX(2-accShiftY);

 //    qDebug()<<"QPointretVal "<<retVal;


    return retVal;
}

SizeGripItem::SizeGripItem(Resizer* resizer, QGraphicsItem* parent)
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

SizeGripItem::~SizeGripItem()
{
    if (resizer_)
        delete resizer_;
}

QRectF SizeGripItem::boundingRect() const
{

   // qDebug()<<"Entering resizer2.......";

    return rect_;

}

void SizeGripItem::paint(QPainter* painter,
                         const QStyleOptionGraphicsItem* option,
                         QWidget* widget)
{

//    emit itemChanged(rect_);


}

#define IMPL_SET_FN(TYPE, POS)                  \
    void SizeGripItem::set ## POS (TYPE v)      \
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

void SizeGripItem::doResize()
{

    if (resizer_)
    {

      //  qDebug()<<"Entering resizer3.......";
        (*resizer_)(parentItem(), rect_);
        updateHandleItemPositions();
    }

}

void SizeGripItem::updateHandleItemPositions()
{
  //  qDebug()<<"Entering resizer4.......";


//    if(resizeState==5)
//    {
//        rect_.setTop(rect_.top()-accShiftY);
//        rect_.setLeft(rect_.left()-accShiftX);
//    }
//    else if(resizeState==1)
//    {
//        rect_.setTop(rect_.top()-accShiftY);
//    }

//    else if(resizeState==9)
//    {
//        rect_.setTop(rect_.top()-accShiftY);
//        rect_.setRight(rect_.right()-accShiftX);

//    }
//    else if(resizeState==8)
//    {
//        rect_.setRight(rect_.right()-accShiftX);

//    }
//    else if(resizeState==10)
//    {
//        rect_.setRight(rect_.right()-accShiftX);
//        rect_.setBottom(rect_.bottom()-accShiftY);

//    }
//    else if(resizeState==2)
//    {
//        rect_.setBottom(rect_.bottom()-accShiftY);

//    }
//    else if(resizeState==6)
//    {
//        rect_.setLeft(rect_.left()-accShiftX);
//        rect_.setBottom(rect_.bottom()-accShiftY);

//    }
//    else if(resizeState==4)
//        rect_.setLeft(rect_.left()-accShiftX);


//    accShiftX=0;
//    accShiftY=0;

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
