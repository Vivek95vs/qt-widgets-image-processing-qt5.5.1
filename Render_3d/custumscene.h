#ifndef CUSTUMSCENE_H
#define CUSTUMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "QVTKWidget.h"


class custumscene : public QVTKWidget
{
     Q_OBJECT
public:
    explicit custumscene(QObject *parent = 0);

    int selectedTool;
    bool pressed= false;
    QVTKWidget *scene;
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

//    QGraphicsPixmapItem *p1=NULL;
//    QGraphicsPixmapItem *p2=NULL;
    ~custumscene();

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
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CUSTUMSCENE_H
