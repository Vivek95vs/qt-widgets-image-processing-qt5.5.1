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
#include <windows.h>
#include <QtTest/QTest>

extern QRectF GripforFreehand;
extern int sceneModeFree;
bool SizeGripChanged=false;
int SizeGripposition;

extern double xS;
extern double yS;
extern double wS;
extern double hS;

extern bool EnableHandle[8];
QPointF pos1;

SizeGripItem::HandleItem::HandleItem(int positionFlags, SizeGripItem* parent)
    : QGraphicsRectItem(-20, -20, 40, 40, parent),
      positionFlags_(positionFlags),
      parent_(parent)
{
//    qDebug()<<"simply3"<<parent_->rect_;
//    Sleep(500);
    setBrush(QBrush(Qt::lightGray));
    setFlag(ItemIsMovable,true);
    setFlag(ItemSendsGeometryChanges);



}

int SizeGripItem::HandleItem::positionFlags() const
{
    return positionFlags_;

}

QVariant SizeGripItem::HandleItem::itemChange(GraphicsItemChange change,
                                              const QVariant &value)
{

    SizeGripChanged=true;

//    qDebug()<<"simply;";

    //Sleep(2000);
    pos1=value.toPointF();

    QVariant retVal = value;

    if (change == ItemPositionChange)
    {
        retVal = restrictPosition(value.toPointF());
    }
    else if (change == ItemPositionHasChanged)
    {
        QPointF pos = value.toPointF();



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
    }

    SizeGripposition=positionFlags_;

    return retVal;

}

QPointF SizeGripItem::HandleItem::restrictPosition(const QPointF& newPos)
{

    QPointF retVal = pos();

//    qDebug()<<"restrcition";

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

SizeGripItem::SizeGripItem(double x, double y, double w, double h,Resizer* resizer, QGraphicsItem* parent)
    : QGraphicsItem(parent),
      resizer_(resizer)
{

    try
    {
   // qDebug()<<"simply1;"<<rect_;

  //  Sleep(2000);

   // if(sceneModeFree!=0)
   // {
    if (parentItem())
        rect_ = parentItem()->boundingRect();
   // }
//    else if (sceneModeFree==5)
//    {   if (parentItem())
//        rect_.setRect(GripforFreehand.x(),GripforFreehand.y(),GripforFreehand.width(),GripforFreehand.height());
//    }


//    handleItems_.append(new HandleItem(TopLeft, this));
//    handleItems_.append(new HandleItem(Top, this));
//    handleItems_.append(new HandleItem(TopRight, this));
//    handleItems_.append(new HandleItem(Right, this));
//    handleItems_.append(new HandleItem(BottomRight, this));
//    handleItems_.append(new HandleItem(Bottom, this));
//    handleItems_.append(new HandleItem(BottomLeft, this));
//    handleItems_.append(new HandleItem(Left, this));

//        handleItems_.clear();

        if(EnableHandle[0]==true)
        {
            handleItems_.append(new HandleItem(TopLeft, this));
            handleItems_.at(0)->setFlag(QGraphicsItem::ItemIsMovable,true);
        }
        if(EnableHandle[1]==true)
        {
            handleItems_.append(new HandleItem(Top, this));
        }
        if(EnableHandle[2]==true)
            handleItems_.append(new HandleItem(TopRight, this));
        if(EnableHandle[3]==true)
            handleItems_.append(new HandleItem(Right, this));
        if(EnableHandle[4]==true)
            handleItems_.append(new HandleItem(BottomRight, this));
        if(EnableHandle[5]==true)
            handleItems_.append(new HandleItem(Bottom, this));
        if(EnableHandle[6]==true)
            handleItems_.append(new HandleItem(BottomLeft, this));
        if(EnableHandle[7]==true)
            handleItems_.append(new HandleItem(Left, this));






    updateHandleItemPositions();
    }
    catch(std::exception &err)
    {
        qDebug()<<"SizeGrip"<<err.what();
    }
}

SizeGripItem::~SizeGripItem()
{
    if (resizer_)
        delete resizer_;
}

QRectF SizeGripItem::boundingRect() const
{


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

//    if (sceneModeFree==5)
//    {
//        {   if (parentItem())
//            rect_.setWidth(GripforFreehand.width());
//            rect_.setHeight(GripforFreehand.height());
//        }
//    }
//    qDebug()<<"simply2;"<<rect_;

 //   Sleep(2000);
    if (resizer_)
    {

        (*resizer_)(parentItem(), rect_);
        //qDebug()<<"simply2;"<<rect_;
        updateHandleItemPositions();

    }

}

void SizeGripItem::updateHandleItemPositions()
{

    try
    {
    emit itemChanged(rect_,1);
    //rect_.setRect(GripforFreehand.x(),GripforFreehand.y(),GripforFreehand.width(),GripforFreehand.height());

//    qDebug()<<"simply4;";
  //  Sleep(2000);
    foreach (HandleItem* item, handleItems_)
    {
        item->setFlag(ItemSendsGeometryChanges, false);


      //  qDebug()<<"rect_"<<rect_;
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

        item->rect().setWidth(wS);
        item->rect().setHeight(hS);

//         qDebug()<<"simply5;";

        item->setFlag(ItemSendsGeometryChanges, true);


    }
    }
    catch(std::exception &err)
    {
         qDebug()<<"SizeGrip"<<err.what();
    }



}
