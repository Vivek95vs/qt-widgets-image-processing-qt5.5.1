#ifndef DRAWIT_H
#define DRAWIT_H

#include <QString>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QRubberBand>
class drawit:public QGraphicsScene
{
public:
    drawit(QWidget *parent);
    int selected;
protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void makeItemsControllable(bool areControllable);
        void onChange(QGraphicsItem *item,bool change);
public:
        QPointF origPoint;
        QPointF origPointr;
        QPointF origPointe;
        QPointF origPointf;
        QGraphicsLineItem *itemtodraw;
        QGraphicsLineItem *itemtodraw1;
        QGraphicsRectItem *itemtodrawrect;
        QGraphicsEllipseItem *itemtodrawellipse;
        QGraphicsPathItem *itemdrawfree;
        QPainterPath p;
        QPointF deletepoint;
        QList<QPointF> rectangle;
        QList<QGraphicsItem*> rt;
        QList<QGraphicsEllipseItem*> elip;
        QList<QGraphicsLineItem*> line;
        QList<QGraphicsPathItem*> path;
        QList<QPointF> pathcoord;
        QGraphicsItem *o;
        QGraphicsView *u;
        bool scale;
        bool pressed;
        QList<QPainterPath> drawnPaths;

        //QRubberBand* _rubberBand;
        void redrawPaths();
};

#endif // DRAWIT_H
