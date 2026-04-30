#ifndef RULER_ITEM_H
#define RULER_ITEM_H

#include <QPainter>
#include <QGraphicsItem>

class Ruler_Item : public QGraphicsItem
{
public:
    Ruler_Item();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool pressed;

private:

    int width=3072;
    int height=3072;
    int Mode;
    qreal dpi;

public:
    void setwidthHeight(int wid,int hei,int mod);
};

#endif // RULER_ITEM_H
