#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsPixmapItem>

class customscene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit customscene(QObject *parent = 0);
    int selectedDraw;
    bool pressed= false;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsItem *item;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect=NULL;
    bool draw_item=true;
    QGraphicsPathItem *mypath;
    double prevX,prevY;
    int w;
    int h;
    QRectF output;
    QList<QGraphicsItem *> group;
    int itemTrackAP=-1;
    QPointF posChanged = QPointF(0,0);
    ~customscene();

private:
    QPointF y;
    QPointF yt;
    QPointF rt;
    QPointF origPoint;
    QRectF newrect;
    QPen drawPen;

    QRectF rect1;
//    QRectF rect1;
    QString type;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
