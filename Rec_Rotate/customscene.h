#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>

class customscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit customscene(QObject *parent = 0);
    int selectedTool;
    bool pressed= false;
    QGraphicsView *view;
    QGraphicsItem *item;
    bool draw_item=true;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect=NULL;
    QGraphicsPathItem *mypath;
    double prevX,prevY;
    int w;
    int h;
    QRectF output;
    QList<QGraphicsItem *> group;
    ~customscene();

private:
    QPointF y;
    QPointF yt;
    QPointF rt;
    QPointF origPoint;
    QRectF newrect;
    QPen drawPen;
    QRectF rect1;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
