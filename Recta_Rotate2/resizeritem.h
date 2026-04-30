#ifndef RESIZERITEM_H
#define RESIZERITEM_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>

#include "customitem.h"


class resizeritem :public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    enum
    {
        Top         = 0x1,
        Bottom      = 0x2,
        Left        = 0x4,
        TopLeft     = Top | Left,
        BottomLeft  = Bottom | Left,
        Right       = 0x8,
        TopRight    = Top | Right,
        BottomRight = Bottom | Right
    };

    class HandleItem : public QGraphicsRectItem
    {

    public:
        HandleItem(int positionFlags, resizeritem* parent);
        int positionFlags() const;


    protected:
        virtual QVariant itemChange(GraphicsItemChange change,
                                    const QVariant &value);

    private:
        QPointF restrictPosition(const QPointF& newPos);

        int positionFlags_;
        resizeritem* parent_;

    };

public:
    class Resizer
    {
    public:
        virtual void operator()(QGraphicsItem* item,
                                const QRectF& rect) = 0;
    };

    resizeritem(Resizer* resizer = 0, QGraphicsItem* parent = 0);
    virtual ~resizeritem();
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget = 0);
    void setTopLeft(const QPointF& pos);
    void setTop(qreal y);
    void setTopRight(const QPointF& pos);
    void setRight(qreal x);
    void setBottomRight(const QPointF& pos);
    void setBottom(qreal y);
    void setBottomLeft(const QPointF& pos);
    void setLeft(qreal x);

private:
    void doResize();
    void updateHandleItemPositions();


    QList<HandleItem*> handleItems_;
    QRectF rect_;
    Resizer* resizer_;

signals:
    void itemChanged(QRectF,int);
    void itemChanged1(QRectF);

};

#endif // RESIZERITEM_H
