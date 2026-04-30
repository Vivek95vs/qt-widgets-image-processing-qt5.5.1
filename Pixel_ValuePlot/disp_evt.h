#ifndef DISP_EVT_H
#define DISP_EVT_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsPixmapItem>

class Disp_Evt : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Disp_Evt(QObject *parent = 0);
    int selectedTool;
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
    QRectF newrect;

//    QGraphicsPixmapItem *p1=NULL;
//    QGraphicsPixmapItem *p2=NULL;
    ~Disp_Evt();

private:
    QPointF y;
    QPointF yt;
    QPointF rt;
    QPointF origPoint;

    QPen drawPen;

    QRectF rect1;
//    QRectF rect1;
    QString type;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void positionLeftchanges();
    void positionRightchanges();
    void positionUpchanges();
    void positionDownchanges();
};

#endif // DISP_EVT_H
