// myitem.h

#ifndef MYITEM_H
#define MYITEM_H

#include <QPainter>
#include <QGraphicsItem>

// class for customization
class myitem :public QGraphicsItem
{
public:
    myitem();

    QRectF boundingRect() const;

    // overriding paint()
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    // item state
    bool Pressed;
protected:

private:
    int width;
    int height;
    int Mode;
    qreal dpi;

public:
    void setWidthHeight(int wid,int hei,int mod);
    // overriding mouse events
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYITEM_H
