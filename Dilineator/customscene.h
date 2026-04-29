#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include "SizeGripItem.h"
#include "customitem.h"
#include "customitemellipse.h"
#include "textitemfocuswatcher.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include<QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include<QGraphicsEllipseItem>
#include<QGraphicsPathItem>
#include<QGraphicsTextItem>
#include<QTextDocument>


struct Drawing
{
    QString type;
    QPointF pos;
    QList<QPointF> pointsList;
    QRectF rect1;
    QString tag;
    QPointF posChange;
};

struct returnList
{
    QList<Drawing*> drawingList;
    int n;
};
/*!
 * \brief The CustomScene class a scene to draw.
 * \author {aaruni,saimahesh}
 */
class CustomScene:public QGraphicsScene
{
     Q_OBJECT
public:
    CustomScene();

    enum Mode {NoMode=0, SelectObject, DrawLine,DrawEllipse,DrawRect,DrawFree
                ,DrawText,DrawAngle,TumorMode,DrawCircle,ManualMode,DilineatorMode,DrawContour,Maximize,Drawrectcbct};
    ~CustomScene();

    QList<QPointF> pntlistxy;//anoop
    Drawing *myDrawingA;
    Drawing *myDrawingB;
    Drawing *myDrawingC;
     Drawing *cbctDrawing;
    int RoiDrawn=0;
    double prevDilX=0,prevDilY=0,curDilX,curDilY, centerDilX,centerDilY,centerTempX,centerTempY;

        double topLeftDiffX, topLeftDiffY, bottomLeftDiffX, bottomLeftDiffY,topRightDiffX, topRightDiffY,bottomRightDiffX, bottomRightDiffY;

        double prevRectPosX,prevRectPosY;
        double tLX,tLY,tRX,tRY,bRX,bRY,bLX,bLY;
        double tLX1,tLY1,tRX1,tRY1,bRY1,bRX1,bLX1,bLY1;


        float prevIsoCenterX, prevIsoCenterY,curRectPosX,curRectPosY;

        float isoDilShiftX, isoDilShiftY;

        double ctLX,ctLY,ctRX,ctRY,cbRX,cbRY,cbLX,cbLY;

        double prevX, prevY, curX,curY;
        CustomItem* rectDefault1;
        QGraphicsRectItem* centerDefault1;

        bool sceneStatus=1;

        void receiveDrawJawsSignal(QRectF *rect, float cTheta, float isoCentreX, float isoCentreY, float p);

        void receiveDrawRectSignalinEnhancement(QRectF *rect, QRectF *rect2, float cTheta, float isoCentreX, float isoCentreY, float p);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    Mode sceneMode;
    Mode sceneMode11;//added for demo
    QPointF origPoint;
    QPointF origPoint1;
    QPointF origPoint2;

    QList<QPointF> CtPointList;

    QPointF startPoint;

    QGraphicsRectItem *isocenterRect;

    float isoRectCenterShiftX, isoRectCenterShiftY;

    float isocenterX,isocenterY;

    QGraphicsLineItem* line;
    QGraphicsLineItem* line2;
    QGraphicsRectItem* rect;

    QGraphicsEllipseItem* circle;
 Drawing *myDrawing;
 QList<float> statsOfRectangle(QImage image, QRectF geometry);
    QGraphicsEllipseItem* ellip;
    QGraphicsPathItem* path;
    QPointF lastPoint;
    QPainterPath *paintPath;
    QGraphicsTextItem *text;
    bool angleFlag=true;
    QGraphicsTextItem *lineTag;
    QGraphicsTextItem *angleTag;
    QGraphicsTextItem *circleTag;

    QGraphicsTextItem *ellipTag;
    QGraphicsTextItem *rectTag;
    QGraphicsItemGroup *group;
    QGraphicsPixmapItem *pixMap;
    float angle;
    QImage image;

    int tFlag=0;

    QGraphicsEllipseItem* ellipnew1;
    QGraphicsEllipseItem* ellipnew2;

    QGraphicsRectItem *rectMoving1;
    QGraphicsRectItem *rectMoving2;
    QGraphicsRectItem *rectMoving3;


    QGraphicsEllipseItem *ellipMoving1;
    QGraphicsPathItem* pathMoving;

    SizeGripItem* ellipseSizeGripItem;
    QGraphicsEllipseItem* ellipseItem;
    QGraphicsLineItem *lineItem;
    SizeGripItem *lineSizeGripItem;

//    QGraphicsRectItem* rectItem;
//    QGraphicsRectItem *rectItem1;
//    QGraphicsRectItem *rectItem2;

    QGraphicsRectItem* rectnew1 ;
    QGraphicsRectItem* rectnew2 ;
    QGraphicsRectItem* rectnew3 ;


    CustomItem* rectItem1;
    CustomItem *rectItem2;
    CustomItem *rectItem3;

    QRectF rect1;
    QRectF rect2;
    QRectF rect3;

    SizeGripItem* rectSizeGripItem1;
    SizeGripItem* rectSizeGripItem2;
    SizeGripItem* rectSizeGripItem3;

    CustomItemEllipse* ellipseItem1;
    CustomItemEllipse *ellipseItem2;
    CustomItemEllipse *ellipseItem3;


    SizeGripItem* ellipseSizeGripItem1;
    SizeGripItem* ellipseSizeGripItem2;
    SizeGripItem* ellipseSizeGripItem3;

//    int sceneChange = 0;
    const  float PI= 3.14159F;
    QPen drawPen;
    QPen movingPen;
    QPen textPen;
    float pixelPitch;
    float slope=2000.0/255.0,intercept=-1000.0;

    CustomItem* rectDefaultTemp;
    CustomItem* rectDefault2;
//    QGraphicsRectItem* centerDefault1;
    float rTheta,dTheta=0;    
    QList<float> statsOfEllipse(QImage image, QRectF geometry);    
    void RotatingDilPositions(QPointF curPoints);    
    void resetDilineator(double theta);

public slots:
 void updateText();
    void setMode(Mode mode);
    void setScene(CustomScene *sceneA, CustomScene *sceneB, CustomScene::Mode mode, int c, int m);
    void setScene(CustomScene *sceneA,CustomScene *sceneB,CustomScene *sceneC,CustomScene::Mode mode,int c,int m);
    void setpixelPitch(float realSize);
    Mode getCurrMode();
    Mode getMode(QString type);
    void setImage(QImage imag);
    void setConversionVals(float a,float b);

    void DrawRectSlot(QRectF output);

    void respondToitem(QRectF rectn,int k);
    void respondToitem1(QRectF rectn, int k);
    void respondToitem2(QRectF rectn, int k);
    void respondToDilineatorResize(QRectF rect12,int k);

    void respondToitemChange(QPointF pos);
    void respondToitemChange1(QPointF pos);
    void respondToitemChange2(QPointF pos);

    QList<Drawing*>redrawRect();
    returnList* returnDrawing();
    float lineAngle(const QPointF start,const QPointF end);

    void rotateDrawRect(float rotateStep, QRectF *jawRect);

    void receiveDrawRectSignal(QRectF* rect, QRectF* rect2, float cTheta, float isoCentreX,float isoCentreY,float p);
 void ReceiveCBCTRedraw(QMap<int, QList<Drawing*>> cbctMap, int sliceNo);

signals:
 void drawn(Drawing *myDrawing);
    void positionChanged(QPointF,int);
    void measurementDrawn(QGraphicsItem *);
    void mouseDoubleClicked();
    void UpdatePlannedVlue(QList<double>PlannedcalValues);
    void SendToDrawContour(QList <QPointF> PointsList,QGraphicsPathItem *pathItem);
    void UpdatecbctDrawing(Drawing *myDrawing);
      void  UpdateOutText();


};

#endif // CUSTOMSCENE_H
