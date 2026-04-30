#include "customscene.h"
#include "applogger.h"
customscene *scene1;
customscene *scene2;
customscene *scene3;

customscene::Mode sceneMode1;
int count;
int count1=0;
int count2=0;

int widthtoscene;
float trackDistanceX,trackDistanceY;
bool checkdeletebeam;
int itemTrackAP=-1;
int itemTrackAP1=-1;
int itemTrackLAT=-1;
int itemTrackLAT1=-1;
float imgSizeBoundary=3072;

int tMode;//1 for 2D and 0 for 3D
float imaginPixelSpacing=0.1;
float f;
float f1;
float pix;
bool pressed=false;
bool pressedMovable=false;
int receiveangleCount=0;
float gCenterX,gCenterY,gTheta;
int flagDrawn;

double boundX=0;
double boundY=0;
double boundZ=0;

double accPosXAP=0,accPosYAP=0;
double accPosXLAT=0,accPosYLAT=0;
QPointF prevPosChangedAP=QPointF(0,0);
QPointF prevPosChangedLAT=QPointF(0,0);

double origAccPosXAP,origAccPosYAP;
double origAccPosXLAT,origAccPosYLAT;

QPointF posChanged = QPointF(0,0);
//int resizeState;
//int resizeUpdate;

// for resizer in rectangle items
class RectResizer : public resizeritem::Resizer
{
public:
    virtual void operator()(QGraphicsItem* item, const QRectF& rect)
    {
        //        QGraphicsRectItem* rectItem =
        //                dynamic_cast<QGraphicsRectItem*>(item);
        customitem* rectItem =
                dynamic_cast<customitem*>(item);

        if (rectItem)
        {
            rectItem->setRect(rect);
        }
    }
};

customscene::customscene()
{

}

customscene::~customscene()
{

}
void customscene::receiveDrawRectSignal(QRectF *rect, QRectF *rect2, float cTheta, float isoCentreX, float isoCentreY, float p)
{
    f=isoCentreX;
    f1=isoCentreY;
    pix=p;
    rectDefault1 =new customitem();
    rectDefault1->setRect(*rect);
    rectDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));
    rectDefault1->setRotation((qreal)cTheta);
    rectDefault1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
    this->addItem(rectDefault1);
    rectDefault1->resetTransform();
    rectDefault1->show();

//    rect1=new customitem();
//    rect1->setParentItem(rectDefault1);
//    rect1->setRect(rectDefault1->sceneBoundingRect().x(),rectDefault1->sceneBoundingRect().y(),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//    rect1->setFlag(QGraphicsItem::ItemIsMovable,false);
//    rect1->setBrush(Qt::lightGray);
//    rect1->setRotation((qreal)cTheta);
//    rect1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    this->addItem(rect1);
//    rect1->show();

//    rect3=new customitem();
//    rect3->setParentItem(rectDefault1);
//    rect3->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()-(1.39/imaginPixelSpacing),rectDefault1->sceneBoundingRect().y(),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//    rect3->setFlag(QGraphicsItem::ItemIsMovable,false);
//    rect3->setBrush(Qt::lightGray);
//    rect3->setRotation((qreal)cTheta);
//    rect3->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    this->addItem(rect3);
//    rect3->show();

//    rect4=new customitem();
//    rect4->setParentItem(rectDefault1);
//    rect4->setRect(rectDefault1->sceneBoundingRect().x(),rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()-(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//    rect4->setFlag(QGraphicsItem::ItemIsMovable,false);
//    rect4->setBrush(Qt::lightGray);
//    rect4->setRotation((qreal)cTheta);
//    rect4->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    this->addItem(rect4);
//    rect4->show();

//    rect5=new customitem();
//    rect5->setParentItem(rectDefault1);
//    rect5->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()-(1.39/imaginPixelSpacing),rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()-(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//    rect5->setFlag(QGraphicsItem::ItemIsMovable,false);
//    rect5->setBrush(Qt::lightGray);
//    rect5->setRotation((qreal)cTheta);
//    rect5->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    this->addItem(rect5);
//    rect5->show();

//    rect6=new customitem();
//    rect6->setParentItem(rectDefault1);
//    rect6->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()/2,rectDefault1->sceneBoundingRect().y(),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//    rect6->setFlag(QGraphicsItem::ItemIsMovable,false);
//    rect6->setBrush(Qt::lightGray);
//    rect6->setRotation((qreal)cTheta);
//    rect6->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    this->addItem(rect6);
//    rect6->show();

//    rect7=new customitem();
//    rect7->setParentItem(rectDefault1);
//    rect7->setRect(rectDefault1->sceneBoundingRect().x(),rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()/2,(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//    rect7->setFlag(QGraphicsItem::ItemIsMovable,false);
//    rect7->setBrush(Qt::blue);
//    rect7->setRotation((qreal)cTheta);
//    rect7->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    this->addItem(rect7);
//    rect7->show();

//    rect8=new customitem();
//    rect8->setParentItem(rectDefault1);
//    rect8->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()-(1.39/imaginPixelSpacing),rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()/2,(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//    rect8->setFlag(QGraphicsItem::ItemIsMovable,false);
//    rect8->setBrush(Qt::lightGray);
//    rect8->setRotation((qreal)cTheta);
//    rect8->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    this->addItem(rect8);
//    rect8->show();

//    rect9=new customitem();
//    rect9->setParentItem(rectDefault1);
//    rect9->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()/2,rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()-(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//    rect9->setFlag(QGraphicsItem::ItemIsMovable,false);
//    rect9->setBrush(Qt::lightGray);
//    rect9->setRotation((qreal)cTheta);
//    rect9->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    this->addItem(rect9);
//    rect9->show();

    rectReSizeItem1 = new resizeritem(new RectResizer, rectDefault1);

    rectDefault2=new customitem();
    rectDefault2->setRect(*rect2);
    rectDefault2->setRotation((qreal)cTheta);
    rectDefault2->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
    rectDefault2->setPen(QPen(Qt::green,(0.139*5)/(imaginPixelSpacing)));
    rectDefault2->setFlag(QGraphicsItem::ItemIsMovable,false);
    this->addItem(rectDefault2);
    rectDefault2->show();

//    rotaterect =new customitem();
//    rotaterect->setRect(rect1->sceneBoundingRect().topLeft().x(),rect1->sceneBoundingRect().topLeft().y(),rect3->sceneBoundingRect().topRight().x()-rect1->sceneBoundingRect().topLeft().x(),rect5->sceneBoundingRect().bottomRight().y()-rect3->sceneBoundingRect().topRight().y());
//    rotaterect->setRotation((qreal)cTheta);
//    rotaterect->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    rotaterect->setPen(QPen(Qt::yellow,(0.139*5)/(imaginPixelSpacing)));
//    rotaterect->setFlag(QGraphicsItem::ItemIsMovable,false);


    /*Iso Center*/
    isocenterRect=new QGraphicsRectItem();
    isocenterRect->setRect(isoCentreX/p-(1.39/(imaginPixelSpacing*2)),isoCentreY/p-(1.39/(imaginPixelSpacing*2)),(1.39/imaginPixelSpacing)/**2*/,(1.39/imaginPixelSpacing)/**2*/);
    isocenterRect->setPen(QPen(Qt::green,(0.139*5)/(imaginPixelSpacing)));
    isocenterRect->setBrush(QBrush(Qt::green));
//    isocenterRect->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
    this->addItem(isocenterRect);

    /*Dilineator Centre Point*/
    centerDefault1 = new QGraphicsRectItem();
//    centerDefault1->setParentItem(rectDefault1);
    centerDefault1->setRect(rectDefault1->rect().center().rx()-(1.39/(imaginPixelSpacing*2)),rectDefault1->rect().center().ry()-(1.39/(imaginPixelSpacing*2)),(1.39/imaginPixelSpacing)/**2*/,(1.39/imaginPixelSpacing)/**2*/);
//    centerDefault1->setRect(rectDefault1->boundingRect().x()+rectDefault1->boundingRect().width()/2,rectDefault1->boundingRect().y()+rectDefault1->boundingRect().height()/2,15,15);
    centerDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));
//    rectDefault2->setFlag(QGraphicsItem::ItemIsMovable,false);
    centerDefault1->setBrush(QBrush(Qt::red));

    centerDefault1->setRotation((qreal)cTheta);
    centerDefault1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
    centerDefault1->resetTransform();
    this->addItem(centerDefault1);

//    Fx1 = (rect7->rect().x()-isoCentreX/p)*p;
//    Fx2 = isocenterRect->rect().y();

//    cen1= rectDefault1->rect().y();
//    cen2= centerDefault1->rect().y();
//    qDebug()<<"center x"<<cen1;
//    qDebug()<<"center Y"<<centerDefault1->rect().y();
//    qDebug()<<"iso Y"<<isoCentreX/p;
//    qDebug()<<"iso"<<isocenterRect->rect().x();
//    qDebug()<<"rect"<<rect7->rect().x();
//    qDebug()<<"Value"<<Fx1;

    cTheta=cTheta *(3.14/180);//convert to radian

    float tempX=rect->topLeft().rx()*p-isoCentreX;
    float tempY=rect->topLeft().ry()*p-isoCentreY;

    tLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    tLY = tempX*sin(cTheta)+tempY*cos(cTheta);

    tLX = (tLX+isoCentreX)/p;
    tLY = (tLY+isoCentreY)/p;

    tempX= rect->topRight().rx()*p-isoCentreX;
    tempY= rect->topRight().ry()*p-isoCentreY;

    tRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    tRY = tempX*sin(cTheta)+tempY*cos(cTheta);

    tRX = (tRX+isoCentreX)/p;
    tRY = (tRY+isoCentreY)/p;

    tempX = rect->bottomLeft().rx()*p-isoCentreX;
    tempY = rect->bottomLeft().ry()*p-isoCentreY;

    bLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    bLY = tempX*sin(cTheta)+tempY*cos(cTheta);


    bLX = (bLX+isoCentreX)/p;
    bLY = (bLY+isoCentreY)/p;

    tempX = rect->bottomRight().rx()*p-isoCentreX;
    tempY = rect->bottomRight().ry()*p-isoCentreY;

    bRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    bRY = tempX*sin(cTheta)+tempY*cos(cTheta);

    bRX = (bRX+isoCentreX)/p;
    bRY = (bRY+isoCentreY)/p;

    tempX = rectDefault1->sceneBoundingRect().center().rx()*p-isoCentreX;
    tempY = rectDefault1->sceneBoundingRect().center().ry()*p-isoCentreY;

    centerTempX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    centerTempY = tempX*sin(cTheta)+tempY*cos(cTheta);

    centerTempX = (centerTempX+isoCentreX)/p;
    centerTempY = (centerTempY+isoCentreY)/p;

    isocenterX = isoCentreX/p;//in pixels
    isocenterY = isoCentreY/p;//in pixels

    isoRectCenterShiftX = centerTempX-isoCentreX/p;
    isoRectCenterShiftY = centerTempY-isoCentreY/p;

    ctLX = rect->topLeft().rx();
    ctLY = rect->topLeft().ry();
    ctRX = rect->topRight().rx();
    ctRY = rect->topRight().ry();
    cbLX = rect->bottomLeft().rx();
    cbLY = rect->bottomLeft().ry();
    cbRX = rect->bottomRight().rx();
    cbRY = rect->bottomRight().ry();


//    calculating initial Dilineator Center

    float initCenterX,initCenterY;
    cTheta=-cTheta;
    tempX = centerTempX*p-isoCentreX;
    tempY = centerTempY*p-isoCentreY;

    initCenterX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    initCenterY = tempX*sin(cTheta)+tempY*cos(cTheta);

    initCenterX = (initCenterX+isoCentreX)/p;
    initCenterY = (initCenterY+isoCentreY)/p;

    if(!((tRX==tLX)&&(tRY==tLY)))
       rTheta = -cTheta*(180/3.14); // rTheta = atan((tRY-tLY)/(tRX-tLX))*(180/3.14);
    else
        rTheta=0;

    qDebug() <<"RotateAngle "<<rTheta;

    gCenterX = isocenterX;
    gCenterY = isocenterY;
    gTheta = rTheta;

    /*Back up*/
    prevIsoCenterX = isocenterX; //Creating a copy of my initial isocenter
    prevIsoCenterY = isocenterY;

}

void customscene::rotateDrawRect(float rotateStep)
{
    isoDilShiftX = centerTempX-isocenterX; // Shift btw initial isocenter and current DilCenter in pixels
    isoDilShiftY = centerTempY-isocenterY;

    /*Changing Iso Centre*/
    isocenterX=centerTempX;
    isocenterY=centerTempY;

    float cTheta = -rTheta*(3.14/180);


    float tempX = tLX-isocenterX;
    float tempY = tLY-isocenterY;

    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

    ctLX = ctLX+isocenterX;
    ctLY = ctLY+isocenterY;

    tempX = tRX-isocenterX;
    tempY = tRY-isocenterY;

    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

    ctRX = ctRX+isocenterX;
    ctRY = ctRY+isocenterY;

    tempX = bLX-isocenterX;
    tempY = bLY-isocenterY;

    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

    cbLX = cbLX+isocenterX;
    cbLY = cbLY+isocenterY;

    tempX = bRX-isocenterX;
    tempY = bRY-isocenterY;

    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

    cbRX = cbRX+isocenterX;
    cbRY = cbRY+isocenterY;


    dTheta = rotateStep;//rotation step
    cTheta = (dTheta+rTheta)*(3.14/180);

    tempX = ctLX-isocenterX;
    tempY = ctLY-isocenterY;

    tLX1 = tempX*cos(cTheta)+tempY*sin(-cTheta);
    tLY1 = tempX*sin(cTheta)+tempY*cos(cTheta);

    tLX1 = tLX1+isocenterX;
    tLY1 = tLY1+isocenterY;

    tempX = ctRX-isocenterX;
    tempY = ctRY-isocenterY;

    tRX1 = tempX*cos(cTheta)+tempY*sin(-cTheta);
    tRY1 = tempX*sin(cTheta)+tempY*cos(cTheta);

    tRX1 = tRX1+isocenterX;
    tRY1 = tRY1+isocenterY;

    tempX = cbLX-isocenterX;
    tempY = cbLY-isocenterY;

    bLX1 = tempX*cos(cTheta)+tempY*sin(-cTheta);
    bLY1 = tempX*sin(cTheta)+tempY*cos(cTheta);

    bLX1 = bLX1+isocenterX;
    bLY1 = bLY1+isocenterY;

    tempX = cbRX-isocenterX;
    tempY = cbRY-isocenterY;

    bRX1 = tempX*cos(cTheta)+tempY*sin(-cTheta);
    bRY1 = tempX*sin(cTheta)+tempY*cos(cTheta);

    bRX1 = bRX1+isocenterX;
    bRY1 = bRY1+isocenterY;

//    if(tLX1>1 && tLX1<3071 && tLY1>1 && tLY1<3071 && tRX1>1 && tRX1<3071 && tRY1>1 && tRY1<3071 && bLX1>1 && bLX1<3071 && bLY1>1 && bLY1<3071 && bRX1>1 && bRX1<3071 && bRY1>1 && bRY1<3071)
//    {
        delete rectDefault1;
        rectDefault1=NULL;
        rectDefault1= new customitem();
        this->addItem(rectDefault1);

        rectDefault1->setRect(ctLX,ctLY,cbRX-ctLX,cbRY-ctLY);
        rectDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));

        rectDefault1->setRotation((qreal)cTheta*(180/3.14));
        rectDefault1->setTransformOriginPoint(isocenterX,isocenterY);
        rectDefault1->setFlag(QGraphicsItem::ItemIsMovable,true);

        rectDefault1->resetTransform();
        rectDefault1->show();

//        delete rect1;
//        rect1=NULL;
//        rect1=new customitem();
//        rect1->setParentItem(rectDefault1);
//        rect1->setRect(rectDefault1->sceneBoundingRect().x(),rectDefault1->sceneBoundingRect().y(),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//        rect1->setFlag(QGraphicsItem::ItemIsMovable,false);
//        rect1->setBrush(Qt::lightGray);
//        rect1->setRotation((qreal)cTheta*(180/3.14));
//        rect1->setTransformOriginPoint(isocenterX,isocenterY);
//        rect1->setTransformOriginPoint(isocenterX,isocenterY);
//        this->addItem(rect1);
//        rect1->show();

//        delete rect3;
//        rect3=NULL;
//        rect3=new customitem();
//        rect3->setParentItem(rectDefault1);
//        rect3->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()-(1.39/imaginPixelSpacing),rectDefault1->sceneBoundingRect().y(),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//        rect3->setFlag(QGraphicsItem::ItemIsMovable,false);
//        rect3->setBrush(Qt::lightGray);
//        rect3->setRotation((qreal)cTheta*(180/3.14));
//        rect3->setTransformOriginPoint(isocenterX,isocenterY);
//        this->addItem(rect3);
//        rect3->show();

//        delete rect4;
//        rect4=NULL;
//        rect4=new customitem();
//        rect4->setParentItem(rectDefault1);
//        rect4->setRect(rectDefault1->sceneBoundingRect().x(),rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()-(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//        rect4->setFlag(QGraphicsItem::ItemIsMovable,false);
//        rect4->setBrush(Qt::lightGray);
//        rect4->setRotation((qreal)cTheta*(180/3.14));
//        rect4->setTransformOriginPoint(isocenterX,isocenterY);
//        this->addItem(rect4);
//        rect4->show();

//        delete rect5;
//        rect5=NULL;
//        rect5=new customitem();
//        rect5->setParentItem(rectDefault1);
//        rect5->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()-(1.39/imaginPixelSpacing),rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()-(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//        rect5->setFlag(QGraphicsItem::ItemIsMovable,false);
//        rect5->setBrush(Qt::lightGray);
//        rect5->setRotation((qreal)cTheta*(180/3.14));
//        rect5->setTransformOriginPoint(isocenterX,isocenterY);
//        this->addItem(rect5);
//        rect5->show();

//        delete rect6;
//        rect6=NULL;
//        rect6=new customitem();
//        rect6->setParentItem(rectDefault1);
//        rect6->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()/2,rectDefault1->sceneBoundingRect().y(),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//        rect6->setFlag(QGraphicsItem::ItemIsMovable,false);
//        rect6->setBrush(Qt::lightGray);
//        rect6->setRotation((qreal)cTheta*(180/3.14));
//        rect6->setTransformOriginPoint(isocenterX,isocenterY);
//        this->addItem(rect6);
//        rect6->show();

//        delete rect7;
//        rect7=NULL;
//        rect7=new customitem();
//        rect7->setParentItem(rectDefault1);
//        rect7->setRect(rectDefault1->sceneBoundingRect().x(),rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()/2,(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//        rect7->setFlag(QGraphicsItem::ItemIsMovable,false);
//        rect7->setBrush(Qt::blue);
//        rect7->setRotation((qreal)cTheta*(180/3.14));
//        rect7->setTransformOriginPoint(isocenterX,isocenterY);
//        this->addItem(rect7);
//        rect7->show();

//        delete rect8;
//        rect8=NULL;
//        rect8=new customitem();
//        rect8->setParentItem(rectDefault1);
//        rect8->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()-(1.39/imaginPixelSpacing),rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()/2,(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//        rect8->setFlag(QGraphicsItem::ItemIsMovable,false);
//        rect8->setBrush(Qt::lightGray);
//        rect8->setRotation((qreal)cTheta*(180/3.14));
//        rect8->setTransformOriginPoint(isocenterX,isocenterY);
//        this->addItem(rect8);
//        rect8->show();

//        delete rect9;
//        rect9=NULL;
//        rect9=new customitem();
//        rect9->setParentItem(rectDefault1);
//        rect9->setRect(rectDefault1->sceneBoundingRect().x()+rectDefault1->sceneBoundingRect().width()/2,rectDefault1->sceneBoundingRect().y()+rectDefault1->sceneBoundingRect().height()-(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing),(1.39/imaginPixelSpacing));
//        rect9->setFlag(QGraphicsItem::ItemIsMovable,false);
//        rect9->setBrush(Qt::lightGray);
//        rect9->setRotation((qreal)cTheta*(180/3.14));
//        rect9->setTransformOriginPoint(isocenterX,isocenterY);
//        this->addItem(rect9);
//        rect9->show();


        delete centerDefault1;
        centerDefault1=NULL;

        centerDefault1 = new QGraphicsRectItem();
        this->addItem(centerDefault1);
//        centerDefault1->setParentItem(rectDefault1);
        centerDefault1->setRect(isocenterX-(1.39/(imaginPixelSpacing*2)),isocenterY-(1.39/(imaginPixelSpacing*2)),(1.39/imaginPixelSpacing)/**2*/,(1.39/imaginPixelSpacing)/**2*/);
        centerDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));
        centerDefault1->setBrush(QBrush(Qt::red));
        centerDefault1->setRotation((qreal)cTheta*(180/3.14));
        centerDefault1->setTransformOriginPoint(isocenterX,isocenterY);
        centerDefault1->resetTransform();
        centerDefault1->show();

        tempX = ctLX-isocenterX;
        tempY = ctLY-isocenterY;

        tLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
        tLY = tempX*sin(cTheta)+tempY*cos(cTheta);

        tLX = tLX+isocenterX;
        tLY = tLY+isocenterY;

        tempX = ctRX-isocenterX;
        tempY = ctRY-isocenterY;

        tRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
        tRY = tempX*sin(cTheta)+tempY*cos(cTheta);

        tRX = tRX+isocenterX;
        tRY = tRY+isocenterY;

        tempX = cbLX-isocenterX;
        tempY = cbLY-isocenterY;

        bLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
        bLY = tempX*sin(cTheta)+tempY*cos(cTheta);

        bLX = bLX+isocenterX;
        bLY = bLY+isocenterY;

        tempX = cbRX-isocenterX;
        tempY = cbRY-isocenterY;

        bRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
        bRY = tempX*sin(cTheta)+tempY*cos(cTheta);

        bRX = bRX+isocenterX;
        bRY = bRY+isocenterY;

        rTheta = rTheta+dTheta;
        qDebug() <<"RotateStepAngle "<<rTheta;

        AppLogger::Instance()->write("Rotateangle");


        gCenterX = isocenterX;
        gCenterY = isocenterY;


        if(rTheta<0)
            rTheta=(rTheta+360);
        if(rTheta>360)
            rTheta=rTheta-360;

        double pixelPitch = imaginPixelSpacing;
        //    }
}

void customscene::setMode(customscene::Mode mode)
{
    sceneMode = mode;

    QGraphicsView::DragMode vMode = QGraphicsView::NoDrag;
    if(mode == SelectObject)
    {
        //makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
    }

}

void customscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode==customscene::Mode::NoMode && checkdeletebeam==1)
    {   /*checkdeletebeam=0;*/
        return;

        pressed = true;
    }

    if(sceneMode!=DrawAngle)
     {
         if(angleList1.length()!=angleList2.length())
         {
             this->removeItem(angleList1.at(angleList1.length()-1).at(0));
             this->removeItem(angleList1.at(angleList1.length()-1).at(1));
             angleList1.removeAt((angleList1.length()-1));
             this->angleFlag=true;
             this->line=0;
             this->line2=0;
         }
     }

    if (event->button() != Qt::LeftButton ){
        return;
    }

    pressed = true;

    origPoint = event->scenePos();
    startPoint = event->scenePos();

    trackDistanceX=0;
    trackDistanceY=0;

    tFlag=0;

//    if(event->button()!=Qt::LeftButton)
//        return;
//    pressed=true;
//    if(sceneMode==this->DrawText)
    if(sceneMode==9)
    {
        origPoint1 =event->scenePos();
    qDebug()<<"origPoint"<<event->scenePos();
//    drawPen=QPen(Qt::blue,2*(0.139/pixelPitch),Qt::SolidLine);

//    if(receiveangleCount!=updateangleCount)
//    {
//        updateangleCount=receiveangleCount;
//        angleFlag=true;
//        line2=0;
//    }
    rectDefault1->setFlag(QGraphicsItem::ItemIsMovable,true);
    prevX = event->scenePos().rx();
    prevY = event->scenePos().ry();
    dTheta=0;

    topLeftDiffX      = tLX-rectDefault1->sceneBoundingRect().topLeft().x();
    topLeftDiffY      = tLY-rectDefault1->sceneBoundingRect().topLeft().y();
    topRightDiffX     = tRX-rectDefault1->sceneBoundingRect().topRight().x();
    topRightDiffY     = tRY-rectDefault1->sceneBoundingRect().topRight().y();
    bottomLeftDiffX   = bLX-rectDefault1->sceneBoundingRect().bottomLeft().x();
    bottomLeftDiffY   = bLY-rectDefault1->sceneBoundingRect().bottomLeft().y();
    bottomRightDiffX  = bRX-rectDefault1->sceneBoundingRect().bottomRight().x();
    bottomRightDiffY  = bRY-rectDefault1->sceneBoundingRect().bottomRight().y();

    qDebug()<<"tLXtolpleft"<<topLeftDiffX<<rectDefault1->sceneBoundingRect().topLeft().x();
    qDebug()<<"topRightxZdsfgb "<<topRightDiffX<<rectDefault1->sceneBoundingRect().topRight().x();
    tLX1 = tLX;
    tLY1 = tLY;
    tRY1 = tRY;
    tRX1 = tRX;
    bLX1 = bLX;
    bLY1 = bLY;
    bRX1 = bRX;
    bRY1 = bRY;

    prevRectPosX = rectDefault1->sceneBoundingRect().topLeft().x();
    prevRectPosY = rectDefault1->sceneBoundingRect().topLeft().y();
    }

    else if(sceneMode==10)
    {
        QList<QGraphicsItem*>itemList1;
        if(tMode==1)
        {
            if(this==scene1)
            {
                itemList1=scene1->items();
                if(itemTrackAP>-1)
                    itemList1.at(itemTrackAP)->setFlag(QGraphicsItem::ItemIsMovable,true);
            }
            else
            {
                itemList1=scene2->items();
                if(itemTrackLAT>-1)
                    itemList1.at(itemTrackLAT)->setFlag(QGraphicsItem::ItemIsMovable,true);
            }
        }

        pressedMovable=false;

        if(itemAt(event->scenePos(),QTransform())->flags().testFlag(QGraphicsItem::ItemIsMovable))
        {
            pressedMovable=true;
            if(tMode==1)
            {
                if((itemTrackAP==-1 ||itemTrackLAT==-1))
                {
                    for(int i=0;i<itemList1.length();i++)
                    {
                        if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                        {
                            if(this==scene1)
                            {
                                itemTrackAP=i;
                            }
                            else
                            itemTrackLAT=i;
                            itemList1.at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
                            break;
                        }
                    }
                }
                else
                {
                    if(this==scene1)
                        itemList1.at(itemTrackAP)->setFlag(QGraphicsItem::ItemIsMovable,false);
                    if(this==scene2)
                        itemList1.at(itemTrackLAT)->setFlag(QGraphicsItem::ItemIsMovable,false);
                }
            }

            if(this==scene2)
            {
                if(itemTrackAP==-1)
                {
                    QList<QGraphicsItem*>itemList1=scene1->items();
                    for(int i=0;i<itemList1.length();i++)
                    {
                        if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                            itemTrackAP=i;
                    }
                }
                origPoint2=event->scenePos();
            }
            if(this==scene1)
            {
                if(itemTrackLAT==-1)
                {
                    QList<QGraphicsItem*>itemList1=scene2->items();
                    for(int i=0;i<itemList1.length();i++)
                    {
                        if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                            itemTrackLAT=i;
                    }
                }
                origPoint1=event->scenePos();
            }
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void customscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    int penwidth=2;

    if(!pressed)
        return;

    if(sceneMode==customscene::Mode::NoMode && checkdeletebeam==1)
    {
        pressed = false;
        return;
    }

   switch(sceneMode)
   {
    case DrawLine:
   {
       qDebug()<<"DrawLine";
       //Draws line and adds its length in pixels as tag
       if(pressed){
           if(!line){
               line = new QGraphicsLineItem;
               this->addItem(line);
               drawPen=QPen(Qt::red, ((penwidth*(widthtoscene/512))), Qt::SolidLine);
               line->setPen(drawPen);
               line->setPos(startPoint);
               lineTag=new QGraphicsTextItem;
               QFont serifFont("Times",(10*(widthtoscene/512)),QFont::Bold);
               lineTag->setPos(startPoint);
               lineTag->setFont(serifFont);
               lineTag->setDefaultTextColor(Qt::white);
               lineTag->setAcceptHoverEvents(false);
               // this->addItem(lineTag);

           }

           float distance;

           if((startPoint.x()+trackDistanceX)>=1 && (startPoint.x()+trackDistanceX)<=imgSizeBoundary-1 && (startPoint.y()+trackDistanceY)>=1 && (startPoint.y()+trackDistanceY)<=imgSizeBoundary-1)
           {
           line->setLine(0,0,
                         event->scenePos().x() - startPoint.x(),
                         event->scenePos().y() - startPoint.y());
//            }
           distance= std::sqrtf(std::powf(event->scenePos().x() - startPoint.x(),2)
                                      +std::powf(event->scenePos().y() - startPoint.y(),2));

           trackDistanceX=event->scenePos().x() - startPoint.x();
           trackDistanceY=event->scenePos().y() - startPoint.y();

           lineTag->setPlainText(QString::number((distance*pixelPitch)/10,'f',2)+" cm");
           distance1 = distance;
           }

       }

       break;
   }
   case DilineatorMode:
   {

    origPoint1=event->scenePos();

    tLX = topLeftDiffX+rectDefault1->sceneBoundingRect().topLeft().x();
    tLY = topLeftDiffY+rectDefault1->sceneBoundingRect().topLeft().y();
    tRX = topRightDiffX+rectDefault1->sceneBoundingRect().topRight().x();
    tRY = topRightDiffY+rectDefault1->sceneBoundingRect().topRight().y();
    bLX = bottomLeftDiffX+rectDefault1->sceneBoundingRect().bottomLeft().x();
    bLY = bottomLeftDiffY+rectDefault1->sceneBoundingRect().bottomLeft().y();
    bRX = bottomRightDiffX+rectDefault1->sceneBoundingRect().bottomRight().x();
    bRY = bottomRightDiffY+rectDefault1->sceneBoundingRect().bottomRight().y();

    curRectPosX = rectDefault1->sceneBoundingRect().topLeft().x();
    curRectPosY = rectDefault1->sceneBoundingRect().topLeft().y();

    break;
   }

     case ManualMode:
   {

       int s;
       if(this==scene1)
       {
           if(itemTrackAP>=0 && scene1->items().at(itemTrackAP)->isUnderMouse() && pressedMovable==true)
           {
               posChanged=event->scenePos()-origPoint1;
               qDebug()<<"clicked area"<<event->scenePos()<<origPoint1;

               accPosXAP=accPosXAP+posChanged.x();
               accPosYAP=accPosYAP+posChanged.y();

               qDebug()<<"poschanged"<<std::abs(posChanged.x())<<std::abs(posChanged.y())<<10/pixelPitch;
               qDebug()<<"posacc"<<accPosXAP<<accPosYAP;

               s=1;

               if(std::abs(accPosXAP)<((boundX*10)/pixelPitch) && std::abs(accPosYAP)<((boundY*10)/pixelPitch))
               {
                   scene1->items().at(itemTrackAP)->moveBy(posChanged.x(),posChanged.y());
                   if(itemTrackLAT>=0)
                   scene2->items().at(itemTrackLAT)->moveBy(0,posChanged.y());
                   qDebug()<<"PosAccXY"<<accPosXAP<<accPosYAP;
                   origAccPosXAP = accPosXAP;  // How much content is moved
                   origAccPosYAP = accPosYAP;
                   origAccPosYLAT = origAccPosYAP;
               }
               else if(std::abs(accPosXAP)<((boundX*10)/pixelPitch))
               {
                   scene1->items().at(itemTrackAP)->moveBy(posChanged.x(),0);
                   qDebug()<<"PosAccX"<<accPosXAP<<accPosYAP;
                   origAccPosXAP = accPosXAP;  // How much content is moved
                   accPosYAP = origAccPosYAP;

               }

               else if(std::abs(accPosYAP)<((boundY*10)/pixelPitch))
               {
                   scene1->items().at(itemTrackAP)->moveBy(0,posChanged.y());
                   if(itemTrackLAT>=0)
                   scene2->items().at(itemTrackLAT)->moveBy(0,posChanged.y());
                   qDebug()<<"PosAccY"<<accPosXAP<<accPosYAP;
                   accPosXAP = origAccPosXAP;  // How much content is moved
                   origAccPosYAP = accPosYAP;
                   origAccPosYLAT = origAccPosYAP;

               }

               else
               {
                   accPosXAP=origAccPosXAP;
                   accPosYAP=origAccPosYAP;
               }

               accPosYLAT = accPosYAP;

               origPoint1 = event->scenePos();

               qDebug()<<"Posss"<<accPosXAP<<accPosYAP;


           }
       }

       else if(this==scene2)
       {
           if(itemTrackLAT>=0 && scene2->items().at(itemTrackLAT)->isUnderMouse() && pressedMovable==true)
           {
               posChanged = event->scenePos()-origPoint2;

               qDebug()<<"clicked Pos "<<event->scenePos()<<origPoint2;

               accPosXLAT = accPosXLAT+posChanged.x();  //How much Cursor is moved
               accPosYLAT = accPosYLAT+posChanged.y();

               qDebug()<<"abs(posChanged)"<<std::abs(posChanged.x())<<std::abs(posChanged.y())<<10/pixelPitch;

               qDebug()<<"PosAcc"<<accPosXLAT<<accPosYLAT;

               if(std::abs(accPosXLAT)<((boundZ*10)/pixelPitch) && std::abs(accPosYLAT)<((boundY*10)/pixelPitch))
               {
                   scene2->items().at(itemTrackLAT)->moveBy(posChanged.x(),posChanged.y());
                   if(itemTrackAP>=0)
                   scene1->items().at(itemTrackAP)->moveBy(0,posChanged.y());

                   qDebug()<<"PosAccXY"<<accPosXLAT<<accPosYLAT;
                   origAccPosXLAT = accPosXLAT;  // How much content is moved
                   origAccPosYLAT = accPosYLAT;
                   origAccPosYAP = origAccPosYLAT;
               }

               else if(std::abs(accPosXLAT)<((boundZ*10)/pixelPitch))
               {
                   scene2->items().at(itemTrackLAT)->moveBy(posChanged.x(),0);
                   qDebug()<<"PosAccX"<<accPosXLAT<<accPosYLAT;
                   origAccPosXLAT = accPosXLAT;  // How much content is moved
                   accPosYLAT = origAccPosYLAT;
               }
               else if(std::abs(accPosYLAT)<((boundY*10)/pixelPitch))
               {
                   scene2->items().at(itemTrackLAT)->moveBy(0,posChanged.y());
                   if(itemTrackAP>=0)
                   scene1->items().at(itemTrackAP)->moveBy(0,posChanged.y());
                   qDebug()<<"PosAccY"<<accPosXLAT<<accPosYLAT;
                   accPosXLAT = origAccPosXLAT;  // How much content is moved
                   origAccPosYLAT = accPosYLAT;
                   origAccPosYAP = origAccPosYLAT;
               }
               else
               {
                   accPosXLAT=origAccPosXLAT;
                   accPosYLAT=origAccPosYLAT;
               }
               accPosYAP = accPosYLAT;

               origPoint2 = event->scenePos();
               qDebug()<<"Posss"<<accPosXLAT<<accPosYLAT<<accPosXAP<<accPosYAP;
           }
       }
       break;
   }

   default:

       break;
   }

    QGraphicsScene::mouseMoveEvent(event);
}

void customscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    Fx1=(rect7->sceneBoundingRect().topLeft().x()-f/pix)*pix;
//    qDebug()<<"Fx1-----:"<<Fx1;

//    Fx2=(rect8->sceneBoundingRect().topLeft().x()-f/pix)*pix;
//    qDebug()<<"Fx2-----:"<<Fx2;

//    Fy1=(f1/pix-rect9->sceneBoundingRect().topLeft().y())*pix;
//    qDebug()<<"Fy1-----:"<<Fy1;

//    Fy2=(f1/pix-rect6->sceneBoundingRect().topLeft().y())*pix;
//    qDebug()<<"Fy2-----:"<<Fy2;

//    Cx=(centerDefault1->sceneBoundingRect().topLeft().x()-f/pix)*pix;
//    qDebug()<<"Cx-----:"<<Cx;

    int penwidth=2;

    if(!pressed)
        return;


    pressed = false;

    switch(sceneMode)
    {

    case DilineatorMode:
    {

    tLX = topLeftDiffX+rectDefault1->sceneBoundingRect().topLeft().x();
    tLY = topLeftDiffY+rectDefault1->sceneBoundingRect().topLeft().y();
    tRX = topRightDiffX+rectDefault1->sceneBoundingRect().topRight().x();
    tRY = topRightDiffY+rectDefault1->sceneBoundingRect().topRight().y();
    bLX = bottomLeftDiffX+rectDefault1->sceneBoundingRect().bottomLeft().x();
    bLY = bottomLeftDiffY+rectDefault1->sceneBoundingRect().bottomLeft().y();
    bRX = bottomRightDiffX+rectDefault1->sceneBoundingRect().bottomRight().x();
    bRY = bottomRightDiffY+rectDefault1->sceneBoundingRect().bottomRight().y();

    qDebug()<<"rectPositions"<<curRectPosX<<prevRectPosX;

    centerDilX = (tLX + bRX)/2;
    centerDilY = (tLY + bRY)/2;

    if (round(abs(curRectPosX-prevRectPosX))>0 ||round(abs(curRectPosY-prevRectPosY))>0 )
     {
    curX = event->scenePos().rx();
    curY = event->scenePos().ry();


    centerDilX = (tLX + bRX)/2;
    centerDilY = (tLY + bRY)/2;

    }

    else if (round(abs(curRectPosX-prevRectPosX))==0 && round(abs(curRectPosY-prevRectPosY))==0)
    {
      centerDilX = centerTempX;
      centerDilY = centerTempY;
    }

    delete[] centerDefault1;
    centerDefault1 = NULL;
    centerDefault1 = new QGraphicsRectItem();
    this->addItem(centerDefault1);
    centerDefault1->setRect(centerDilX-(1.39/(imaginPixelSpacing*2)),centerDilY-(1.39/(imaginPixelSpacing*2)),(1.39/imaginPixelSpacing)/**2*/,(1.39/imaginPixelSpacing)/**2*/);
    centerDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));
    centerDefault1->setBrush(QBrush(Qt::red));
    centerTempX = centerDilX;
    centerTempY = centerDilY;

    float invangle;

   invangle = rTheta*(3.14/180);
    rTheta = invangle*(180/3.14);

    qDebug() <<"ReleaseRotateAngle "<<rTheta;


    double cTheta = -invangle;
    float tempX = tLX-isocenterX;
    float tempY = tLY-isocenterY;

    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

    ctLX = ctLX+isocenterX;
    ctLY = ctLY+isocenterY;

    tempX = tRX-isocenterX;
    tempY = tRY-isocenterY;

    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

    ctRX = ctRX+isocenterX;
    ctRY = ctRY+isocenterY;

    tempX = bLX-isocenterX;
    tempY = bLY-isocenterY;

    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);


    cbLX = cbLX+isocenterX;
    cbLY = cbLY+isocenterY;

    tempX = bRX-isocenterX;
    tempY = bRY-isocenterY;

    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

    cbRX = cbRX+isocenterX;
    cbRY = cbRY+isocenterY;



    cTheta = rTheta*(3.14/180);


    /*Calculating intial Dilineator Center*/

    float initCenterX, initCenterY;
     cTheta=-cTheta;
    tempX = centerTempX-isocenterX;
    tempY = centerTempY-isocenterY;

    initCenterX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    initCenterY = tempX*sin(cTheta)+tempY*cos(cTheta);

    initCenterX = (initCenterX+isocenterX);
    initCenterY = (initCenterY+isocenterY);


    if (rTheta!=gTheta)
    {
     gCenterX = isocenterX;
     gCenterY = isocenterY;
    }
    break;
    }

     case ManualMode:
    {
        pressedMovable=false;
        int s;

        if(this==scene1)
        {
            count1++;
            posChanged = QPointF(origAccPosXAP,origAccPosYAP)-prevPosChangedAP;
            prevPosChangedAP = QPointF(origAccPosXAP,origAccPosYAP);
            prevPosChangedLAT.ry()=prevPosChangedAP.ry();
            s = 1;
        }
        else
        {
            count2++;
            posChanged = QPointF(origAccPosXLAT,origAccPosYLAT)-prevPosChangedLAT;
            prevPosChangedLAT = QPointF(origAccPosXLAT,origAccPosYLAT);
            prevPosChangedAP.ry()=prevPosChangedLAT.ry();
            s = 2;
        }

        qDebug()<<"position changed......"<<posChanged<<" "<<s;
        emit positionChanged(posChanged,s);
        qDebug()<<"position changed emitted......";

        break;
    }

    default:
        break;

    }

    QGraphicsScene::mouseReleaseEvent(event);
}

