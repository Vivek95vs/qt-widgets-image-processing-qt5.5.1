#ifndef CUSTOMESCENE_H
#define CUSTOMESCENE_H


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include<QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include<QGraphicsEllipseItem>
#include<QGraphicsPathItem>
#include "SizeGripItem.h"
#include "customitemellipse.h"
#include "customitem.h"

struct Drawing
{
    QString type;
    QPointF pos;
    QList<QPointF>pointsList;
    QRectF rect1;
    QPointF posChange;
};

struct returnList
{
    QList<Drawing*> drawingList;
    int n;
};

class customescene:public QGraphicsScene
{
 Q_OBJECT
public:
    customescene();

   // enum Mode { DrawEllipse};
    Drawing *myDrawingA = NULL;
    Drawing *myDrawingB = NULL;
    Drawing *myDrawingC = NULL;

    QGraphicsEllipseItem* ellipnew1 = NULL;
    QGraphicsPathItem* path = NULL;

    enum Mode{NoMode,DrawEllipse};

    void setScene(customescene *sceneA,customescene *sceneB,customescene *sceneC,customescene::Mode mode);


    CustomItemEllipse* ellipseItem1 = NULL; //
//    CustomItemEllipse* ellipseItem2 = NULL; //
//    CustomItemEllipse* ellipseItem3 = NULL; //

//    QGraphicsEllipseItem* ellipMobing1 = NULL;

    Drawing *cbctDrawing;

    void setMode(customescene::Mode mode);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event);

private:

    int tFlag = 0;

    QPointF endPoint;
    QPointF tagPoint;
    QPointF startPoint;

    QPointF origPoint;
    QPointF origPoint1;
    QPointF origPoint2;

    int sceneMode;

    double drawThick;

    int var1;
    int var2;
    int var3;
    int var4;

    QRectF rectCheck;
    QPointF posPoints;
    int mover;

    QRectF rect1;
    QRectF rect2;
    QRectF rect3;

    QGraphicsEllipseItem* ellip = NULL;


    QImage image; //
    QGraphicsPixmapItem *pixMap;
    QGraphicsEllipseItem* ellipsnew2;
    CustomItem *rectItem2=NULL;
    CustomItem *rectItem3=NULL;

//    SizeGripItem* ellipseSizeGripItem;
    QGraphicsEllipseItem* ellipseItem;

    QRectF tempRect;
    QRectF tempRect2;


    SizeGripItem* rectSizeGripItem1=NULL;
    SizeGripItem* rectSizeGripItem2=NULL;
    SizeGripItem* rectSizeGripItem3=NULL;

    QPen drawPen;
    QPen drawPenContour;
    QPen movingPen;
    QPen teztPen;

    float pixelPitch;
    QList<double>PixPitch;



    void DrawRectSlot(QRectF output);

private slots:
    void respondToitem(QRectF rectn,int k);
    void respondToitem1(QRectF rectn, int k);
    void respondToitem2(QRectF rectn, int k);

    void respondToitemChange(QPointF pos);
    void respondToitemChange1(QPointF pos);
    void respondToitemChange2(QPointF pos);

};

#endif // CUSTOMESCENE_H
