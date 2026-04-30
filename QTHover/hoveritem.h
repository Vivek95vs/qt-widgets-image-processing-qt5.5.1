#ifndef HOVERITEM_H
#define HOVERITEM_H

#include <QGraphicsScene>
#include "QGraphicsSceneHoverEvent"
#include "QHoverEvent"


class Hoveritem : public QGraphicsScene
{
    Q_OBJECT
public:
    Hoveritem();

protected:
    void hoverEnter(QGraphicsSceneHoverEvent *event);
    void hoverLeave(QGraphicsSceneHoverEvent *event);
    void hoverMove(QGraphicsSceneHoverEvent *event);
    bool event(QEvent *event);

};

#endif // HOVERITEM_H
