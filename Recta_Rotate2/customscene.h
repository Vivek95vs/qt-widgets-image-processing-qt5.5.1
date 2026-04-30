#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>
#include "customitem.h"
#include "resizeritem.h"


class customscene : public QGraphicsScene
{
    Q_OBJECT
public:
    customscene();
    enum Mode {NoMode=0,SelectObject,DrawLine,DrawEllipse,DrawRect,DrawFree,DrawAngle,DrawText,DrawCircle,DilineatorMode,ManualMode};
    ~customscene();
    customitem* rectDefault1;
    customitem* rectDefault2;
    customitem* rect1;
    customitem* rect3;
    customitem* rect4;
    customitem* rect5;
    customitem* rect6;
    customitem* rect7;
    customitem* rect8;
    customitem* rect9;
    QList<QPointF>Line_Points,Line_Points1;
    QGraphicsRectItem* centerDefault1;
    QGraphicsRectItem *isocenterRect;
    QGraphicsPixmapItem *pixMap;
    customitem* rotaterect;
    double Fx1,Fx2,Fy1,Fy2,Cx;
    double centerTempX,centerTempY;
    QGraphicsLineItem* line2;
    QList<QList<QGraphicsItem*>> angleList1;
    QList<QList<QGraphicsItem*>> angleList2;
    QGraphicsLineItem* line=NULL;
    double a,b,c,d;
    float rTheta,dTheta=0;
    float isocenterX,isocenterY;
    double prevX, prevY, curX,curY;
    QGraphicsRectItem* rect;
    QPen drawPen;
    int updateangleCount=0;
    float isoDilShiftX, isoDilShiftY;
    double tLX,tLY,tRX,tRY,bRX,bRY,bLX,bLY;
    double ctLX,ctLY,ctRX,ctRY,cbRX,cbRY,cbLX,cbLY;
    double tLX1,tLY1,tRX1,tRY1,bRY1,bRX1,bLX1,bLY1;
    float prevIsoCenterX, prevIsoCenterY;
    double topLeftDiffX, topLeftDiffY, bottomLeftDiffX, bottomLeftDiffY,topRightDiffX, topRightDiffY,bottomRightDiffX, bottomRightDiffY;
    double prevRectPosX,prevRectPosY;
    double centerDilX,centerDilY;
    float curRectPosX,curRectPosY;
    QGraphicsItemGroup *group,*group2,*group3,*group4;

public slots:

    void receiveDrawRectSignal(QRectF* rect, QRectF* rect2, float cTheta, float isoCentreX,float isoCentreY,float p);
    void rotateDrawRect(float rotateStep);
        void setMode(Mode mode);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    Mode sceneMode;
    int tFlag;
    QPointF origPoint;
    QGraphicsTextItem *lineTag;
    float distance1;
    QPointF origPoint1;
    QPointF origPoint2;
    float pixelPitch=1.0;
    bool angleFlag=true;
    resizeritem* rectReSizeItem1;
    resizeritem* rectReSizeItem2;
    resizeritem* rectReSizeItem3;
    QPointF startPoint;
    float isoRectCenterShiftX, isoRectCenterShiftY;
//    float isocenterX,isocenterY;

signals:
    void positionChanged(QPointF,int);
    void LineDrawn(double x1,double y1,double x2,double y2,QPointF pos1,QPointF pos2, QString val);
};

#endif // CUSTOMSCENE_H
