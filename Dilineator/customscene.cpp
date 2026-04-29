#include "customscene.h"
CustomScene *scene1;
CustomScene *scene2;
CustomScene *scene3;// for interchanging scene1 and scene2

CustomScene::Mode sceneMode1;
int count;
int count1 = 0;
int count2 = 0;

int tMode;// 1 for 2D , 0 for 3D
QRectF output;

int changeScene = 0;
int changeScene1 = 0;

//Drawing *myDrawingA;
//Drawing *myDrawingB;
//Drawing *myDrawingC;

extern int resizeState;
extern int resizeUpdate;
extern int workFMode;
extern int ImaginMode;
extern int FrameRateMode;

int itemTrackAP=-1;
int itemTrackAP1=-1;
int itemTrackLAT=-1;
int itemTrackLAT1=-1;

float trackDistanceX,trackDistanceY;
double accShiftX=0,accShiftY=0;

extern double boundX;
extern double boundY;
extern double boundZ;
//extern double boundPitch;
//extern double boundRoll;
//extern double boundYaw;

float gCenterX,gCenterY,gTheta;

extern QRectF APLATrect1;

extern int ContourBasedMovement;

double accPosXAP=0,accPosYAP=0;
double accPosXLAT=0,accPosYLAT=0;
QPointF prevPosChangedAP=QPointF(0,0);
QPointF prevPosChangedLAT=QPointF(0,0);

double origAccPosXAP,origAccPosYAP;
double origAccPosXLAT,origAccPosYLAT;
int UpdateAP,UpdateLAT;

extern float imaginPixelSpacing;
extern float imgSizeBoundary;

QPointF posChanged = QPointF(0,0);
bool pressed = false;
bool pressedMovable=false;


int updateangleCount=0;
extern int receiveangleCount;

namespace
{
// for resizer in rectangle items
class RectResizer : public SizeGripItem::Resizer
{
public:
    virtual void operator()(QGraphicsItem* item, const QRectF& rect)
    {
        //        QGraphicsRectItem* rectItem =
        //                dynamic_cast<QGraphicsRectItem*>(item);
        CustomItem* rectItem =
                dynamic_cast<CustomItem*>(item);

        if (rectItem)
        {
            rectItem->setRect(rect);
        }
    }
};
//ellipse resizer was implemented from the above code with same number of track points.the same can be implemented for all the
// other graphics items

class EllipseResizer : public SizeGripItem::Resizer
{
public:
    virtual void operator()(QGraphicsItem* item, const QRectF& rect)
    {
        CustomItemEllipse* ellipseItem =
                dynamic_cast<CustomItemEllipse*>(item);

        if (ellipseItem)
        {
            ellipseItem->setRect(rect);
        }
    }
};

}

CustomScene::CustomScene()
{
    sceneMode = NoMode;
    circle = 0;
    line = 0;
    rect=0;
    ellip=0;
    path=0;
    paintPath=0;
    text=0;
    line2=0;
    //    myDrawing=0;
    pixMap=0;
    drawPen=QPen(Qt::blue, 3, Qt::SolidLine);
    movingPen=QPen(Qt::green, 1, Qt::SolidLine);
    textPen=QPen(Qt::black, 1, Qt::SolidLine);
    pixelPitch=1.0;

}
CustomScene::~CustomScene()
{

}

void CustomScene::setScene(CustomScene *sceneA,CustomScene *sceneB,CustomScene::Mode mode,int c,int m)
{
    // set scenes in 2d mode
    rect=0;
    ellip=0;
    path=0;
    paintPath = 0;
    sceneMode1 = mode;
    scene1 = sceneA;
    scene2 = sceneB;
    count = c;
    tMode = m;
}

void CustomScene::setScene(CustomScene *sceneA, CustomScene *sceneB, CustomScene *sceneC, CustomScene::Mode mode, int c, int m)
{
    // set scenes in 3d mode
    rect=0;
    ellip=0;
    path=0;
    paintPath = 0;
    sceneMode1 = mode;
    scene1 = sceneA;
    scene2 = sceneB;
    scene3 = sceneC;
    count = c;
    tMode = m;
}


void CustomScene::setMode(CustomScene::Mode mode)
{
    /*set the mode for the scene*/
    sceneMode = mode;

    QGraphicsView::DragMode vMode = QGraphicsView::NoDrag;
    if(mode == SelectObject)
    {
        //makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
    }

}

void CustomScene::setpixelPitch(float realSize)
{
    pixelPitch=realSize;
}

CustomScene::Mode CustomScene::getCurrMode()
{
    return sceneMode;
}

CustomScene::Mode CustomScene::getMode(QString type)
{
    //Assumes type is one of the allowed strings.
    //Returns mode based on the string .
    //returns NoMode for anything else
    if(type=="ellipse")
    {
        return DrawEllipse;
    }
    else if(type=="rectangle")
    {
        return DrawRect;
    }
    else if(type=="line")
    {
        return DrawLine;
    }
    else if(type=="angle")
    {
        return DrawAngle;
    }
    else if(type=="freehand")
    {
        return DrawFree;
    }
    else if(type=="text")
    {
        return DrawText;
    }
    else if (type=="cbctrectangle")
       {
           return Drawrectcbct;
       }
    else
    {
        return NoMode;
    }
}

void CustomScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode!=10){
        emit mouseDoubleClicked();

    }
     QGraphicsScene::mouseDoubleClickEvent(event);
     //emit mouseDoubleClicked();
}

void CustomScene::keyPressEvent(QKeyEvent *event)
{

if(sceneMode==ManualMode){

    if((event->key()==Qt::Key_Left)||(event->key()==Qt::Key_Right)||(event->key()==Qt::Key_Up)||(event->key()==Qt::Key_Down))
    {
      posChanged.rx()=0;
      posChanged.ry()=0;
    if(event->key()==Qt::Key_Left)
    {
        if(ContourBasedMovement==1)
        {
            if(origAccPosXAP>(-((boundX-0.05)*10)/(pixelPitch)))
            {
            posChanged.rx()=-0.5/(pixelPitch);//-2;
            posChanged.ry()=0;
            origAccPosXAP = origAccPosXAP+posChanged.x();  //How much Cursor is moved
            origAccPosYAP = origAccPosYAP+posChanged.y();

            origAccPosYLAT=origAccPosYAP;
            accPosXAP=origAccPosXAP;
            accPosYAP=origAccPosYAP;
            accPosYLAT = origAccPosYLAT;
            }
        }
        else if (ContourBasedMovement==2)
        {
            if(origAccPosXLAT>(-((boundZ-0.05)*10)/(pixelPitch)))
            {
            posChanged.rx()=-0.5/(pixelPitch);//-2;
            posChanged.ry()=0;
            origAccPosXLAT = origAccPosXLAT+posChanged.x();  //How much Cursor is moved
            origAccPosYLAT = origAccPosYLAT+posChanged.y();

            accPosXLAT = origAccPosXLAT;
            accPosYLAT = origAccPosYLAT;
            origAccPosYAP = origAccPosYLAT;
            accPosYAP=origAccPosYAP;
            }
        }

        else
        {

        if(this==scene1)
        {
        if(origAccPosXAP>(-((boundX-0.05)*10)/(pixelPitch)))
        {
        posChanged.rx()=-0.5/(pixelPitch);//-2;
        posChanged.ry()=0;
        origAccPosXAP = origAccPosXAP+posChanged.x();  //How much Cursor is moved
        origAccPosYAP = origAccPosYAP+posChanged.y();

        origAccPosYLAT=origAccPosYAP;
        accPosXAP=origAccPosXAP;
        accPosYAP=origAccPosYAP;
        accPosYLAT = origAccPosYLAT;
        }
        }
        else
        {
         if(origAccPosXLAT>(-((boundZ-0.05)*10)/(pixelPitch)))
         {
         posChanged.rx()=-0.5/(pixelPitch);//-2;
         posChanged.ry()=0;
         origAccPosXLAT = origAccPosXLAT+posChanged.x();  //How much Cursor is moved
         origAccPosYLAT = origAccPosYLAT+posChanged.y();

         accPosXLAT = origAccPosXLAT;
         accPosYLAT = origAccPosYLAT;
         origAccPosYAP = origAccPosYLAT;
         accPosYAP=origAccPosYAP;
         }
        }
        }

    }
    if(event->key()==Qt::Key_Right)
    {
        if(ContourBasedMovement==1)
        {
            if(origAccPosXAP<(((boundX-0.05)*10)/(pixelPitch)))
            {
            posChanged.rx()=0.5/(pixelPitch);//2;
            posChanged.ry()=0;
            origAccPosXAP = origAccPosXAP+posChanged.x();  //How much Cursor is moved
            origAccPosYAP = origAccPosYAP+posChanged.y();

            origAccPosYLAT=origAccPosYAP;
            accPosXAP=origAccPosXAP;
            accPosYAP=origAccPosYAP;
            accPosYLAT = origAccPosYLAT;
            }
        }
        else if (ContourBasedMovement==2)
        {
            if(origAccPosXLAT<(((boundZ-0.05)*10)/(pixelPitch)))
            {
            posChanged.rx()=0.5/(pixelPitch);//2;
            posChanged.ry()=0;
            origAccPosXLAT = origAccPosXLAT+posChanged.x();  //How much Cursor is moved
            origAccPosYLAT = origAccPosYLAT+posChanged.y();

            accPosXLAT = origAccPosXLAT;
            accPosYLAT = origAccPosYLAT;
            origAccPosYAP = origAccPosYLAT;
            accPosYAP=origAccPosYAP;
            }
        }

        else
        {

        if(this==scene1)
        {
        if(origAccPosXAP<(((boundX-0.05)*10)/(pixelPitch)))
        {
        posChanged.rx()=0.5/(pixelPitch);//2;
        posChanged.ry()=0;
        origAccPosXAP = origAccPosXAP+posChanged.x();  //How much Cursor is moved
        origAccPosYAP = origAccPosYAP+posChanged.y();

        origAccPosYLAT=origAccPosYAP;
        accPosXAP=origAccPosXAP;
        accPosYAP=origAccPosYAP;
        accPosYLAT = origAccPosYLAT;
        }
        }
        else
        {
         if(origAccPosXLAT<(((boundZ-0.05)*10)/(pixelPitch)))
         {
         posChanged.rx()=0.5/(pixelPitch);//2;
         posChanged.ry()=0;
         origAccPosXLAT = origAccPosXLAT+posChanged.x();  //How much Cursor is moved
         origAccPosYLAT = origAccPosYLAT+posChanged.y();

         accPosXLAT = origAccPosXLAT;
         accPosYLAT = origAccPosYLAT;
         origAccPosYAP = origAccPosYLAT;
         accPosYAP=origAccPosYAP;
         }
        }
        }
    }
    if(event->key()==Qt::Key_Up)
    {

        if(ContourBasedMovement==1)
        {
            if(origAccPosYAP>(-((boundY-0.05)*10)/(pixelPitch)))
            {
            posChanged.rx()=0;
            posChanged.ry()=-0.5/(pixelPitch);//-2;
            origAccPosXAP = origAccPosXAP+posChanged.x();  //How much Cursor is moved
            origAccPosYAP = origAccPosYAP+posChanged.y();

            origAccPosYLAT=origAccPosYAP;
            accPosXAP=origAccPosXAP;
            accPosYAP=origAccPosYAP;
            accPosYLAT = origAccPosYLAT;
            }
        }
        else if (ContourBasedMovement==2)
        {
            if(origAccPosYLAT>(-((boundY-0.05)*10)/(pixelPitch)))
            {
            posChanged.rx()=0;
            posChanged.ry()=-0.5/(pixelPitch);//-2;
            origAccPosXLAT = origAccPosXLAT+posChanged.x();  //How much Cursor is moved
            origAccPosYLAT = origAccPosYLAT+posChanged.y();


            accPosXLAT = origAccPosXLAT;
            accPosYLAT = origAccPosYLAT;
            origAccPosYAP = origAccPosYLAT;
            accPosYAP=origAccPosYAP;
            }
        }

        else
        {

        if(this==scene1)
        {
        if(origAccPosYAP>(-((boundY-0.05)*10)/(pixelPitch)))
        {
        posChanged.rx()=0;
        posChanged.ry()=-0.5/(pixelPitch);//-2;
        origAccPosXAP = origAccPosXAP+posChanged.x();  //How much Cursor is moved
        origAccPosYAP = origAccPosYAP+posChanged.y();

        origAccPosYLAT=origAccPosYAP;
        accPosXAP=origAccPosXAP;
        accPosYAP=origAccPosYAP;
        accPosYLAT = origAccPosYLAT;
        }
        }
        else
        {
         if(origAccPosYLAT>(-((boundY-0.05)*10)/(pixelPitch)))
         {
         posChanged.rx()=0;
         posChanged.ry()=-0.5/(pixelPitch);//-2;
         origAccPosXLAT = origAccPosXLAT+posChanged.x();  //How much Cursor is moved
         origAccPosYLAT = origAccPosYLAT+posChanged.y();


         accPosXLAT = origAccPosXLAT;
         accPosYLAT = origAccPosYLAT;
         origAccPosYAP = origAccPosYLAT;
         accPosYAP=origAccPosYAP;
         }
        }
        }
    }
    if(event->key()==Qt::Key_Down)
    {

        if(ContourBasedMovement==1)
        {
            if(origAccPosYAP<(((boundY-0.05)*10)/(pixelPitch)))
            {
            posChanged.rx()=0;
            posChanged.ry()=0.5/(pixelPitch);//2;
            origAccPosXAP = origAccPosXAP+posChanged.x();  //How much Cursor is moved
            origAccPosYAP = origAccPosYAP+posChanged.y();

            origAccPosYLAT=origAccPosYAP;
            accPosXAP=origAccPosXAP;
            accPosYAP=origAccPosYAP;
            accPosYLAT = origAccPosYLAT;
            }
        }
        else if (ContourBasedMovement==2)
        {
            if(origAccPosYLAT<(((boundY-0.05)*10)/(pixelPitch)))
            {
            posChanged.rx()=0;
            posChanged.ry()=0.5/(pixelPitch);//2;
            origAccPosXLAT = origAccPosXLAT+posChanged.x();  //How much Cursor is moved
            origAccPosYLAT = origAccPosYLAT+posChanged.y();

            accPosXLAT = origAccPosXLAT;
            accPosYLAT = origAccPosYLAT;
            origAccPosYAP = origAccPosYLAT;
            accPosYAP=origAccPosYAP;
            }
        }

        else
        {

        if(this==scene1)
        {
        if(origAccPosYAP<(((boundY-0.05)*10)/(pixelPitch)))
        {
        posChanged.rx()=0;
        posChanged.ry()=0.5/(pixelPitch);//2;
        origAccPosXAP = origAccPosXAP+posChanged.x();  //How much Cursor is moved
        origAccPosYAP = origAccPosYAP+posChanged.y();

        origAccPosYLAT=origAccPosYAP;
        accPosXAP=origAccPosXAP;
        accPosYAP=origAccPosYAP;
        accPosYLAT = origAccPosYLAT;
        }
        }
        else
        {
         if(origAccPosYLAT<(((boundY-0.05)*10)/(pixelPitch)))
         {
         posChanged.rx()=0;
         posChanged.ry()=0.5/(pixelPitch);//2;
         origAccPosXLAT = origAccPosXLAT+posChanged.x();  //How much Cursor is moved
         origAccPosYLAT = origAccPosYLAT+posChanged.y();

         accPosXLAT = origAccPosXLAT;
         accPosYLAT = origAccPosYLAT;
         origAccPosYAP = origAccPosYLAT;
         accPosYAP=origAccPosYAP;
         }
        }
        }
    }

    int s;
    if(ContourBasedMovement==1)
    {

        // in AP

            s = 1;

            if(itemTrackAP1>=0)
                   {
                   scene2->items().at(itemTrackAP1)->moveBy(posChanged.x(),posChanged.y());
                   prevPosChangedAP = QPointF(origAccPosXAP,origAccPosYAP);
                   prevPosChangedLAT.ry()=prevPosChangedAP.ry();
                   }

                   else
                   {
                       QList<QGraphicsItem*> itemList1=scene2->items();
                       for(int i=0;i<itemList1.length();i++){

                            if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                            {
                                itemList1.at(i)->moveBy(posChanged.x(),posChanged.y());
                                itemTrackAP1 = i;
                            }
                       }

                       prevPosChangedAP = QPointF(origAccPosXAP,origAccPosYAP);
                       prevPosChangedLAT.ry()=prevPosChangedAP.ry();
                   }

    }
    else if (ContourBasedMovement==2)
    {

        // in AP

            s = 2;

            if(itemTrackLAT1>=0)
                   {
                   scene2->items().at(itemTrackLAT1)->moveBy(posChanged.x(),posChanged.y());
                   prevPosChangedLAT = QPointF(origAccPosXLAT,origAccPosYLAT);
                   prevPosChangedAP.ry()=prevPosChangedLAT.ry();
                   }

                   else
                   {
                       QList<QGraphicsItem*> itemList1=scene2->items();
                       for(int i=0;i<itemList1.length();i++){

                            if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                            {
                                itemList1.at(i)->moveBy(posChanged.x(),posChanged.y());
                                itemTrackLAT1 = i;
                            }
                       }

                       prevPosChangedLAT = QPointF(origAccPosXLAT,origAccPosYLAT);
                       prevPosChangedAP.ry()=prevPosChangedLAT.ry();
                   }

    }

    else
    {

    // in AP
    if (this==scene1){


        s = 1;

        if(itemTrackAP>=0)
               {
               scene1->items().at(itemTrackAP)->moveBy(posChanged.x(),posChanged.y());
               if(itemTrackLAT>=0)
               scene2->items().at(itemTrackLAT)->moveBy(0,posChanged.y());
               prevPosChangedAP = QPointF(origAccPosXAP,origAccPosYAP);
               prevPosChangedLAT.ry()=prevPosChangedAP.ry();
               }

               else
               {
                   QList<QGraphicsItem*> itemList1=scene1->items();
                   for(int i=0;i<itemList1.length();i++){

                        if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                        {
                          itemList1.at(i)->moveBy(posChanged.x(),posChanged.y());
                          itemTrackAP=i;
                        }
                   }

                   QList<QGraphicsItem*> itemList=scene2->items();
                   for(int i=0;i<itemList.length();i++){

                        if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList.at(i))&&itemList.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                        {
                            itemList.at(i)->moveBy(0,posChanged.y());
                            itemTrackLAT=i;
                        }
                   }

                   prevPosChangedAP = QPointF(origAccPosXAP,origAccPosYAP);
                   prevPosChangedLAT.ry()=prevPosChangedAP.ry();
               }


           }

           // in LAT
           else{

               s = 2;

               if(itemTrackLAT>=0)
               {
               scene2->items().at(itemTrackLAT)->moveBy(posChanged.x(),posChanged.y());
               if(itemTrackAP>=0)
               scene1->items().at(itemTrackAP)->moveBy(0,posChanged.y());
               prevPosChangedLAT = QPointF(origAccPosXLAT,origAccPosYLAT);
               prevPosChangedAP.ry()=prevPosChangedLAT.ry();
               }

               else
               {
                   QList<QGraphicsItem*> itemList1=scene2->items();
                   for(int i=0;i<itemList1.length();i++){

                        if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                        {
                            itemList1.at(i)->moveBy(posChanged.x(),posChanged.y());
                            itemTrackLAT=i;
                        }
                   }

                     QList<QGraphicsItem*> itemList=scene1->items();
                     for(int i=0;i<itemList.length();i++){

                          if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList.at(i))&&itemList.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                          {
                              itemList.at(i)->moveBy(0,posChanged.y());
                              itemTrackAP=i;
                          }
                     }
                     prevPosChangedLAT = QPointF(origAccPosXLAT,origAccPosYLAT);
                     prevPosChangedAP.ry()=prevPosChangedLAT.ry();
               }


           }
    }

           qDebug()<<"position Changed";


    emit positionChanged(posChanged,s);

   }

   // QGraphicsScene::keyPressEvent(event);
   }
QGraphicsScene::keyPressEvent(event);
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug()<<"mouse pressed...."<<sceneMode<<pixelPitch<<imaginPixelSpacing;


    qDebug()<<"event->scenePos "<<event->scenePos();





    if (event->button() != Qt::LeftButton)
        return;

    pressed = true;

    if(sceneMode==this->DrawText)
            origPoint=event->scenePos();
        qDebug()<<"origPoint "<<event->scenePos();
    //    else if(sceneMode==this->DrawLine)
    //         startPoint=event->scenePos();


   // qDebug()<<"accPossssss "<<accPosXAP<<accPosYAP<<accPosXLAT<<accPosYLAT;

    drawPen=QPen(Qt::blue, 2*(0.139/pixelPitch), Qt::SolidLine);

    if (receiveangleCount!=updateangleCount)
     {
      updateangleCount = receiveangleCount;
      angleFlag=true;
      line2=0;

     }

    if (workFMode==1&&ImaginMode==0)
    {
        qDebug()<<"workFMode==1&&ImaginMode==0";
        if(sceneStatus!=1)
            return;
        if(rectDefault1)
        {
            this->rectDefault1->setFlag(QGraphicsItem::ItemIsMovable,false);
            rectSizeGripItem1->setEnabled(false);
        }
    }

    qDebug()<<"mouse pressed...."<<sceneMode;

    // manual mode in 2D
    if(sceneMode==10)
    {
        if(ContourBasedMovement==1)
        {
         QList<QGraphicsItem*> itemList1;
         itemList1=scene2->items();
         if(itemTrackAP1>-1)
         itemList1.at(itemTrackAP1)->setFlag(QGraphicsItem::ItemIsMovable,true);

         pressedMovable=false;

         qDebug()<<"Entering";

         if(itemAt(event->scenePos(),QTransform())==0)
            return;
         if(itemAt(event->scenePos(),QTransform())->flags().testFlag(QGraphicsItem::ItemIsMovable))
         {
             pressedMovable=true;

             qDebug()<<"Entering";

             if(itemTrackAP1==-1)
             {
             for(int i=0;i<itemList1.length();i++)
             {
             if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
             {
                 itemTrackAP1 =i;
                 itemList1.at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
                 break;
             }
             }
             }
             else
                itemList1.at(itemTrackAP1)->setFlag(QGraphicsItem::ItemIsMovable,false);
             origPoint1 = event->scenePos();
          }
        }

        else if (ContourBasedMovement==2)
        {
            QList<QGraphicsItem*> itemList1;
            itemList1=scene2->items();
            if(itemTrackLAT1>-1)
            itemList1.at(itemTrackLAT1)->setFlag(QGraphicsItem::ItemIsMovable,true);

            pressedMovable=false;

            if(itemAt(event->scenePos(),QTransform())==0)
               return;

            if(itemAt(event->scenePos(),QTransform())->flags().testFlag(QGraphicsItem::ItemIsMovable))
            {
                pressedMovable=true;

                if(itemTrackLAT1==-1)
                {
                for(int i=0;i<itemList1.length();i++)
                {
                if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                {
                    itemTrackLAT1 =i;
                    itemList1.at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
                    break;
                }
                }
                }
                else
                   itemList1.at(itemTrackLAT1)->setFlag(QGraphicsItem::ItemIsMovable,false);

                origPoint2 = event->scenePos();
             }
           }


        else
        {

        QList<QGraphicsItem*> itemList1;
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
            if((itemTrackAP==-1 || itemTrackLAT==-1))
            {
            for(int i=0;i<itemList1.length();i++)
            {
            if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList1.at(i))&&itemList1.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
            {

                if(this==scene1)
                {
                itemTrackAP =i;
                }
                else
                itemTrackLAT =i;
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



            //Assigns the scene position to origPoint.
            // if the current scene is LAT
            if(this==scene2)
            {
                if(itemTrackAP==-1)
                {
                QList<QGraphicsItem*> itemList=scene1->items();
                for(int i=0;i<itemList.length();i++){

                if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList.at(i))&&itemList.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                 itemTrackAP =i;
                }
                }

                //scene2->setMode(sceneMode1);
                origPoint2 = event->scenePos();

            }

            //Assigns the scene position to origPoint.
            // if the current scene is AP
            if(this==scene1)
            {
                qDebug()<<"Scene1";
                //scene1->setMode(sceneMode1);

                if(itemTrackLAT==-1)
                {
                QList<QGraphicsItem*> itemList=scene2->items();
                for(int i=0;i<itemList.length();i++){

                if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList.at(i))&&itemList.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                 itemTrackLAT =i;
                }
                }

                origPoint1 = event->scenePos();

                qDebug()<<"origPoint1"<<origPoint1;
            }
        }
        }



    }

    else if(sceneMode==11){


        if(workFMode==1&&ImaginMode==0&&FrameRateMode==1){


            origPoint1 = event->scenePos();

        //if(workFMode==1&&ImaginMode==0&&(FrameRateMode==1||FrameRateMode==2||FrameRateMode==3)){

          //this->setSceneRect(0,0,3072,3072);
          rectDefault1->setFlag(QGraphicsItem::ItemIsMovable,true);

          rectSizeGripItem1->setEnabled(true);
          prevX = event->scenePos().rx();
          prevY = event->scenePos().ry();

          dTheta=0;

          qDebug()<<"event scenttLXe "<<tLX<<tLY<<tRX<<tRY<<bLX<<bLY<<bRX<<bRY;


          if (resizeUpdate!=1)
          {

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

        }

    }

    else if(sceneMode==12)
    {
    CtPointList.clear();
    origPoint = event->scenePos();
    CtPointList.append(origPoint);
    }
    // if the mode is not NoMode
    else if((sceneMode!=0))
    {

        qDebug()<<"sceneMode.......... "<<sceneMode<<"sceneMode1........... "<<sceneMode1;
        // get the current point
        startPoint = event->scenePos();

        trackDistanceX=0;
        trackDistanceY=0;

        tFlag=0;

        qDebug()<<"Start Point"<<startPoint;
        qDebug()<<"count"<<count;

        if (count==1)
        {
            origPoint = event->scenePos();

            // if 3D mode, set axial scene mode
            if(tMode==0)
            {
                if(this==scene1)
                {
                    scene1->setMode(sceneMode1);
                }
            }
            else
            {
                // if pressed in AP, set AP scene mode
                if(this==scene1)
                {
                    scene1->setMode(sceneMode1);
                }
                // if pressed in LAT,set LAT scene mode&set changeScene flag to 1
                else
                {
                    scene2->setMode(sceneMode1);
                    changeScene = 1;
                }

            }

        }
    }

    qDebug()<<"mouse pressed...."<<sceneMode;





    QGraphicsScene::mousePressEvent(event);

}


void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if(!pressed)
       return;

    switch(sceneMode){

    qDebug()<<"sceneMode"<<sceneMode;

    case DrawAngle:
    {
        //Draws angle tool  and adds  tag at the  angle
        // angle tools has 2 lines:line &line2

        int var1 = 0;
        int var2 = 0;
        int var3 = 3072;
        int var4 = 3072;

        if(angleFlag)
        {
            // when angle is being drawn for 1st time, draw 1st line
            if(!line){
                if((startPoint.x()>var1 && startPoint.x()<var1+var3) && (startPoint.y()>var2 && startPoint.y()<var2+var4))
                {
                    line = new QGraphicsLineItem;
                    this->addItem(line);
                    line->setPen(drawPen);
                    line->setPos(startPoint);
                    qDebug()<<"1111";
                }

            }
            qDebug()<<"6"<<angleFlag;
            if(line!=0 && (event->scenePos().x()>var1+10 && event->scenePos().x()<var1+var3-10) &&(event->scenePos().y()>var2+10 && event->scenePos().y()<var2+var4-10))
            {
                line->setLine(0,0,
                              event->scenePos().x() - startPoint.x(),
                              event->scenePos().y() - startPoint.y());
            }
            qDebug()<<"7";
        }
        //}
        // after 1st line is drawn, draw 2nd line
        else if(!angleFlag)
        {
            qDebug()<<"1--->"<<angleFlag;
            if(!line2){
                qDebug()<<"2--->"<<startPoint<<var1<<var2<<var3<<var4;
                if(line!=0&& (startPoint.x()>var1 && startPoint.x()<var1+var3) && (startPoint.y()>var2 && startPoint.y()<var2+var4))
                {
                    line2 = new QGraphicsLineItem;
                    this->addItem(line2);
                    line2->setPen(drawPen);
                    line2->setPos(startPoint);
                    qDebug()<<"3--->"<<startPoint;
                }

            }

            if(line2!=0 && (event->scenePos().x()>var1+10 && event->scenePos().x()<var1+var3-10) &&(event->scenePos().y()>var2+10 && event->scenePos().y()<var2+var4-10))
            {
                line2->setLine(0,0,
                               event->scenePos().x() - startPoint.x(),
                               event->scenePos().y() - startPoint.y());

                qDebug()<<"888";

                // calculate angle
                float angle2=(lineAngle(startPoint,event->scenePos())-angle);

                if(QString::number(angle2)=="nan")
                    angle2=0;

                if(angle2>=0)
                {
                    angle2*=180.0F/(3.14);
                }
                else
                {
                    angle2=(angle2+3.14)*180.0/3.14;
                }


                QString a= QString::number(angle2,'f',1);//precision one.
                a.append(QChar(0xB0));//for degree symbol in unicode.
                angleTag->setPlainText(a);
                qDebug()<<"9";
                if(tMode==1)
                {


                    angleTag->setDefaultTextColor(Qt::white);
//                    QFont serifFont("Times",10,QFont::Bold);
                    QFont serifFont("Times",(0.139*25)/(pixelPitch),QFont::Bold);
                    angleTag->setFont(serifFont);

                }
                else
                {
                    angleTag->setDefaultTextColor(Qt::yellow);
//                    QFont serifFont("Times",6,QFont::Bold);
                    QFont serifFont("Times",(0.139*25)/(pixelPitch),QFont::Bold);
                    angleTag->setFont(serifFont);
                    qDebug()<<"3";

                }

                angleTag->setFlag(QGraphicsItem::ItemIsSelectable,false);
            }

        }

        break;
    }

    case Drawrectcbct:
    {

        if(!rect){
            rect = new QGraphicsRectItem;
            this->addItem(rect);
            rect->setPen(drawPen);
            rect->setPos(origPoint);
        }
        rect->setRect(0,0,
                      event->scenePos().x() - origPoint.x(),
                      event->scenePos().y() - origPoint.y());
        break;


    }
    case DrawText:
    {
        qDebug()<<"move----";
        break;
    }
    case DrawLine :

    {
        //Draws line and adds its length in pixels as tag
        if(pressed){
            if(!line){
                line = new QGraphicsLineItem;
                this->addItem(line);
                line->setPen(drawPen);
                line->setPos(startPoint);
                lineTag=new QGraphicsTextItem;
                QFont serifFont("Times",(0.139*25)/(pixelPitch),QFont::Bold);
                lineTag->setPos(startPoint);
                lineTag->setFont(serifFont);
                lineTag->setDefaultTextColor(Qt::yellow);
                lineTag->setAcceptHoverEvents(false);
                this->addItem(lineTag);

            }


          //  qDebug()<<"distanceline "<<startPoint<<trackDistanceX<<trackDistanceY<<imgSizeBoundary;



            if((startPoint.x()+trackDistanceX)>=1 && (startPoint.x()+trackDistanceX)<=imgSizeBoundary-1 && (startPoint.y()+trackDistanceY)>=1 && (startPoint.y()+trackDistanceY)<=imgSizeBoundary-1)
            {
            line->setLine(0,0,
                          event->scenePos().x() - startPoint.x(),
                          event->scenePos().y() - startPoint.y());
//            }
            float distance= std::sqrtf(std::powf(event->scenePos().x() - startPoint.x(),2)
                                       +std::powf(event->scenePos().y() - startPoint.y(),2));

            trackDistanceX=event->scenePos().x() - startPoint.x();
            trackDistanceY=event->scenePos().y() - startPoint.y();

            lineTag->setPlainText(QString::number((distance*pixelPitch)/10,'f',2)+" cm");
            }
        }

        break;
    }
//    case DrawCircle:
//    {
//        // draws circle, add its diameter as tag
//        if(pressed){
//            QPointF point = event->scenePos(); // Get the current mouse position

//            /* Find out how much mouse has moved from the initial point
//             * X Direction movement = width of rectangle,y direction movement = height of rectangle*/


//            int w = point.x()-startPoint.x();
//            int h = w;


//            if(!circle){

//                // create new ellipse item
//                circle = new QGraphicsEllipseItem;
//                circle->setPen(drawPen);

//                this->addItem(circle);
//                //                rect->setFlag(QGraphicsItem::ItemSendsScenePositionChanges,true);
//                circle->setZValue(1);

//                circleTag=new QGraphicsTextItem;
//                QFont serifFont("Times",10,QFont::Bold);
//                circleTag->setPos(startPoint);
//                circleTag->setFont(serifFont);
//                circleTag->setDefaultTextColor(Qt::white);
//                circleTag->setAcceptHoverEvents(false);
//                this->addItem(circleTag);

//            }
//            // adjust position
//            if (w<1)
//            {
//                if (h<1)
//                {
//                    circle->setRect(point.x(),point.y(),std::abs(w),std::abs(h));
//                }
//                else
//                {
//                    circle->setRect(point.x(),startPoint.y(),std::abs(w),h);

//                }
//            }
//            else
//            {
//                if (h<1)
//                {
//                    circle->setRect(point.x(),point.y(),w,std::abs(h));
//                }
//                else
//                {
//                    circle->setRect(startPoint.x(),startPoint.y(),w,h);

//                }
//            }
//            circleTag->setPlainText(QString::number((std::abs(w)*pixelPitch),'f',1)+" mm");

//        }

//        break;
//    }
    /*modified*/
    case DrawCircle:
       {
           // draws circle, add its diameter as tag
           if(pressed){
               QPointF point = event->scenePos(); // Get the current mouse position

               /* Find out how much mouse has moved from the initial point
                * X Direction movement = width of rectangle,y direction movement = height of rectangle*/


               int w = point.x()-startPoint.x();
               int h = (point.y()-startPoint.y())/abs(point.y()-startPoint.y())*abs(w);


               if(!circle)
               {
                   // create new ellipse item
                   circle = new QGraphicsEllipseItem;
                   circle->setPen(drawPen);
                   this->addItem(circle);
                   //                rect->setFlag(QGraphicsItem::ItemSendsScenePositionChanges,true);
                   circle->setZValue(1);

                   circleTag=new QGraphicsTextItem;
                   QFont serifFont("Times",(0.139*25)/(pixelPitch),QFont::Bold);
                   circleTag->setPos(startPoint);
                   circleTag->setFont(serifFont);
                   circleTag->setDefaultTextColor(Qt::yellow);
                   circleTag->setAcceptHoverEvents(false);
                   this->addItem(circleTag);
               }
               // adjust position
               if (w<1)
               {
                   if (h<1)
                   {   if((startPoint.x()+w)>=2 && (startPoint.y()+h)>=2)
                       {
                       circle->setRect(startPoint.x(),startPoint.y(),w,h);
                       circleTag->setPlainText(QString::number((std::abs(w)*pixelPitch)/10,'f',2)+" cm");
                       }
                   }
                   else
                   {
                       if((startPoint.x()+w)>=2 && (h+startPoint.y())<=imgSizeBoundary-2)
                       {
                       circle->setRect(startPoint.x(),startPoint.y(),w,h);
                       circleTag->setPlainText(QString::number((std::abs(w)*pixelPitch)/10,'f',2)+" cm");
                       }

                   }
               }
               else
               {
                   if (h<1)
                   {
                       if((w+startPoint.x())<=imgSizeBoundary-2 && (startPoint.y()+h)>=2)
                       {
                       circle->setRect(startPoint.x(),startPoint.y(),w,h);
                       circleTag->setPlainText(QString::number((std::abs(w)*pixelPitch)/10,'f',2)+" cm");
                       }
                   }
                   else
                   {
                       qDebug()<<"wwww"<<w<<startPoint.x()<<h<<startPoint.y();
                       if((w+startPoint.x())<=imgSizeBoundary-2 && (h+startPoint.y())<=imgSizeBoundary-2)
                       {
                       circle->setRect(startPoint.x(),startPoint.y(),w,h);
                       circleTag->setPlainText(QString::number((std::abs(w)*pixelPitch)/10,'f',2)+" cm");
                       }
                   }
               }
           }

           break;
       }

      case DrawContour:
      {
        if(!path)
        {
            path=new QGraphicsPathItem;
            //                path->setFlag(QGraphicsItem::ItemIsMovable);
            this->addItem(path);
              qDebug() << "widthhhhhhhhhhhhh" ;
            drawPen=QPen(Qt::red, 2*(0.139/pixelPitch), Qt::SolidLine);

           // drawPen=QPen(Qt::red, (2*(6)), Qt::SolidLine);
            path->setPen(drawPen);
            path->setPos(origPoint);
            paintPath=new QPainterPath;
        }

       // qDebug()<<"Points "<<event->scenePos();
        CtPointList.append(event->scenePos());


        //                *paintPath=path->mapToScene(*paintPath);
        // connect the points to create path
        paintPath->lineTo(event->scenePos().x()-origPoint.x(),event->scenePos().y()-origPoint.y());
        //   qDebug()<<"event->scenePos()123"<<event->scenePos() <<event->scenePos().x()-origPoint.x() << event->scenePos().y()-origPoint.y();
        path->setPath(*paintPath);
        break;
    }

    case DrawRect:
    {
        if(ellip)
        {
            ellip = NULL;
        }

        QPointF point = event->scenePos(); // Get the current mouse position

        /* Find out how much mouse has moved from the initial point
             * X Direction movement = width of rectangle,y direction movement = height of rectangle*/


        int w = point.x()-origPoint.x();
        int h = point.y()-origPoint.y();


        if(!rect){

            // create new rectangle item
            rect = new QGraphicsRectItem;

            this->addItem(rect);
            rect->setFlag(QGraphicsItem::ItemIsMovable,true);
            rect->setPen(drawPen);
            //                rect->setFlag(QGraphicsItem::ItemSendsScenePositionChanges,true);
            rect->setZValue(1);


        }
        // adjust position
        if (w<1)
        {
            if (h<1)
            {
                rect->setRect(point.x(),point.y(),std::abs(w),std::abs(h));
            }
            else
            {
                rect->setRect(point.x(),origPoint.y(),std::abs(w),h);

            }
        }
        else
        {
            if (h<1)
            {
                rect->setRect(point.x(),point.y(),w,std::abs(h));
            }
            else
            {
                rect->setRect(origPoint.x(),origPoint.y(),w,h);

            }
        }

        break;

    }
    case DrawEllipse:
    {

        if(rect)
        {
            rect = NULL;
        }

        QPointF point = event->scenePos(); // Get the current mouse position

        /* Find out how much mouse has moved from the initial point
             * X Direction movement = width of rectangle,y direction movement = height of rectangle*/


        int w = point.x()-origPoint.x();
        int h = point.y()-origPoint.y();
        //            std::cout << "w: " << w << " h:" << h << std::endl;


        if(!ellip)
        {
            // create new rectangle item
            ellip = new QGraphicsEllipseItem;

            this->addItem(ellip);
            ellip->setPen(drawPen);
            ellip->setFlag(QGraphicsItem::ItemIsMovable,true);
            //                rect->setFlag(QGraphicsItem::ItemSendsScenePositionChanges,true);
            ellip->setZValue(1);
        }
        // adjust position
        if (w<1)
        {
            if (h<1)
            {
                ellip->setRect(point.x(),point.y(),std::abs(w),std::abs(h));
            }
            else
            {
                ellip->setRect(point.x(),origPoint.y(),std::abs(w),h);
            }
        }
        else
        {
            if (h<1)
            {
                ellip->setRect(point.x(),point.y(),w,std::abs(h));
            }
            else
            {
                ellip->setRect(origPoint.x(),origPoint.y(),w,h);
            }
        }

        break;

    }

    case DrawFree:
    {
        if(rect)
        {
            rect = NULL;

        }

        if(ellip)
        {
            ellip = NULL;

        }


        // mouse moved when creating ROI
        if(count==1)
        {
            if(!path)
            {

                path=new QGraphicsPathItem;
                //                path->setFlag(QGraphicsItem::ItemIsMovable);
                this->addItem(path);
                path->setPen(drawPen);
                path->setPos(origPoint);
                paintPath=new QPainterPath;
                myDrawingA=new Drawing;
                myDrawingA->pos=origPoint;
                myDrawingA->type="freehand";
            }
            myDrawingA->pointsList.append(event->scenePos());
            //                *paintPath=path->mapToScene(*paintPath);
            // connect the points to create path
            paintPath->lineTo(event->scenePos().x()-origPoint.x(),event->scenePos().y()-origPoint.y());
            path->setPath(*paintPath);

        }
        // moving ROI after it is drawn
        else
        {
            // adjust the position of rectangles in other scenes
            rectnew2->setRect(group->boundingRect());
            rectnew2->setPen(drawPen);
            if(tMode==0)
                rectnew2->setPos(QPointF(group->pos().x(),rectnew2->pos().y()));

            else
                rectnew2->setPos(QPointF(rectnew2->pos().x(),group->pos().y()));

            myDrawingB->rect1 = rectnew2->mapRectToScene(rectnew2->rect());

            // for 3D
            if(tMode==0)
            {
                rectnew3->setRect(group->boundingRect());
                rectnew3->setPen(drawPen);
                rectnew3->setPos(QPointF(group->pos().y(),rectnew3->pos().y()));
                myDrawingC->rect1 = rectnew3->mapRectToScene(rectnew3->rect());
            }

        }
        break;

    }
    case DilineatorMode:
        {
            if(workFMode==1&&ImaginMode==0&&FrameRateMode==1){
            //if(workFMode==1&&ImaginMode==0&&(FrameRateMode==1||FrameRateMode==2||FrameRateMode==3)){
                if (resizeUpdate!=1)
                    {

                    qDebug()<<"event scene "<<tLX<<tLY<<tRX<<tRY<<bLX<<bLY<<bRX<<bRY<<event->scenePos()<<origPoint1;

                    qDebug()<<"truefalse"<<((tLX+(event->scenePos().x()-origPoint1.x()))>0)<< ((tLY+(event->scenePos().y()-origPoint1.y()))>0) << ((tRX+(event->scenePos().x()-origPoint1.x()))<3072) << ((tRY+(event->scenePos().y()-origPoint1.y()))>0) << ((bLX+(event->scenePos().x()-origPoint1.x()))>0) << ((bLY+(event->scenePos().y()-origPoint1.y()))<3072) <<((bRX+(event->scenePos().x()-origPoint1.x()))<3072) <<((bRY+(event->scenePos().y()-origPoint1.y()))<3072);

//                    if(((tLX1+(event->scenePos().x()-origPoint1.x()))>1) && ((tLX1+(event->scenePos().x()-origPoint1.x()))<3071) && ((tLY1+(event->scenePos().y()-origPoint1.y()))>1) && ((tLY1+(event->scenePos().y()-origPoint1.y()))<3071) && ((tRX1+(event->scenePos().x()-origPoint1.x()))>1) && ((tRX1+(event->scenePos().x()-origPoint1.x()))<3071) && ((tRY1+(event->scenePos().y()-origPoint1.y()))>1) && ((tRY1+(event->scenePos().y()-origPoint1.y()))<3071) && ((bLX1+(event->scenePos().x()-origPoint1.x()))>1) && ((bLX1+(event->scenePos().x()-origPoint1.x()))<3071) && ((bLY1+(event->scenePos().y()-origPoint1.y()))>1) && ((bLY1+(event->scenePos().y()-origPoint1.y()))<3071) && ((bRX1+(event->scenePos().x()-origPoint1.x()))>1) && ((bRX1+(event->scenePos().x()-origPoint1.x()))<3071) && ((bRY1+(event->scenePos().y()-origPoint1.y()))>1) && ((bRY1+(event->scenePos().y()-origPoint1.y()))<3071))
//                    {
////                        tLX1 = tLX;
////                        tLY1 = tLY;
////                        tRY1 = tRY;
////                        tRX1 = tRX;
////                        bLX1 = bLX;
////                        bLY1 = bLY;
////                        bRX1 = bRX;
////                        bRY1 = bRY;
//                        rectDefault1->setFlag(QGraphicsItem::ItemIsMovable,true);
//                        tLX1 = tLX1+(event->scenePos().x()-origPoint1.x());
//                        tLY1 = tLY1+(event->scenePos().y()-origPoint1.y());
//                        tRY1 = tRY1+(event->scenePos().y()-origPoint1.y());
//                        tRX1 = tRX1+(event->scenePos().x()-origPoint1.x());
//                        bLX1 = bLX1+(event->scenePos().x()-origPoint1.x());
//                        bLY1 = bLY1+(event->scenePos().y()-origPoint1.y());
//                        bRX1 = bRX1+(event->scenePos().x()-origPoint1.x());
//                        bRY1 = bRY1+(event->scenePos().y()-origPoint1.y());

//                        accShiftX=accShiftX+(event->scenePos().x()-origPoint1.x());
//                        accShiftY=accShiftY+(event->scenePos().y()-origPoint1.y());

//                    }
//                    else
//                    {
//                        rectDefault1->setFlag(QGraphicsItem::ItemIsMovable,false);
//                        tLX1 = tLX1+(event->scenePos().x()-origPoint1.x());
//                        tLY1 = tLY1+(event->scenePos().y()-origPoint1.y());
//                        tRY1 = tRY1+(event->scenePos().y()-origPoint1.y());
//                        tRX1 = tRX1+(event->scenePos().x()-origPoint1.x());
//                        bLX1 = bLX1+(event->scenePos().x()-origPoint1.x());
//                        bLY1 = bLY1+(event->scenePos().y()-origPoint1.y());
//                        bRX1 = bRX1+(event->scenePos().x()-origPoint1.x());
//                        bRY1 = bRY1+(event->scenePos().y()-origPoint1.y());
                  //  }

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
                    }

            }
            break;

        }


    case ManualMode:
    {

    if(ContourBasedMovement==1)
    {

        if(itemTrackAP1>=0 && scene2->items().at(itemTrackAP1)->isUnderMouse() && pressedMovable==true)
        {
        posChanged = event->scenePos()-origPoint1;

        qDebug()<<"clicked Pos "<<event->scenePos()<<origPoint1<<pixelPitch<<boundX<<boundY;


        accPosXAP = accPosXAP+posChanged.x();  //How much Cursor is moved
        accPosYAP = accPosYAP+posChanged.y();

        qDebug()<<"clicked Pos1 "<<accPosXAP<<accPosYAP<<posChanged;

        if(std::abs(accPosXAP)<((boundX*10)/pixelPitch) && std::abs(accPosYAP)<((boundY*10)/pixelPitch))
        {
        scene2->items().at(itemTrackAP1)->moveBy(posChanged.x(),posChanged.y());
        qDebug()<<"PosAccXY"<<accPosXAP<<accPosYAP;
        origAccPosXAP = accPosXAP;  // How much content is moved
        origAccPosYAP = accPosYAP;
        }
        else if(std::abs(accPosXAP)<((boundX*10)/pixelPitch))
        {
        scene2->items().at(itemTrackAP1)->moveBy(posChanged.x(),0);
        qDebug()<<"PosAccX"<<accPosXAP<<accPosYAP;
        origAccPosXAP = accPosXAP;  // How much content is moved
        accPosYAP = origAccPosYAP;


        }

        else if(std::abs(accPosYAP)<((boundY*10)/pixelPitch))
        {
        scene2->items().at(itemTrackAP1)->moveBy(0,posChanged.y());
        qDebug()<<"PosAccY"<<accPosXAP<<accPosYAP;
        accPosXAP = origAccPosXAP;  // How much content is moved
        origAccPosYAP = accPosYAP;

        }

        else
        {
         accPosXAP=origAccPosXAP;
         accPosYAP=origAccPosYAP;
        }

        accPosYLAT = accPosYAP;
        origAccPosYLAT = origAccPosYAP;

        origPoint1 = event->scenePos();

        qDebug()<<"Posss"<<accPosXAP<<accPosYAP;
        }
    }
    else if(ContourBasedMovement==2)
    {
        if(itemTrackLAT1>=0 && scene2->items().at(itemTrackLAT1)->isUnderMouse() && pressedMovable==true)
        {
        posChanged = event->scenePos()-origPoint2;

        qDebug()<<"clicked Pos "<<event->scenePos()<<origPoint2;

        accPosXLAT = accPosXLAT+posChanged.x();  //How much Cursor is moved
        accPosYLAT = accPosYLAT+posChanged.y();


        if(std::abs(accPosXLAT)<((boundZ*10)/pixelPitch) && std::abs(accPosYLAT)<((boundY*10)/pixelPitch))
        {
        scene2->items().at(itemTrackLAT1)->moveBy(posChanged.x(),posChanged.y());

        qDebug()<<"PosAccXY"<<accPosXLAT<<accPosYLAT;
        origAccPosXLAT = accPosXLAT;  // How much content is moved
        origAccPosYLAT = accPosYLAT;


        }
        else if(std::abs(accPosXLAT)<((boundZ*10)/pixelPitch))
        {
        scene2->items().at(itemTrackLAT1)->moveBy(posChanged.x(),0);
        qDebug()<<"PosAccX"<<accPosXLAT<<accPosYLAT;
        origAccPosXLAT = accPosXLAT;  // How much content is moved
        accPosYLAT = origAccPosYLAT;

        }

        else if(std::abs(accPosYLAT)<((boundY*10)/pixelPitch))
        {
        scene2->items().at(itemTrackLAT1)->moveBy(0,posChanged.y());
        qDebug()<<"PosAccY"<<accPosXLAT<<accPosYLAT;
        accPosXLAT = origAccPosXLAT;  // How much content is moved
        origAccPosYLAT = accPosYLAT;


        }

        else
        {
         accPosXLAT=origAccPosXLAT;
         accPosYLAT=origAccPosYLAT;
        }

        accPosYAP = accPosYLAT;
        origAccPosYAP = origAccPosYLAT;

        origPoint2 = event->scenePos();
        qDebug()<<"Posss"<<accPosXLAT<<accPosYLAT<<accPosXAP<<accPosYAP;
        }
    }

    else
    {
    int s;
    if(this==scene1)
    {
    if(itemTrackAP>=0 && scene1->items().at(itemTrackAP)->isUnderMouse() && pressedMovable==true)
    {
    posChanged = event->scenePos()-origPoint1;

    qDebug()<<"clicked Pos "<<event->scenePos()<<origPoint1;

    accPosXAP = accPosXAP+posChanged.x();  //How much Cursor is moved
    accPosYAP = accPosYAP+posChanged.y();

    qDebug()<<"std::abs(posChanged)"<<std::abs(posChanged.x())<<std::abs(posChanged.y())<<10/pixelPitch;

    qDebug()<<"PosAcc12"<<accPosXAP<<accPosXAP;


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

    qDebug()<<"std::abs(posChanged)"<<std::abs(posChanged.x())<<std::abs(posChanged.y())<<10/pixelPitch;

    qDebug()<<"PosAcc12"<<accPosXLAT<<accPosYLAT;


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
    }

        break;
    }


    default:

        break;

    }
    QGraphicsScene::mouseMoveEvent(event);

}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // emit signals indicating draw/measure tools are drawn, save positions
    // delete / reset drawn items, clear flags/ variables

    qDebug()<<"releaseyj";

    if(event->scenePos()==origPoint&&(sceneMode!=DrawText))
    {
        //to enable  doubleclick on screen.
        QGraphicsScene::mouseReleaseEvent(event);
        return;
    }

    switch(sceneMode)

    {
    case DrawLine :
    {
        if(tMode==1)
        {
            if(!line)
                break;

            //emit signals  indicating measure tool is drawn
            emit measurementDrawn(line);
            emit measurementDrawn(lineTag);

            lineTag=0;
            line=0;
        }
        else if(tMode==0)
        {

            if(!line)
                break;

            //        //emit signals  indicating measure tool is drawn
            //        emit measurementDrawn(line);
            //        emit measurementDrawn(lineTag);

            //        lineTag=0;
            //        line=0;
            //        break;
            //  this->setMode(CustomScene::Mode::NoMode);
            QList<QGraphicsItem*> list;
            qDebug()<<"entered line";
            list.append(line);
            list.append(lineTag);

            group=this->createItemGroup(list);
            // group->setFlag(QGraphicsItem::ItemIsSelectable,false);
            group->setFlag(QGraphicsItem::ItemIsMovable,false);

            //  group=this->createItemGroup(list);
            // group->setFlag(QGraphicsItem::ItemIsSelectable,true);

            // emit measurementDrawn(group);

            //        this->addItem(lineTag);

            cbctDrawing=new Drawing;
            cbctDrawing->type="line";
            cbctDrawing->pos=origPoint;

            cbctDrawing->tag=lineTag->toPlainText();
            cbctDrawing->pointsList.append(line->line().p1());
            cbctDrawing->pointsList.append(line->line().p2());
            qDebug()<<"Releaseline-->"<<line->line();
            emit UpdatecbctDrawing(cbctDrawing);
            //  setMode(CustomScene::NoMode);
            emit measurementDrawn(line);
            emit measurementDrawn(lineTag);

            lineTag=0;
            line=0;

        }

        break;
    }

    case Drawrectcbct:
      {

   //output = ellip->mapRectToScene(ellip->rect());
          qDebug()<<"pixelPitchpixelPitch"<<pixelPitch;
       //   qDebug()<<"Drawrectcbct mode"<<Mode;
          QRectF pointsRect= rect->mapRectToScene(rect->rect());
          QList<float>stats= statsOfRectangle(image,pointsRect);
          QPointF center=QPointF((2*pointsRect.x()+pointsRect.width())/2,(2*pointsRect.y()+pointsRect.height())/2);
          rectTag=new QGraphicsTextItem;
          QFont serifFont("Times",6,QFont::Bold);
          rectTag->setPos(center);
          rectTag->setFont(serifFont);
          rectTag->setDefaultTextColor(Qt::yellow);
          rectTag->setAcceptHoverEvents(false);


         double area =  slope*(stats.at(1))+intercept;
         qDebug()<<"statsstatsstats"<<stats<<area;
         if(area > 0.0)
             area = area-300;
          qDebug()<<"statsstatsstats123"<<stats << area;

          QString data= "Area: "+QString::number((stats.at(0))*pixelPitch*pixelPitch,'f',1)
                  +"\n"+"Mean: "+QString::number(area,'f',1)
                  +"\n"+"Std Dev: "+QString::number(slope*(stats.at(2)*pixelPitch),'f',1);

        // qDebug()<<"pixel vale:"<<stats.at(1)<<"HU value:"<<slope*stats.at(1)+intercept << "  " << stats << pixelPitch;
          rectTag->setPlainText(data);
          this->addItem(rectTag);
          QList<QGraphicsItem*> list;
          list.append(rect);
          list.append(rectTag);
          group=this->createItemGroup(list);
          group->setFlag(QGraphicsItem::ItemIsSelectable,false);
        //  emit measurementDrawn(group);


          group->setFlag(QGraphicsItem::ItemIsMovable,false);

          cbctDrawing=new Drawing;
          cbctDrawing->type="cbctrectangle";
          cbctDrawing->pos=origPoint;
          cbctDrawing->tag=data;
          cbctDrawing->pointsList.append(QPointF(rect->rect().x(),rect->rect().y()));
          cbctDrawing->pointsList.append(QPointF(rect->rect().width(),rect->rect().height()));
          cbctDrawing->pointsList.append(center);
            emit UpdatecbctDrawing(cbctDrawing);
          emit measurementDrawn(group);


            rect=0;
            rectTag=0;
            group=0;




           setMode(CustomScene::NoMode);
        //  emit drawn(cbctDrawing);

          rectTag=0;
          rect=0;
          group=0;
          break;



      }



    case DrawCircle :
    {
        if(tMode==1)
        {
            if(!circle)
                break;

            // emit signals  indicating measure tool is drawn
            emit measurementDrawn(circle);
            emit measurementDrawn(circleTag);

            circle=0;
            circleTag=0;
        }
        else if(tMode==0)
        {

            if(!circle)
                break;

            cbctDrawing=new Drawing;
            cbctDrawing->type="circle";
            cbctDrawing->pos=startPoint;
            qDebug()<<"111";


            QRectF points= circle->mapRectToScene(circle->rect());

            QPointF center= QPointF((2*points.x()+points.width())/2,(2*points.y()+points.height())/2);
            qDebug()<<"1111";

            cbctDrawing->tag=circleTag->toPlainText();
            cbctDrawing->pointsList.append(QPointF(circle->rect().x(),circle->rect().y()));
            cbctDrawing->pointsList.append(QPointF(circle->rect().width(),circle->rect().height()));
            qDebug()<<"200";
            cbctDrawing->pointsList.append(center);
            // qDebug()<<"Releaseline-->"<<circle->line();
            emit UpdatecbctDrawing(cbctDrawing);
            emit measurementDrawn(circle);
            emit measurementDrawn(circleTag);


            circle=0;
            circleTag=0;


        }

        break;
    }

    case DrawAngle:
    {
        QList<QGraphicsItem*> list;

        //QList<QGraphicsItem*> list;
        qDebug()<<"777";
        // mouse released after drawing 1st line in the angle tool
        if(angleFlag)
        {
            if(!line){
                break;
            }
            angleFlag=false;
            qDebug()<<"8888";
            QLineF linePoints= line->line();
            angle=lineAngle(linePoints.p1(),linePoints.p2());
            cbctDrawing=new Drawing;
            cbctDrawing->pos=origPoint;
            cbctDrawing->type="angle";

            angleTag=new QGraphicsTextItem;
            if(tMode==1)
            {
                QFont serifFont("Times",(0.139*25)/(pixelPitch),QFont::Bold);
                angleTag->setDefaultTextColor(Qt::white);
                angleTag->setFont(serifFont);

            }
            else
            {
                QFont serifFont("Times",(0.139*25)/(pixelPitch),QFont::Bold);
                angleTag->setDefaultTextColor(Qt::yellow);
                angleTag->setFont(serifFont);
            }

            // QFont serifFont("Times",(drawToolThickness),QFont::Bold);
            startPoint=QPointF(line->line().x2()+startPoint.x(),line->line().y2()+startPoint.y());
            cbctDrawing->pointsList.append(startPoint);
            angleTag->setPos(startPoint);


            angleTag->setAcceptHoverEvents(false);
            this->addItem(angleTag);

            qDebug()<<"checkk";


            //            //added
            //            list.append(line);
            //            list.append(angleTag);
            //            group=this->createItemGroup(list);
            //            emit measurementDrawn(group);
            angleTag->setFlag(QGraphicsItem::ItemIsSelectable,false);
            line->setFlag(QGraphicsItem::ItemIsSelectable,false);

            emit measurementDrawn(line);
            emit measurementDrawn(angleTag);
            qDebug()<<"checkk1";
            // emit UpdatecbctDrawing(cbctDrawing);

            //            line = 0;


            //            startPoint=event->scenePos();
            mouseMoveEvent(event);
        }
        // mouse released after drawing 2nd line in angle tool(finished drawing angle tool)
        else if(!angleFlag)
        {

            if(!line2)
                break;

            angleFlag=true;
            startPoint=event->scenePos();

            //            list.append(line);
            //            list.append(line2);
            //            list.append(angleTag);

            //            group=this->createItemGroup(list);
            //            group->setFlag(QGraphicsItem::ItemIsSelectable,true);
            qDebug()<<"cfffff";
            //            emit measurementDrawn(group);
            cbctDrawing->pointsList.append(event->scenePos());
            list.append(line);
            list.append(line2);
            list.append(angleTag);
            angleTag->setFlag(QGraphicsItem::ItemIsSelectable,false);
            line2->setFlag(QGraphicsItem::ItemIsSelectable,false);


            //              //            emit measurementDrawn(group);
            qDebug()<<"cfffff1";
            cbctDrawing->tag=angleTag->toPlainText();
            emit measurementDrawn(line2);
            emit measurementDrawn(angleTag);
            qDebug()<<"c";
            if(tMode==0)
            {
                emit UpdatecbctDrawing(cbctDrawing);
            }
            //setMode(CustomScene::NoMode);
            line=0;
            angleTag=0;
            line2=0;
            //            group=0;
        }
        break;
    }
    case DrawRect:
    {
        RoiDrawn = 1 ;//anoop

        output = rect->mapRectToScene(rect->rect());
        this->setMode(CustomScene::Mode::NoMode);
        this->removeItem(rect);
        rect =NULL;
        delete rect;

        /*save the ROI's (type, position)to structure Drawing(both in scene1 and scene2)*/
        myDrawingA=new Drawing;
        myDrawingA->type="rectangle";
        myDrawingA->rect1 = output;

        myDrawingB = new Drawing;
        myDrawingB->type = "rectangle";
        myDrawingB->rect1 = output;

        // save for scene3 in 3D
        if(tMode==0)
        {
            myDrawingC = new Drawing;
            myDrawingC->type = "rectangle";
            myDrawingC->rect1 = output;

        }


        this->DrawRectSlot(output);
        count++;

        break;

    }
    case DrawEllipse:
    {

       // RoiDrawn = 2 ;//anoop

        output = ellip->mapRectToScene(ellip->rect());
        this->setMode(CustomScene::Mode::NoMode);
//        this->removeItem(ellip);
//        ellip = NULL;
//        delete ellip;
        count++;

        if(tMode==0)
        {
        QRectF points= ellip->mapRectToScene(ellip->rect());
        QPointF center= QPointF((2*points.x()+points.width())/2,(2*points.y()+points.height())/2);
        QRectF ellipParam=QRectF(center.x(),center.y(),points.width(),points.height());
        QList<float>stats= statsOfEllipse(image,ellipParam);
        QString data= "Area: "+QString::number((stats.at(0))*pixelPitch*pixelPitch,'f',1)
                +"\n"+"Mean: "+QString::number(slope*(stats.at(1))+intercept,'f',1)
                +"\n"+"Std Dev: "+QString::number(slope*(stats.at(2)*pixelPitch),'f',1);
        qDebug()<<"tttt";
        ellipTag=new QGraphicsTextItem;
       QFont serifFont("Times",6,QFont::Bold);
        ellipTag->setPos(center);
        ellipTag->setFont(serifFont);
        ellipTag->setDefaultTextColor(Qt::yellow);
        ellipTag->setAcceptHoverEvents(false);
        ellipTag->setPlainText(data);
       // this->addItem(ellipTag);
       ellip->setFlag(QGraphicsItem::ItemIsSelectable,true);
        QList<QGraphicsItem*> list;
        list.append(ellip);
        list.append(ellipTag);
        group=this->createItemGroup(list);
        group->setFlag(QGraphicsItem::ItemIsSelectable,true);
        qDebug()<<"Release-->"<<ellip->rect()<<ellipParam<< origPoint;
              cbctDrawing = new Drawing;
              cbctDrawing->pos=origPoint;
              cbctDrawing->type="ellipse";
              cbctDrawing->tag=data;
              cbctDrawing->pointsList.append(QPointF(ellip->rect().x(),ellip->rect().y()));
              cbctDrawing->pointsList.append(QPointF(ellip->rect().width(),ellip->rect().height()));
              cbctDrawing->pointsList.append(center);
              emit UpdatecbctDrawing(cbctDrawing);
              emit measurementDrawn(ellip);
              emit measurementDrawn(ellipTag);

              group=0;
              ellip=0;
              ellipTag=0;


        }



        break;

    }
    case DrawFree:
    {
        RoiDrawn = 3 ;//anoop
        // mouse released after drawing the ROI
        if(count==1)
        {
            QList<QGraphicsItem*> list;
            list.append(path);
            // add path to the graphics item group
            group=this->createItemGroup(list);
            group->setFlag(QGraphicsItem::ItemIsMovable,true);
            group->setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);

            myDrawingA->pointsList<<myDrawingA->pointsList.at(0);
            //pntlistxy.append(pntlistxy.at(0));//anoop

            for(int i=0;i<myDrawingA->pointsList.length();i++)
            {
                paintPath->lineTo(myDrawingA->pointsList.at(i).x()-myDrawingA->pos.x(),
                                  myDrawingA->pointsList.at(i).y()-myDrawingA->pos.y());

            }


            path->setPath(*paintPath);
            path->setPen(drawPen);

            // get the bounding rectangle around the freehand ROI
            QRectF output = group->boundingRect();
            myDrawingB=new Drawing;
            myDrawingB->type="rectangle";
            myDrawingB->rect1 = output;
            //            this->removeItem(path);
            path = NULL;
            delete path;

            // add the rectangle item (bounding rect around freehand ROI)to the other scenes
            rectnew2 = new QGraphicsRectItem;
            rectnew2->setPen(drawPen);
            if(changeScene==0)
            {
                scene2->addItem(rectnew2);

            }
            else
            {
                scene1->addItem(rectnew2);
                changeScene = 0;
                changeScene1 = 1;

            }
            rectnew2->setRect(myDrawingB->rect1);

            if(tMode==0)
            {
                myDrawingC=new Drawing;
                myDrawingC->type="rectangle";
                myDrawingC->rect1 = output;

                rectnew3 = new QGraphicsRectItem;
                rectnew3->setPen(drawPen);
                scene3->addItem(rectnew3);
                rectnew3->setRect(myDrawingC->rect1);
            }

            count++;// increment count indicating ROI is drawn

        }
        // mouse released after changing the position of ROI
        // get how much the ROI is shifted from the previous position
        else
        {
            posChanged = posChanged+(event->scenePos()-startPoint);
            myDrawingA->posChange = posChanged;
            qDebug()<<"anoop the pos change freehand"<<posChanged;
        }
        break;

    }
    case DrawText:
      {

          qDebug()<<"DrawText origPoint"<<origPoint;
          QList<QGraphicsItem*> list;
          text= new QGraphicsTextItem;
          TextitemFocusWatcher *focusitem=new TextitemFocusWatcher(text);
           qDebug()<<"DrawTextooo";
          connect(focusitem,SIGNAL(focuschanged(bool)),this,SLOT(updateText()));
          QFont serifFont("Times",6,QFont::Bold);
          text->setPos(origPoint);
          text->setFont(serifFont);

          text->setDefaultTextColor(Qt::yellow);
          text->setAcceptHoverEvents(false);
          text->setTextInteractionFlags(Qt::TextEditable);
          text->setFlag(QGraphicsItem::ItemIsSelectable,true);
          text->setFlag(QGraphicsItem::ItemIsMovable,true);
          text->setFocus();
          text->setHandlesChildEvents(false);
          text->setSelected(true);

          list.append(text);
          this->addItem(text);
          setMode(CustomScene::NoMode);
          emit measurementDrawn(text);
text=0;
  //        cbctDrawing = new Drawing;
  //        cbctDrawing->pos=origPoint;
  //        cbctDrawing->type="text";
  //        cbctDrawing->tag=text->toPlainText();
  //        emit UpdatecbctDrawing(cbctDrawing);
          //emit UpdateOutText();
          //text=0;
          break;
      }
    case DrawContour:
    {
        if(!path)
           return;
//        paintPath->lineTo(0,0);
//        CtPointList.append(origPoint);
        path->setPath(*paintPath);
        APLATrect1 = path->sceneBoundingRect();
        emit SendToDrawContour(CtPointList,path);
        break;
    }
    case ManualMode:
    {
       // if(itemAt(event->scenePos(),QTransform())->flags().testFlag(QGraphicsItem::ItemIsMovable)&&pressedMovable==true){
            pressedMovable=false;

            int s;
            // for 3D
            if(tMode==0){
                // move only in axial scene
                if (this==scene1){
                    count1++;
                    // get how much it is moved
                    posChanged = event->scenePos()-origPoint1;
                    s = 3;
                }
                qDebug()<<"position changed......"<<posChanged<<" "<<s;

            }
            // for 2D
            else{

                if(ContourBasedMovement==1)
                {
                    posChanged = QPointF(origAccPosXAP,origAccPosYAP)-prevPosChangedAP;
                    prevPosChangedAP = QPointF(origAccPosXAP,origAccPosYAP);
                    prevPosChangedLAT.ry()=prevPosChangedAP.ry();
                    //posChanged = QPointF(origAccPosXAP,origAccPosYAP);
                    s = 1;
                }
                else if (ContourBasedMovement==2)
                {
                    posChanged = QPointF(origAccPosXLAT,origAccPosYLAT)-prevPosChangedLAT;
                    prevPosChangedLAT = QPointF(origAccPosXLAT,origAccPosYLAT);
                    prevPosChangedAP.ry()=prevPosChangedLAT.ry();
                    //posChanged = event->scenePos()-origPoint2;
                    s = 2;
                }
                else
                {
                // in AP
                if (this==scene1){
                    count1++;
                    posChanged = QPointF(origAccPosXAP,origAccPosYAP)-prevPosChangedAP;
                    prevPosChangedAP = QPointF(origAccPosXAP,origAccPosYAP);
                    prevPosChangedLAT.ry()=prevPosChangedAP.ry();
                    //posChanged = QPointF(origAccPosXAP,origAccPosYAP);
                    s = 1;

//                    QList<QGraphicsItem*> itemList=scene2->items();
//                    for(int i=0;i<itemList.length();i++){

                    //scene1->items().at(itemTrackAP)->moveBy();
                         //if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList.at(i))&&itemList.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
                          // scene1->itemList.at(i)->moveBy(0,posChanged.y());
                    //}


                }
                // in LAT
                else{
                    count2++;
                    posChanged = QPointF(origAccPosXLAT,origAccPosYLAT)-prevPosChangedLAT;
                    prevPosChangedLAT = QPointF(origAccPosXLAT,origAccPosYLAT);
                    prevPosChangedAP.ry()=prevPosChangedLAT.ry();
                    //posChanged = event->scenePos()-origPoint2;
                    s = 2;

//                      QList<QGraphicsItem*> itemList=scene1->items();
//                      for(int i=0;i<itemList.length();i++){

//                           if(qgraphicsitem_cast<QGraphicsPixmapItem*>(itemList.at(i))&&itemList.at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
//                             itemList.at(i)->moveBy(0,posChanged.y());
//                      }


                }
                qDebug()<<"position changed......"<<posChanged<<" "<<s;
            }
            // send the change in position to mainwindow to calculate x,y,z shifts



            emit positionChanged(posChanged,s);
            }
            qDebug()<<"position changed emitted......";
      //  }
        break;
    }
    case DilineatorMode:
    {

        if(workFMode==1&&ImaginMode==0&&FrameRateMode==1){
        //if(workFMode==1&&ImaginMode==0&&(FrameRateMode==1||FrameRateMode==2||FrameRateMode==3)){
        if (resizeUpdate==0) //Move Dilineator
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



    //        centerDilX = centerTempX + (curX-prevX);
    //        centerDilY = centerTempY + (curY-prevY);

    //        qDebug() <<"centers "<<centerDilX<<centerDilY;
    //        qDebug() <<"topLeft "<<tLX<<tLY;
            }

            else if (round(abs(curRectPosX-prevRectPosX))==0 && round(abs(curRectPosY-prevRectPosY))==0)
            {
              centerDilX = centerTempX;
              centerDilY = centerTempY;
            }
            }

        else //Resize Dilineator
        {
            /*Added*/

            QPointF curPoints;

            if(event->scenePos().x()<2)
                curPoints.setX(2);
            else if(event->scenePos().x()>3070)
                curPoints.setX(3070);
            else
                curPoints.setX(event->scenePos().x());
            if(event->scenePos().y()<2)
                curPoints.setY(2);
            else if(event->scenePos().y()>3070)
                curPoints.setY(3070);
            else
                curPoints.setY(event->scenePos().y());


            RotatingDilPositions(curPoints);


                       tLX = ctLX;
                       tLY = ctLY;
                       tRX = ctRX;
                       tRY = ctRY;
                       bLX = cbLX;
                       bLY = cbLY;
                       bRX = cbRX;
                       bRY = cbRY;

                       centerDilX = (tLX+bRX)/2;
                       centerDilY = (tLY+bRY)/2;

                       accShiftX=0;
                       accShiftY=0;


    //            /*Added*/
        }

//        resetDilineator(dTheta);

//        if(rectSizeGripItem1)
//            delete rectSizeGripItem1;

//        delete rectDefault1;
//        rectDefault1=NULL;
//        rectDefault1= new CustomItem();
//        this->addItem(rectDefault1);

//        rectDefault1->setRect(ctLX,ctLY,cbRX-ctLX,cbRY-ctLY);
//        rectDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));

//        rectDefault1->setRotation((qreal)dTheta*(180/3.14));
//        rectDefault1->setTransformOriginPoint(isocenterX,isocenterY);

//        rectDefault1->resetTransform();
//        rectDefault1->show();

////        if(resizeUpdate!=0)
////        {


//            rectSizeGripItem1 =new SizeGripItem(new RectResizer, rectDefault1);
//            QObject::disconnect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToDilineatorResize(QRectF,int)));
//            QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToDilineatorResize(QRectF,int)));
//       // }




      qDebug() <<"Enter topLeft Center"<<centerDilX << centerDilY;

    //    qDebug() <<" topLeft"<<tLX<<tLY<<tRX<<tRY<<bLX<<bLY<<bRX<<bRY;

    //    qDebug() <<"event->scene "<<event->scenePos().rx()<<event->scenePos().ry();

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

    //    if(!((tRX==tLX)&&(tRY==tLY)))
    //        //atan((tRY-tLY)/(tRX-tLX));
    //    else
    //        invangle=0;

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


        /*Calculating intial Dilineator Center*/



              QList<double> plannedValue;
                double pixelPitch = imaginPixelSpacing;
                plannedValue.append((ctLX-prevIsoCenterX)*pixelPitch);
                plannedValue.append((cbRX-prevIsoCenterX)*pixelPitch);
                plannedValue.append(-(cbRY-prevIsoCenterY)*pixelPitch);
                plannedValue.append(-(ctLY-prevIsoCenterY)*pixelPitch);

                plannedValue.append((centerTempX-prevIsoCenterX)*pixelPitch);
                plannedValue.append(-(centerTempY-prevIsoCenterY)*pixelPitch);


                plannedValue.append((0.0));
                plannedValue.append(rTheta);

                plannedValue.append((initCenterX-prevIsoCenterX)*pixelPitch);
                plannedValue.append(-(initCenterY-prevIsoCenterY)*pixelPitch);

    //          double pixelPitch = imaginPixelSpacing;
    //          plannedValue.append((ctLX-isocenterX)*pixelPitch);
    //          plannedValue.append((cbRX-isocenterX)*pixelPitch);
    //          plannedValue.append(-(cbRY-isocenterY)*pixelPitch);
    //          plannedValue.append(-(ctLY-isocenterY)*pixelPitch);

    //          plannedValue.append((centerTempX-isocenterX)*pixelPitch);
    //          plannedValue.append(-(centerTempY-isocenterY)*pixelPitch);


    //          plannedValue.append((0.0));
    //          plannedValue.append(rTheta);

    //          plannedValue.append((initCenterX-isocenterX)*pixelPitch);
    //          plannedValue.append(-(initCenterY-isocenterY)*pixelPitch);

           emit  UpdatePlannedVlue(plannedValue);
            ////////////////////  ///////////////////////

            resizeUpdate=0;
        }
        break;
    }
    default:    
        break;
    }




    QGraphicsScene::mouseReleaseEvent(event);
    pressed = false;

}

void CustomScene::resetDilineator(double theta)
{
    float cTheta = -theta*(3.14/180);


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

}
void CustomScene::updateText()
{
    qDebug()<<"update text called"<<text;
    if(text){
           qDebug()<<"entered text"<<text;
        if(!text->toPlainText().isEmpty()){
            cbctDrawing = new Drawing;
            cbctDrawing->pos=origPoint;
            cbctDrawing->type="text";
            cbctDrawing->tag=text->toPlainText();
            emit UpdatecbctDrawing(cbctDrawing);
            qDebug()<<"text measure updated";
        }
        else{
             qDebug()<<"else";
            removeItem(text);
            delete text;
        }
        setMode(CustomScene::NoMode);
        text=0;
    }
}


void CustomScene::respondToDilineatorResize(QRectF rect12,int k)
{
    k=1;

    qDebug()<<"Entering resizer5.......";

    float cTheta = rTheta*(3.14/180);

    float topLeftCurValueX,topLeftCurValueY,topRightCurValueX,topRightCurValueY,bottomLeftCurValueX,bottomLeftCurValueY,bottomRightCurValueX,bottomRightCurValueY;

    float tempX = rect12.x()-isocenterX;
    float tempY = rect12.y()-isocenterY;

    topLeftCurValueX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    topLeftCurValueY = tempX*sin(cTheta)+tempY*cos(cTheta);

    topLeftCurValueX = topLeftCurValueX+isocenterX;
    topLeftCurValueY = topLeftCurValueY+isocenterY;

    tempX = rect12.width()+rect12.x()-isocenterX;
    tempY = rect12.y()-isocenterY;

    topRightCurValueX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    topRightCurValueY = tempX*sin(cTheta)+tempY*cos(cTheta);

    topRightCurValueX = topRightCurValueX+isocenterX;
    topRightCurValueY = topRightCurValueY+isocenterY;

    tempX = rect12.x()-isocenterX;
    tempY = rect12.height()+rect12.y()-isocenterY;

    bottomLeftCurValueX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    bottomLeftCurValueY = tempX*sin(cTheta)+tempY*cos(cTheta);

    bottomLeftCurValueX = bottomLeftCurValueX+isocenterX;
    bottomLeftCurValueY = bottomLeftCurValueY+isocenterY;

    tempX = rect12.x()+rect12.width()-isocenterX;
    tempY = rect12.height()+rect12.y()-isocenterY;

    bottomRightCurValueX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    bottomRightCurValueY = tempX*sin(cTheta)+tempY*cos(cTheta);

    bottomRightCurValueX = bottomRightCurValueX+isocenterX;
    bottomRightCurValueY = bottomRightCurValueY+isocenterY;



//    if(rectDefault1->sceneBoundingRect().topLeft().x()+topLeftDiffX<1 || rectDefault1->sceneBoundingRect().topLeft().x()+topLeftDiffX>3071 || rectDefault1->sceneBoundingRect().topRight().x()+topRightDiffX>1  || rectDefault1->sceneBoundingRect().topRight().x()+topRightDiffX<3071 || rectDefault1->sceneBoundingRect().topLeft().y()+topLeftDiffY<1 || rectDefault1->sceneBoundingRect().topLeft().y()+topLeftDiffY>3071 || rectDefault1->sceneBoundingRect().topRight().y()+topRightDiffY<1 || rectDefault1->sceneBoundingRect().topRight().y()+topRightDiffY>3071 || rectDefault1->sceneBoundingRect().bottomLeft.x()+bottomLeftDiffX<1 || rectDefault1->sceneBoundingRect().bottomLeft.x()+bottomLeftDiffX>3071 || rectDefault1->sceneBoundingRect().bottomLeft().y()+bottomLeftDiffY<1 || rectDefault1->sceneBoundingRect().bottomLeft().y()+bottomLeftDiffY>3071 || rectDefault1->sceneBoundingRect().bottomRight().x()+bottomRightDiffX<1 || rectDefault1->sceneBoundingRect().bottomRight().x()+bottomRightDiffX>3071 || rectDefault1->sceneBoundingRect().bottomRight().y()+bottomRightDiffY<1 || rectDefault1->sceneBoundingRect().bottomRight().y()+bottomRightDiffY>3071 )
//        rectSizeGripItem1->setEnabled(false);

    qDebug()<<"event scenttLXeResize "<<tLX<<tLY<<tRX<<tRY<<bLX<<bLY<<bRX<<bRY;


//    dTheta = rotateStep;//rotation step
//    cTheta = (dTheta+rTheta)*(3.14/180);

    qDebug()<<"rectDefault1->sceneBoundingRect().topLeft().x()"<<rectDefault1->sceneBoundingRect().topLeft().x()<<rectDefault1->sceneBoundingRect().topRight().x()<<topLeftDiffX<<topRightDiffX;

    qDebug()<<"RectPoints"<<rect12.x()<<rect12.y()<<rect12.width()<<rect12.height()<<topLeftCurValueX<<topLeftDiffX;



}



void CustomScene::DrawRectSlot(QRectF output)
{
    // add resizable rectangle/ ellipse (with size grip items for resizing)

    switch (sceneMode1) {
    case DrawRect:
    {
        // add rectangle to the scene
        rectItem1 = new CustomItem;
        rectItem1->setRect(QRectF(0,0,output.width(),output.height()));
        rectItem1->setPos(output.x(),output.y());
        rectItem1->setPen(drawPen);
        if(changeScene==0)
        {
            scene1->addItem(rectItem1);

        }
        else
        {
            scene2->addItem(rectItem1);

        }
        rect1 = rectItem1->mapRectToScene(rectItem1->rect());
        // add size grip items to the rectangles
        rectSizeGripItem1 =new SizeGripItem(new RectResizer, rectItem1);
        QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem(QRectF,int)));
        QObject::connect(rectItem1,SIGNAL(itemChanged(QPointF)),this,SLOT(respondToitemChange(QPointF)));
        break;

    }


    case DrawEllipse:
    {
        // add ellipse to the scene
        ellipseItem1 = new CustomItemEllipse;
        ellipseItem1->setRect(QRectF(0,0,output.width(),output.height()));
        ellipseItem1->setPos(output.x(),output.y());
        ellipseItem1->setPen(drawPen);
        if(changeScene==0)
        {

            scene1->addItem(ellipseItem1);

        }
        else
        {
            scene2->addItem(ellipseItem1);

        }
        rect1 = ellipseItem1->mapRectToScene(ellipseItem1->rect());
        // add size grip items to the ellipse
        rectSizeGripItem1 =new SizeGripItem(new EllipseResizer, ellipseItem1);
        QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem(QRectF,int)));
        QObject::connect(ellipseItem1,SIGNAL(itemChanged(QPointF)),this,SLOT(respondToitemChange(QPointF)));
        break;

    }
    default:
        break;
    }

    // add corresponding rectangles to other scene
    rectItem2 = new CustomItem;
    rectItem2->setRect(QRectF(0,0,output.width(),output.height()));
    rectItem2->setPos(output.x(),output.y());
    rectItem2->setPen(drawPen);

    if(changeScene==0)
    {
        scene2->addItem(rectItem2);
    }
    else
    {
        scene1->addItem(rectItem2);
        changeScene = 0;
        changeScene1 = 1;
    }
    rect2 = rectItem2->mapRectToScene(rectItem2->rect());
    // add size grip item to rectangle 2
    rectSizeGripItem2 =new SizeGripItem(new RectResizer, rectItem2);
    QObject::connect(rectSizeGripItem2,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem1(QRectF,int)));
    QObject::connect(rectItem2,SIGNAL(itemChanged(QPointF)),this,SLOT(respondToitemChange1(QPointF)));

    // for 3D, add rectangle to 3rd scene
    if(tMode==0)
    {
        rectItem3 = new CustomItem;
        rectItem3->setRect(QRectF(0,0,output.width(),output.height()));
        rectItem3->setPos(output.x(),output.y());

        rectItem3->setPen(drawPen);
        scene3->addItem(rectItem3);

        rect3 = rectItem3->mapRectToScene(rectItem3->rect());
        // add size grip item to rectangle 3
        rectSizeGripItem3 =new SizeGripItem(new RectResizer, rectItem3);
        QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));
        QObject::connect(rectItem3,SIGNAL(itemChanged(QPointF)),this,SLOT(respondToitemChange2(QPointF)));

    }

}
void CustomScene::respondToitem(QRectF rectn, int k)
{
    rect2 = (rectItem2->rect());

    // when the scene1 ROI item is moved but not resized using size grip item
    if(k==0)
    {
        if(tMode==0)
        {
            // ignore signals from scene2 ROI item movement
            rectItem2->blockSignals(true);
            // set to postion from size grip item
            rectItem2->setX(rectn.x());
            // allow signals from scene2 ROI item movement
            rectItem2->blockSignals(false);

            rect3 = (rectItem3->rect());
            // for scene3 ROI item
            rectItem3->blockSignals(true);
            rectItem3->setX(rectn.y());
            rectItem3->blockSignals(false);
            delete rectSizeGripItem3;
            rectSizeGripItem3 =new SizeGripItem(new RectResizer, rectItem3);
            QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));
            myDrawingC->rect1 = rectItem3->mapRectToScene(rectItem3->rect());

        }
        else
        {
            // ignore signals from scene2 ROI item movement
            rectItem2->blockSignals(true);
            // set to postion from size grip item
            rectItem2->setY(rectn.y());
            // allow signals from scene2 ROI item movement
            rectItem2->blockSignals(false);

        }

    }
    // when the scene1 ROI item is resized using size grip item
    else
    {
        if(tMode==0)
        {
            // adjust the position& size of scene2 & scene3 ROI items
            rectItem2->setRect(QRectF(rectn.x(),rect2.y(),rectn.width(),rect2.height()));
            rect3 = (rectItem3->rect());
            rectItem3->setRect(QRectF(rectn.y(),rect3.y(),rectn.height(),rect3.height()));
            delete rectSizeGripItem3;
            rectSizeGripItem3 =new SizeGripItem(new RectResizer, rectItem3);
            QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));
            myDrawingC->rect1 = rectItem3->mapRectToScene(rectItem3->rect());
        }
        else
            // adjust the position& size of scene2  ROI item
            rectItem2->setRect(QRectF(rect2.x(),rectn.y(),rect2.width(),rectn.height()));
    }

    delete rectSizeGripItem2;
    rectSizeGripItem2 =new SizeGripItem(new RectResizer, rectItem2);
    QObject::connect(rectSizeGripItem2,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem1(QRectF,int)));

    if(k==0)
    {
        myDrawingA->rect1 = rectn;

    }
    else
    {
        // ellipse mode
        if(sceneMode1==3)
            myDrawingA->rect1 = ellipseItem1->mapRectToScene(rectn);
        // rectangle mode
        else if(sceneMode1==4)
            myDrawingA->rect1 = rectItem1->mapRectToScene(rectn);


    }

    myDrawingB->rect1 = rectItem2->mapRectToScene(rectItem2->rect());


}

void CustomScene::respondToitem1(QRectF rectn, int k)
{

    // when the scene2 ROI item is moved but not resized using size grip item
    switch (sceneMode1) {
    case DrawRect:
    {
        rect1 = (rectItem1->rect());
        if(k==0)
        {
            // ignore signals from scene1 ROI item movement
            // set to postion from size grip item
            // allow signals from scene1 ROI item movement

            if(tMode==0)
            {
                rectItem1->blockSignals(true);
                rectItem1->setX(rectn.x());
                rectItem1->blockSignals(false);
            }
            else
            {

                rectItem1->blockSignals(true);
                rectItem1->setY(rectn.y());
                rectItem1->blockSignals(false);
            }

        }
        // when the scene2 ROI item is resized using size grip item
        // adjust the position& size of scene1  ROI item

        else
        {
            if(tMode==0)
            {
                rectItem1->setRect(QRectF(rectn.x(),rect1.y(),rectn.width(),rect1.height()));

            }
            else

                rectItem1->setRect(QRectF(rect1.x(),rectn.y(),rect1.width(),rectn.height()));
        }


        delete rectSizeGripItem1;
        rectSizeGripItem1 =new SizeGripItem(new RectResizer, rectItem1);
        QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem(QRectF,int)));
        myDrawingA->rect1 = rectItem1->mapRectToScene(rectItem1->rect());;

        break;
    }
    case DrawEllipse:
    {

        rect1 = (ellipseItem1->rect());
        if(k==0)
        {
            // ignore signals from scene1 ROI item movement
            // set to postion from size grip item
            // allow signals from scene1 ROI item movement
            if(tMode==0)
            {
                ellipseItem1->blockSignals(true);
                ellipseItem1->setX(rectn.x());
                ellipseItem1->blockSignals(false);
            }
            else
            {
                ellipseItem1->blockSignals(true);
                ellipseItem1->setY(rectn.y());
                ellipseItem1->blockSignals(false);
            }

        }
        // when the scene2 ROI item is resized using size grip item
        // adjust the position& size of scene1  ROI item
        else
        {
            if(tMode==0)
                ellipseItem1->setRect(QRectF(rectn.x(),rect1.y(),rectn.width(),rect1.height()));
            else

                ellipseItem1->setRect(QRectF(rect1.x(),rectn.y(),rect1.width(),rectn.height()));

            delete rectSizeGripItem1;
            rectSizeGripItem1 =new SizeGripItem(new EllipseResizer, ellipseItem1);
            QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem(QRectF,int)));
            myDrawingA->rect1 = ellipseItem1->mapRectToScene(ellipseItem1->rect());;

        }

        break;

    }

    }
    // adjust the position& size of scene3  ROI item
    if(tMode==0)
    {
        rect3 = (rectItem3->rect());
        if(k==0){
            rectItem3->blockSignals(true);
            rectItem3->setY(rectn.y());
            rectItem3->blockSignals(false);
        }
        else
            rectItem3->setRect(QRectF(rect3.x(),rectn.y(),rect3.width(),rectn.height()));
        delete rectSizeGripItem3;
        rectSizeGripItem3 =new SizeGripItem(new RectResizer, rectItem3);
        QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));
        myDrawingC->rect1 = rectItem3->mapRectToScene(rectItem3->rect());

    }
    if(k==0)
    {
        myDrawingB->rect1 = rectn;

    }
    else
        myDrawingB->rect1 = rectItem2->mapRectToScene(rectn);

}



void CustomScene::respondToitem2(QRectF rectn, int k)
{

    switch (sceneMode1) {
    case DrawRect:
    {
        rect1 = (rectItem1->rect());
        // when the scene3 ROI item is moved but not resized using size grip item
        if(k==0){
            // ignore signals from scene1 ROI item movement
            // set to postion from size grip item
            // allow signals from scene1 ROI item movement
            rectItem1->blockSignals(true);
            rectItem1->setY(rectn.x());
            rectItem1->blockSignals(false);
        }
        // when the scene3 ROI item is resized using size grip item
        // adjust the position& size of scene1  ROI item
        else{
            rectItem1->setRect(QRectF(rect1.x(),rectn.x(),rect1.width(),rectn.width()));

        }

        delete rectSizeGripItem1;
        rectSizeGripItem1 =new SizeGripItem(new RectResizer, rectItem1);
        QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem(QRectF,int)));
        myDrawingA->rect1 = rectItem1->mapRectToScene(rectItem1->rect());

        break;
    }
    case DrawEllipse:
    {

        rect1 = (ellipseItem1->rect());
        // when the scene3 ROI item is moved but not resized using size grip item
        if(k==0){
            // ignore signals from scene1 ROI item movement
            // set to postion from size grip item
            // allow signals from scene1 ROI item movement
            ellipseItem1->blockSignals(true);
            ellipseItem1->setY(rectn.x());
            ellipseItem1->blockSignals(false);
        }
        // when the scene3 ROI item is resized using size grip item
        // adjust the position& size of scene3  ROI item
        else{
            ellipseItem1->setRect(QRectF(rect1.x(),rectn.x(),rect1.width(),rectn.width()));
        }
        delete rectSizeGripItem1;
        rectSizeGripItem1 =new SizeGripItem(new RectResizer, ellipseItem1);
        QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem(QRectF,int)));
        myDrawingA->rect1 = ellipseItem1->mapRectToScene(ellipseItem1->rect());

        break;
    }
    }
    rect2 = (rectItem2->rect());

    // when the scene3 ROI item is moved but not resized using size grip item
    // ignore signals from scene2 ROI item movement
    // set to postion from size grip item
    // allow signals from scene2 ROI item movement
    if(k==0){
        rectItem2->blockSignals(true);
        rectItem2->setY(rectn.y());
        rectItem2->blockSignals(false);
    }
    // when the scene3 ROI item is resized using size grip item
    // adjust the position& size of scene2  ROI item
    else
        rectItem2->setRect(QRectF(rect2.x(),rectn.y(),rect2.width(),rectn.height()));
    delete rectSizeGripItem2;
    rectSizeGripItem2 =new SizeGripItem(new RectResizer, rectItem2);
    QObject::connect(rectSizeGripItem2,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem1(QRectF,int)));



    myDrawingB->rect1 = rectItem2->mapRectToScene(rectItem2->rect());
    if(k==0)
    {
        myDrawingC->rect1 = rectn;

    }
    else
        myDrawingC->rect1 = rectItem3->mapRectToScene(rectn);


}





void CustomScene::respondToitemChange(QPointF pos)
{
    // when the scene1 ROI is moved, get the current positions
    switch (sceneMode1) {
    case DrawRect:
    {
        rect1 = rectItem1->mapRectToScene(rectItem1->rect());
        //        rect1 = (rectItem1->rect());

        break;
    }
    case DrawEllipse:
    {
        rect1 = ellipseItem1->mapRectToScene(ellipseItem1->rect());
        break;
    }
    default:
        break;
    }

    QRectF rectangle = QRectF(pos.x(),pos.y(),rect1.width(),rect1.height());
    // call function to respond to the change in position of scene1 ROI
    this->respondToitem(rectangle,0);

}

void CustomScene::respondToitemChange1(QPointF pos)
{
    // when the scene2 ROI is moved, get the current positions
    rect2 = rectItem2->mapRectToScene(rectItem2->rect());

    QRectF rectangle = QRectF(pos.x(),pos.y(),rect2.width(),rect2.height());
    // call function to respond to the change in position of scene2 ROI
    this->respondToitem1(rectangle,0);
}

void CustomScene::respondToitemChange2(QPointF pos)
{
    // when the scene3 ROI is moved, get the current positions
    rect3 = rectItem3->mapRectToScene(rectItem3->rect());
    QRectF rectangle = QRectF(pos.x(),pos.y(),rect3.width(),rect3.height());
    // call function to respond to the change in position of scene3 ROI
    this->respondToitem2(rectangle,0);
}



QList<Drawing*>CustomScene::redrawRect()
{
    // function to redraw ROIs on the scenes
    QList<Drawing*> drawinglist;

    CustomScene::Mode mode= getMode(myDrawingA->type);


    QRectF movingmask = QRectF(myDrawingA->rect1.x()-5,myDrawingA->rect1.y()-5,myDrawingA->rect1.width()+10
                               ,myDrawingA->rect1.height()+10);
    QRectF movingmask1 = QRectF(myDrawingB->rect1.x()-5,myDrawingB->rect1.y()-5,myDrawingB->rect1.width()+10
                                ,myDrawingB->rect1.height()+10);
    QRectF movingmask2 ;
    if(myDrawingC)
    {
        //        qDebug()<<"3D";

        movingmask2 = QRectF(myDrawingC->rect1.x()-5,myDrawingC->rect1.y()-5,myDrawingC->rect1.width()+10
                             ,myDrawingC->rect1.height()+10);

    }

    qDebug()<<mode;
    switch(mode)
    {
    case DrawRect:
    {
        rectnew1 = new QGraphicsRectItem;
        rectMoving1 = new QGraphicsRectItem;

        rectnew2 = new QGraphicsRectItem;
        rectMoving2 =new QGraphicsRectItem;

        rectnew1->setPen(drawPen);
        rectnew2->setPen(drawPen);

        rectMoving1->setPen(movingPen);
        rectMoving2->setPen(movingPen);


        if(changeScene1==1)
        {
            scene2->addItem(rectnew1);
            rectnew1->setRect(myDrawingA->rect1);

            scene2->addItem(rectMoving1);
            rectMoving1->setRect(movingmask);

            scene1->addItem(rectnew2);
            rectnew2->setRect(myDrawingB->rect1);

            scene1->addItem(rectMoving2);
            rectMoving2->setRect(movingmask1);
        }
        else
        {
            scene1->addItem(rectnew1);
            rectnew1->setRect(myDrawingA->rect1);

            scene1->addItem(rectMoving1);
            rectMoving1->setRect(movingmask);

            scene2->addItem(rectnew2);
            rectnew2->setRect(myDrawingB->rect1);

            scene2->addItem(rectMoving2);
            rectMoving2->setRect(movingmask1);
        }


        break;


    }
    case DrawEllipse:
    {
        ellipnew1 = new QGraphicsEllipseItem;

        ellipMoving1 = new QGraphicsEllipseItem;

        rectnew2 = new QGraphicsRectItem;

        rectMoving2 =new QGraphicsRectItem;

        ellipnew1->setPen(drawPen);
        rectnew2->setPen(drawPen);

        ellipMoving1->setPen(movingPen);
        rectMoving2->setPen(movingPen);


        if(changeScene1==1)
        {
            scene2->addItem(ellipnew1);
            ellipnew1->setRect(myDrawingA->rect1);

            scene2->addItem(ellipMoving1);
            ellipMoving1->setRect(movingmask);

            scene1->addItem(rectnew2);
            rectnew2->setRect(myDrawingB->rect1);

            scene1->addItem(rectMoving2);
            rectMoving2->setRect(movingmask1);
        }


        else
        {
            scene1->addItem(ellipnew1);
            ellipnew1->setRect(myDrawingA->rect1);

            scene1->addItem(ellipMoving1);
            ellipMoving1->setRect(movingmask);

            scene2->addItem(rectnew2);
            rectnew2->setRect(myDrawingB->rect1);

            scene2->addItem(rectMoving2);
            rectMoving2->setRect(movingmask1);
        }

        break;
    }

    case DrawFree:
    {

        path=new QGraphicsPathItem;
        path->setPos(myDrawingA->pos);
        paintPath=new QPainterPath;

        paintPath->moveTo(0,0);


        pathMoving = new QGraphicsPathItem;
        pathMoving->setPos(myDrawingA->pos);

        //        pathMoving->setPos(myDrawing->pos.x()+5,myDrawing->pos.y()+5);

        QPainterPath *paintPath1;
        paintPath1=new QPainterPath;
        //        paintPath1->moveTo(0,0);


        for(int i=1;i<myDrawingA->pointsList.length();i++)
        {
            paintPath->lineTo(myDrawingA->pointsList.at(i).x()-myDrawingA->pos.x(),
                              myDrawingA->pointsList.at(i).y()-myDrawingA->pos.y());
            //            paintPath1->lineTo(myDrawing->pointsList.at(i).x()-myDrawing->pos.x(),
            //                               myDrawing->pointsList.at(i).y()-myDrawing->pos.y());
        }
        paintPath->translate(myDrawingA->posChange);
        path->setPath(*paintPath);
        path->setPen(drawPen);
        paintPath1 = paintPath;


        //        paintPath1->translate(myDrawing->posChange);
        //        pathMoving->setPath(*paintPath1);
        //        pathMoving->setPen(QPen(Qt::white, 1, Qt::SolidLine));

        //        pathMoving->setScale(1.5);
        //        pathMoving->setTransformOriginPoint(path->transformOriginPoint());
        //        pathMoving->setPos(0,0);


        QPainterPathStroker stroker;

        stroker.setWidth(20);
        stroker.setJoinStyle(Qt::MiterJoin); // and other adjustments you need
        QPainterPath newpath = (stroker.createStroke(*paintPath) + *paintPath).simplified();

        pathMoving->setPath(newpath);
        pathMoving->setPen(movingPen);

        rectnew2 = new QGraphicsRectItem;
        rectnew2->setPen(drawPen);

        rectMoving2 =new QGraphicsRectItem;

        rectMoving2->setPen(movingPen);



        if(changeScene1==1)
        {
            scene2->addItem(path);
            scene2->addItem(pathMoving);

            scene1->addItem(rectnew2);
            rectnew2->setRect(myDrawingB->rect1);
            scene1->addItem(rectMoving2);
            rectMoving2->setRect(movingmask1);
        }
        else
        {
            scene1->addItem(path);
            //            scene2->addItem(path);
            scene1->addItem(pathMoving);
            scene2->addItem(rectnew2);
            rectnew2->setRect(myDrawingB->rect1);
            scene2->addItem(rectMoving2);
            rectMoving2->setRect(movingmask1);
        }

    }

    default:
        break;
    }

    if(myDrawingC)
    {
        rectnew3 = new QGraphicsRectItem;
        rectMoving3 =new QGraphicsRectItem;

        rectnew3->setPen(drawPen);
        rectMoving3->setPen(movingPen);

        scene3->addItem(rectnew3);
        rectnew3->setRect(myDrawingC->rect1);

        scene3->addItem(rectMoving3);
        rectMoving3->setRect(movingmask2);



    }
    drawinglist<< myDrawingA;
    drawinglist<< myDrawingB;

    if(myDrawingC)
    {
        drawinglist<< myDrawingC;
    }
    return drawinglist;

    //    return myDrawing,myDrawingB;

}


returnList* CustomScene::returnDrawing()
{
    // return the list of drawn items
    returnList *L;
    L = new returnList;

    QList<Drawing*> drawinglist;
    drawinglist<< myDrawingA;
    drawinglist<< myDrawingB;

    if(myDrawingC)

        drawinglist<< myDrawingC;

    L->drawingList = drawinglist;
    L->n = changeScene1;
    return L;


}


float CustomScene::lineAngle(const QPointF start,const QPointF end)
{
    return std::atanf((end.y()-start.y())/(end.x()-start.x()));
}


void CustomScene::receiveDrawRectSignalinEnhancement(QRectF *rect,QRectF *rect2,float cTheta, float isoCentreX,float isoCentreY,float p)
{


    this->setMode(Mode::DilineatorMode);

    /*Dilineator Rectangle*/

    rectDefault1= new CustomItem();
    this->addItem(rectDefault1);

    qDebug()<<"Points Verifying "<<ctLX<<ctLY<<cbRX<<cbRY;

    rectDefault1->setRect(ctLX,ctLY,cbRX-ctLX,cbRY-ctLY);

    if(FrameRateMode==2||FrameRateMode==3)
        rectDefault1->setPen(QPen(Qt::white,(0.139*5)/(imaginPixelSpacing)));
    else
        rectDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));

    rectDefault1->setRotation((qreal)cTheta);

    rectDefault1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);

    rectDefault1->resetTransform();
    rectDefault1->show();

     qDebug()<<"ctLX"<<*rect;

    rectSizeGripItem1 =new SizeGripItem(new RectResizer, rectDefault1);

    if(FrameRateMode!=1)
    {
        rectSizeGripItem1->setEnabled(false);
        rectSizeGripItem1->hide();
    }
    else
        QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToDilineatorResize(QRectF,int)));
    //    QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));
    //    QObject::connect(rectItem3,SIGNAL(itemChanged(QPointF)),this,SLOT(respondToitemChange2(QPointF)));





    if(FrameRateMode==1){

    /*Jaw Rectangle*/
    rectDefault2= new CustomItem();
    this->addItem(rectDefault2);
    rectDefault2->setRect(*rect2);
    rectDefault2->setRotation((qreal)gTheta);
    rectDefault2->setTransformOriginPoint(prevIsoCenterX,prevIsoCenterY);
    rectDefault2->setPen(QPen(Qt::green,(0.139*5)/(imaginPixelSpacing)));
    rectDefault2->setFlag(QGraphicsItem::ItemIsMovable,false);
    rectDefault2->show();
    }



    qDebug()<<"Jaw Rect: "<<rectDefault2->rect();

    qDebug()<<"Dil Rect: "<<rectDefault1->rect();





    /*Iso Center*/

    isocenterRect = new QGraphicsRectItem();

    this->addItem(isocenterRect);
    isocenterRect->setRect(prevIsoCenterX-(1.39/(imaginPixelSpacing*2)),prevIsoCenterY-(1.39/(imaginPixelSpacing*2)),(1.39/imaginPixelSpacing)/**2*/,(1.39/imaginPixelSpacing)/**2*/);
    isocenterRect->setPen(QPen(Qt::green,(0.139*5)/(imaginPixelSpacing)));
    isocenterRect->setBrush(QBrush(Qt::green));


 qDebug()<<"isocenterRect: "<<isocenterRect->rect();


  qDebug()<<"centerTempX "<<gCenterX<<gCenterY;

//    qDebug()<<"DilCenter:(pixels)"<<rectDefault1->rect().center();
//    qDebug()<<"DilAngle (degree):"<<rectDefault1->rotation();









    /*Dilineator Centre Point*/
    centerDefault1 = new QGraphicsRectItem();
    this->addItem(centerDefault1);
    centerDefault1->setRect(centerTempX-(1.39/(imaginPixelSpacing*2)),centerTempY-(1.39/(imaginPixelSpacing*2)),(1.39/imaginPixelSpacing)/**2*/,(1.39/imaginPixelSpacing)/**2*/);
  //  centerDefault1->setRect(centerTempX-10.0,centerTempY-10.0,20,20);
    if(FrameRateMode==2||FrameRateMode==3){
        centerDefault1->setPen(QPen(Qt::white,(0.139*5)/(imaginPixelSpacing)));
        centerDefault1->setBrush(QBrush(Qt::white));
    }
    else{
        centerDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));
        centerDefault1->setBrush(QBrush(Qt::red));
    }

    centerDefault1->setRotation((qreal)cTheta);
    centerDefault1->setTransformOriginPoint(centerTempX,centerTempY);
    centerDefault1->resetTransform();
    //centerDefault1->setParentItem(rectDefault1);




}


void CustomScene::ReceiveCBCTRedraw(QMap<int, QList<Drawing *> > cbctMap, int sliceNo)
{

    if(!cbctMap.contains(sliceNo))
        return;

    QList<Drawing*> drawList = cbctMap.find(sliceNo).value();
    qDebug()<<"drawList-->"<<drawList<<sliceNo;
    for(int i=0;i<drawList.length();i++)
    {
        Drawing* redraw = drawList.at(i);
        CustomScene::Mode mode= getMode(redraw->type);
        qDebug()<<"redraw->type"<<redraw->type << redraw->pointsList ;
   qDebug()<<"mode"<<mode;
        switch (mode)
        {
        case DrawEllipse:
        {
//            if(!ellip)
//            {
                ellip=new QGraphicsEllipseItem;

                ellip->setPen(drawPen);
                //ellip->setPos(redraw->pos);
                ellip->setRect(QRectF(redraw->pointsList.at(0).x(),redraw->pointsList.at(0).y(),
                                      redraw->pointsList.at(1).x(),redraw->pointsList.at(1).y()));
                ellipTag=new QGraphicsTextItem;
                QFont serifFont("Times",6,QFont::Bold);
                ellipTag->setPos(redraw->pointsList.at(2));
                ellipTag->setFont(serifFont);
                ellipTag->setDefaultTextColor(Qt::yellow);
                ellipTag->setAcceptHoverEvents(false);
                ellipTag->setPlainText(redraw->tag);
                this->addItem(ellipTag);
                this->addItem(ellip);
//                QList<QGraphicsItem*> list;
//                list.append(ellip);
//                list.append(ellipTag);
//                group=this->createItemGroup(list);
//                group->setFlag(QGraphicsItem::ItemIsSelectable,true);
qDebug()<<"ellipse drawn"<<redraw->pos<<ellip->rect();
emit measurementDrawn(ellip);
emit measurementDrawn(ellipTag);

                group=0;
                ellip=0;
                ellipTag=0;


//            }

            break;
        }
        case Drawrectcbct:
        {
         //   if(!rect){

              qDebug()<<"redraw rectangle";
                rect = new QGraphicsRectItem;
                this->addItem(rect);
                rect->setPen(drawPen);

                rect->setPos(redraw->pos);
                rect->setRect(QRectF(redraw->pointsList.at(0).x(),redraw->pointsList.at(0).y(),
                                    redraw->pointsList.at(1).x(),redraw->pointsList.at(1).y()));



                rectTag=new QGraphicsTextItem;
                QFont serifFont("Times",6,QFont::Bold);
                rectTag->setPos(redraw->pointsList.at(2));
                rectTag->setFont(serifFont);
                rectTag->setDefaultTextColor(Qt::yellow);
                rectTag->setAcceptHoverEvents(false);
                rectTag->setPlainText(redraw->tag);


                this->addItem(rectTag);
                QList<QGraphicsItem*> list;
                list.append(rect);
                list.append(rectTag);
                group=this->createItemGroup(list);
                group->setFlag(QGraphicsItem::ItemIsSelectable,false);
              emit measurementDrawn(group);


                rect=0;
                rectTag=0;
                group=0;




            //}
            break;

        }
        case DrawText:
        {
            qDebug()<<"text details--->"<<redraw->tag<<redraw->pos;
            text= new QGraphicsTextItem(redraw->tag);
            QFont serifFont("Times",6,QFont::Bold);
            text->setPos(redraw->pos);
            text->setFont(serifFont);
            text->setDefaultTextColor(Qt::yellow);
            text->setAcceptHoverEvents(false);
            text->setHandlesChildEvents(false);
            this->addItem(text);
            emit measurementDrawn(text);
 text=0;
            //text=0;
            qDebug()<<"text drawn"<<redraw->pos;
            break;
        }
//        default:
//            break;
//        }
        case DrawLine:
        {
            qDebug()<<"line details--->"<<redraw->tag<<redraw->pos;
            line = new QGraphicsLineItem;
            line->setPen(drawPen);
            line->setPos(redraw->pos);
              lineTag=new QGraphicsTextItem;
               QFont serifFont("Times",6,QFont::Bold);
                  lineTag->setPos(redraw->pos);

      //      this->addItem(lineTag);
            //redraw was replaced by reDrawlist//
           lineTag->setPlainText(redraw->tag);
            lineTag->setFont(serifFont);
            lineTag->setDefaultTextColor(Qt::yellow);
            lineTag->setAcceptHoverEvents(false);

           line->setLine(redraw->pointsList.at(0).x(),redraw->pointsList.at(0).y(),
                          redraw->pointsList.at(1).x(),redraw->pointsList.at(1).y());
               this->addItem(line);
                 this->addItem(lineTag);
           // QList<QGraphicsItem*> list;

       //     list.append(line);
         //   list.append(lineTag);
               //qDebug()<<"line details1--->"<<list;
          //  group=this->createItemGroup(list);
          //  group->setFlag(QGraphicsItem::ItemIsSelectable,true);
            //  emit measurementDrawn(group);
           emit measurementDrawn(line);
           emit measurementDrawn(lineTag);

         //   this->addItem(lineTag);
           line=0;
           lineTag=0;
            break;
        }
             case DrawAngle:
        {
                qDebug()<<"angle details--->";
                  qDebug()<<"line details--->"<<redraw->tag;
            if(!line)
            {
                  qDebug()<<"angle details1--->";
                line = new QGraphicsLineItem;
                line->setPen(drawPen);
                line->setPos(redraw->pos);
                line->setLine(0,0,
                              redraw->pointsList.at(0).x()-redraw->pos.x(),
                              redraw->pointsList.at(0).y()-redraw->pos.y());

                this->addItem(line);
                    emit measurementDrawn(line);

            }
            if(!line2)
            {
                  qDebug()<<"angle details2--->";
                line2 = new QGraphicsLineItem;

                line2->setPen(drawPen);
                line2->setPos(redraw->pointsList.at(0));
                  qDebug()<<"angle details4--->";
                  qDebug()<<redraw->pointsList.at(1).x()<<redraw->pointsList.at(0).x()<<redraw->pointsList.at(1).y()<<redraw->pointsList.at(0).y();
                line2->setLine(0,0, redraw->pointsList.at(1).x()-redraw->pointsList.at(0).x(),
                               redraw->pointsList.at(1).y()-redraw->pointsList.at(0).y());
                  qDebug()<<"angle details5--->";
                this->addItem(line2);


            }
               qDebug()<<"angle details3--->";
            angleTag=new QGraphicsTextItem;
            QFont serifFont("Times",6,QFont::Bold);
            angleTag->setPos(redraw->pointsList.at(0));
            angleTag->setFont(serifFont);
            angleTag->setDefaultTextColor(Qt::yellow);
            angleTag->setAcceptHoverEvents(false);
            angleTag->setPlainText(redraw->tag);
            this->addItem(angleTag);
            QList<QGraphicsItem*> list;
            list.append(line);
           list.append(line2);
            list.append(angleTag);
            group=this->createItemGroup(list);
            group->setFlag(QGraphicsItem::ItemIsSelectable,true);
            emit measurementDrawn(line2);
            emit measurementDrawn(angleTag);

         //   group->setFlag(QGraphicsItem::ItemIsMovable,true);
            line2=0;
            line=0;
 angleTag=0;


        break;



        }
        }


    }
}



void CustomScene::receiveDrawRectSignal(QRectF *rect, QRectF *rect2, float cTheta, float isoCentreX,float isoCentreY,float p)
{


    this->setMode(Mode::DilineatorMode);

    /*Dilineator Rectangle*/
    rectDefault1= new CustomItem();
    this->addItem(rectDefault1);

    rectDefault1->setRect(*rect);

    if(FrameRateMode==2||FrameRateMode==3)
        rectDefault1->setPen(QPen(Qt::white,(0.139*5)/(imaginPixelSpacing)));
    else
        rectDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));

    rectDefault1->setRotation((qreal)cTheta);

    rectDefault1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);

    rectDefault1->resetTransform();
    rectDefault1->show();




    rectSizeGripItem1 =new SizeGripItem(new RectResizer, rectDefault1);

    if(FrameRateMode!=1)
    {
        rectSizeGripItem1->setEnabled(false);
        rectSizeGripItem1->hide();
    }
    else
        QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToDilineatorResize(QRectF,int)));

    //    QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));
    //    QObject::connect(rectItem3,SIGNAL(itemChanged(QPointF)),this,SLOT(respondToitemChange2(QPointF)));





//    if(FrameRateMode==1){

    /*Jaw Rectangle*/
    rectDefault2= new CustomItem();
    this->addItem(rectDefault2);
    rectDefault2->setRect(*rect2);
    rectDefault2->setRotation((qreal)cTheta);
    rectDefault2->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
    rectDefault2->setPen(QPen(Qt::green,(0.139*5)/(imaginPixelSpacing)));
    rectDefault2->setFlag(QGraphicsItem::ItemIsMovable,false);
    rectDefault2->show();
//    }



  //  qDebug()<<"Jaw Rect: "<<rectDefault2->rect();





    /*Iso Center*/

    isocenterRect = new QGraphicsRectItem();

    this->addItem(isocenterRect);
    isocenterRect->setRect(isoCentreX/p-(1.39/(imaginPixelSpacing*2)),isoCentreY/p-(1.39/(imaginPixelSpacing*2)),(1.39/imaginPixelSpacing)/**2*/,(1.39/imaginPixelSpacing)/**2*/);
    isocenterRect->setPen(QPen(Qt::green,(0.139*5)/(imaginPixelSpacing)));
    isocenterRect->setBrush(QBrush(Qt::green));







//    qDebug()<<"DilCenter:(pixels)"<<rectDefault1->rect().center();
//    qDebug()<<"DilAngle (degree):"<<rectDefault1->rotation();








    /*Dilineator Centre Point*/
    centerDefault1 = new QGraphicsRectItem();
    this->addItem(centerDefault1);
    centerDefault1->setRect(rectDefault1->rect().center().rx()-(1.39/(imaginPixelSpacing*2)),rectDefault1->rect().center().ry()-(1.39/(imaginPixelSpacing*2)),(1.39/imaginPixelSpacing)/**2*/,(1.39/imaginPixelSpacing)/**2*/);
  //  centerDefault1->setRect(centerTempX-10.0,centerTempY-10.0,20,20);
    if(FrameRateMode==2||FrameRateMode==3){
        centerDefault1->setPen(QPen(Qt::white,(0.139*5)/(imaginPixelSpacing)));
        centerDefault1->setBrush(QBrush(Qt::white));
    }
    else{
        centerDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));
        centerDefault1->setBrush(QBrush(Qt::red));
    }

    centerDefault1->setRotation((qreal)cTheta);
    centerDefault1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
    centerDefault1->resetTransform();
    //centerDefault1->setParentItem(rectDefault1);









    /*Applying ColliTheta on Dilineator*/


    cTheta = cTheta * (3.14/180);//to radian


    /*Added */
    float tempX = rect->topLeft().rx()*p-isoCentreX;
    float tempY = rect->topLeft().ry()*p-isoCentreY;

    tLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    tLY = tempX*sin(cTheta)+tempY*cos(cTheta);

    tLX = (tLX+isoCentreX)/p;
    tLY = (tLY+isoCentreY)/p;

    tempX = rect->topRight().rx()*p-isoCentreX;
    tempY = rect->topRight().ry()*p-isoCentreY;

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

    /*Added*/


    /*Calculate Dilineator Center*/
    tempX = centerDefault1->rect().center().rx()*p-isoCentreX;
    tempY = centerDefault1->rect().center().ry()*p-isoCentreY;

    centerTempX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    centerTempY = tempX*sin(cTheta)+tempY*cos(cTheta);

    centerTempX = (centerTempX+isoCentreX)/p;
    centerTempY = (centerTempY+isoCentreY)/p;



//    qDebug() <<"centers "<<centerTempX<<centerTempY;
//    qDebug()<<"oppo cor cen"<<(tLX+bRX)/2<<(tLY+bRY)/2;


    isocenterX = isoCentreX/p;//in pixels
    isocenterY = isoCentreY/p;//in pixels




    /*Couch Shift calculated in pixels*/

    isoRectCenterShiftX = centerTempX-isoCentreX/p;
    isoRectCenterShiftY = centerTempY-isoCentreY/p;




    /*X1,X2,Y1,Y2*/
    ctLX = rect->topLeft().rx();
    ctLY = rect->topLeft().ry();
    ctRX = rect->topRight().rx();
    ctRY = rect->topRight().ry();
    cbLX = rect->bottomLeft().rx();
    cbLY = rect->bottomLeft().ry();
    cbRX = rect->bottomRight().rx();
    cbRY = rect->bottomRight().ry();



    /*Calculating intial Dilineator Center*/

    float initCenterX, initCenterY;
    cTheta=-cTheta;
    tempX = centerTempX*p-isoCentreX;
    tempY = centerTempY*p-isoCentreY;

    initCenterX = tempX*cos(cTheta)+tempY*sin(-cTheta);
    initCenterY = tempX*sin(cTheta)+tempY*cos(cTheta);

    initCenterX = (initCenterX+isoCentreX)/p;
    initCenterY = (initCenterY+isoCentreY)/p;

    /*Calculating intial Dilineator Center*/

    if(!((tRX==tLX)&&(tRY==tLY)))
       rTheta = -cTheta*(180/3.14); // rTheta = atan((tRY-tLY)/(tRX-tLX))*(180/3.14);
    else
        rTheta=0;
 //   qDebug() <<"rtheta angle in degree "<<rTheta;

    qDebug() <<"RotateAngle "<<rTheta;

    gCenterX = isocenterX;
    gCenterY = isocenterY;
    gTheta = rTheta;

    /*Back up*/
    prevIsoCenterX = isocenterX; //Creating a copy of my initial isocenter
    prevIsoCenterY = isocenterY;

        QList<double> plannedValue;

                             plannedValue.append((ctLX*p-isoCentreX));//X1

                             plannedValue.append((cbRX*p-isoCentreX));//X2

                             plannedValue.append(-(cbRY*p-isoCentreY));//Y1


                             plannedValue.append(-(ctLY*p-isoCentreY));//Y2


                             plannedValue.append(isoRectCenterShiftX*p);//CouchX
                             plannedValue.append(-isoRectCenterShiftY*p);//CouchY
                             plannedValue.append((0.0));//CouchZ
                             plannedValue.append(rTheta);

                             plannedValue.append(initCenterX*p-isoCentreX);
                             plannedValue.append(-(initCenterY*p-isoCentreY));

     emit  UpdatePlannedVlue(plannedValue);





}

void CustomScene::setImage(QImage imag)
{
    //Set Image to calculate stats for rectangle and ellipse
    image= imag;
    //qDebug()<<"Setting pixmap";
    pixMap=new QGraphicsPixmapItem;
    pixMap->setPixmap(QPixmap::fromImage(image));
    pixMap->setFlag(QGraphicsItem::ItemIsSelectable,false);
    this->addItem(pixMap);
    pixMap=0;
}

void CustomScene::setConversionVals(float a, float b)
{
    //HU conversion slope and intercept.
    slope=a;
    intercept=b;
}



void CustomScene::rotateDrawRect(float rotateStep, QRectF *jawRect)
{


/*
 * Caution: Centre will be changed.Couch shift will be calculated and send.
   Additional step of rotaion will be added to the current colliTheta.
   The updated colliTheta can be directly applied to the mlc.
*/
 /*
   For rotating Dilineator Wires at given rotation step added with colli theta
 */




//    /*Back up*/
//    prevIsoCenterX = isocenterX; //Creating a copy of my initial isocenter
//    prevIsoCenterY = isocenterY;

    isoDilShiftX = centerTempX-isocenterX; // Shift btw initial isocenter and current DilCenter in pixels
    isoDilShiftY = centerTempY-isocenterY;



    /*Changing Iso Centre*/
    isocenterX=centerTempX;
    isocenterY=centerTempY;



    /*finding Dil positions without collithta, by removing colllitheta w. r.t  new iso centre */

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


//    qDebug()<<"Rotation Step     :"<<rotateStep;
//    qDebug()<<"Updated Collitheta:"<<cTheta*(180/3.14);


    if(tLX1>1 && tLX1<3071 && tLY1>1 && tLY1<3071 && tRX1>1 && tRX1<3071 && tRY1>1 && tRY1<3071 && bLX1>1 && bLX1<3071 && bLY1>1 && bLY1<3071 && bRX1>1 && bRX1<3071 && bRY1>1 && bRY1<3071)
    {

//    qDebug() <<"Current Dilineator Positions in Scene Co-ordinates without  (pixels): "<<ctLX<<ctRX<<ctLY<<ctRY<<cbLX<<cbLY<<cbRX<<cbRY;


    /*For Dilineator wires*/

         delete rectDefault1;
         rectDefault1=NULL;
         rectDefault1= new CustomItem();
         this->addItem(rectDefault1);

         rectDefault1->setRect(ctLX,ctLY,cbRX-ctLX,cbRY-ctLY);
         rectDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));

         rectDefault1->setRotation((qreal)cTheta*(180/3.14));
         rectDefault1->setTransformOriginPoint(isocenterX,isocenterY);

         rectDefault1->resetTransform();
         rectDefault1->show();


         rectSizeGripItem1 =new SizeGripItem(new RectResizer, rectDefault1);
         QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToDilineatorResize(QRectF,int)));



     /*For Dilineator wires*/



     /*For Dilineator Center*/
         delete centerDefault1;
         centerDefault1=NULL;

         centerDefault1 = new QGraphicsRectItem();
         this->addItem(centerDefault1);
         centerDefault1->setRect(isocenterX-(1.39/(imaginPixelSpacing*2)),isocenterY-(1.39/(imaginPixelSpacing*2)),(1.39/imaginPixelSpacing)/**2*/,(1.39/imaginPixelSpacing)/**2*/);
         centerDefault1->setPen(QPen(Qt::red,(0.139*5)/(imaginPixelSpacing)));
         centerDefault1->setBrush(QBrush(Qt::red));
         centerDefault1->setRotation((qreal)cTheta*(180/3.14));
         centerDefault1->setTransformOriginPoint(isocenterX,isocenterY);
         centerDefault1->resetTransform();
         centerDefault1->show();

     /*For Dilineator Center*/







    /*After Applying */

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











        /*Calculating intial Dilineator Center*/

//        centerTempX = (tLX+bRX)/2;
//        centerTempY = (tLY+bRY)/2;


//        qDebug() <<"Points to check "<<tRX<<tLX<<tRY<<tLY;
        //rTheta = atan((tRY-tLY)/(tRX-tLX))*(180/3.14);



        /*Upadted ColliTheta*/
        rTheta = rTheta+dTheta;
        qDebug() <<"RotateStepAngle "<<rTheta;

        gCenterX = isocenterX;
        gCenterY = isocenterY;


        if(rTheta<0)
            rTheta=(rTheta+360);
        if(rTheta>360)
            rTheta=rTheta-360;

        double pixelPitch = imaginPixelSpacing;
        QList<double> plannedValue;

                             plannedValue.append((ctLX-prevIsoCenterX)*pixelPitch);
                             plannedValue.append((cbRX-prevIsoCenterX)*pixelPitch);
                             plannedValue.append(-(cbRY-prevIsoCenterY)*pixelPitch);
                             plannedValue.append(-(ctLY-prevIsoCenterY)*pixelPitch);
                             plannedValue.append((centerTempX-prevIsoCenterX)*pixelPitch);
                             plannedValue.append(-(centerTempY-prevIsoCenterY)*pixelPitch);
                             plannedValue.append((0.0));
                             plannedValue.append(rTheta);

                             plannedValue.append((centerTempX-prevIsoCenterX)*pixelPitch);
                             plannedValue.append(-(centerTempY-prevIsoCenterY)*pixelPitch);

     emit  UpdatePlannedVlue(plannedValue);
    }
    else
    {
      //Message Box
    }

}

void CustomScene::RotatingDilPositions(QPointF curPoints)
{
    dTheta=0;

    //Rotating all Dilineator positions to 0 degree
    double cTheta =-(rTheta+dTheta)*(3.14/180);
//    qDebug() <<"cThetssa "<<cTheta<<rTheta<<dTheta;

   float tempX = tLX-centerTempX;
   float tempY = tLY-centerTempY;

        ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
        ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

        ctLX = ctLX+centerTempX;
        ctLY = ctLY+centerTempY;

        tempX = tRX-centerTempX;
        tempY = tRY-centerTempY;

        ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
        ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

        ctRX = ctRX+centerTempX;
        ctRY = ctRY+centerTempY;

        tempX = bLX-centerTempX;
        tempY = bLY-centerTempY;

        cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
        cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

        cbLX = cbLX+centerTempX;
        cbLY = cbLY+centerTempY;

        tempX = bRX-centerTempX;
        tempY = bRY-centerTempY;

        cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
        cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

        cbRX = cbRX+centerTempX;
        cbRY = cbRY+centerTempY;

        //Rotating all Dilineator positions to 0 degree


        //Rotating previous and current mouse positions to -theta

            double tempCurx,tempCurx1, tempCury1, tempCury;

            tempX = prevX-centerTempX;
            tempY = prevY-centerTempY;

            tempCurx = tempX*cos(cTheta)+tempY*sin(-cTheta);
            tempCury = tempX*sin(cTheta)+tempY*cos(cTheta);

            tempCurx = tempCurx+centerTempX;
            tempCury = tempCury+centerTempY;

            tempX = curPoints.rx()-centerTempX;
            tempY = curPoints.ry()-centerTempY;

            tempCurx1 = tempX*cos(cTheta)+tempY*sin(-cTheta);
            tempCury1 = tempX*sin(cTheta)+tempY*cos(cTheta);

            tempCurx1 = tempCurx1+centerTempX;
            tempCury1 = tempCury1+centerTempY;

            qDebug()<<"resizeState "<<resizeState;

            if ((resizeState==4 || resizeState==5 || resizeState==6) && ctLX+(tempCurx1-tempCurx)>ctRX && (tempCurx1-tempCurx)>0 && std::roundf(ctRX)>=std::roundf(ctLX)) // Dilineator Left Sides
            {
                qDebug() <<"Enter1st Condition";
                tempCurx1=tempCurx;
                ctLX = ctRX;
                cbLX = cbRX;

            }

            if ((resizeState==1 || resizeState==5 || resizeState==9) && ctLY+(tempCury1-tempCury)>cbLY && (tempCury1-tempCury)>0 && std::roundf(cbLY)>=std::roundf(ctLY)) //Dilineator Top Sides
            {
                qDebug() <<"Enter2nd Condition";
                tempCury1=tempCury;
                ctLY = cbLY;
                ctRY = cbRY;
            }

            if ((resizeState==8 || resizeState==9 || resizeState==10) && ctRX+(tempCurx1-tempCurx)<ctLX && (tempCurx1-tempCurx)<0 && std::roundf(ctRX)>=std::roundf(ctLX)) // Dilineator Right Sides
            {
                qDebug() <<"Enter3rd Condition";
                tempCurx1=tempCurx;
                ctRX = ctLX;
                cbRX = cbLX;
            }

            if ((resizeState==6 || resizeState==2 || resizeState==10) && cbLY+(tempCury1-tempCury)<ctLY && (tempCury1-tempCury)<0 && std::roundf(cbLY)>=std::roundf(ctLY)) // Dilineator Right Sides
            {
                qDebug() <<"Enter4th Condition";
                tempCury1=tempCury;
                cbLY = ctLY;
                cbRY = ctRY;
            }

            //Rotating previous and current mouse positions to -theta


            if (resizeState==5)  //topLeft
             {
               tLX = ctLX+(tempCurx1-tempCurx);
               tLY = ctLY+(tempCury1-tempCury);

               tRX = ctRX;
               tRY = ctRY+(tempCury1-tempCury);

               bLX = cbLX+(tempCurx1-tempCurx);
               bLY = cbLY;

               bRX = cbRX;
               bRY = cbRY;

               cTheta =(rTheta+dTheta)*(3.14/180);

               tempX = tLX-centerTempX;
               tempY = tLY-centerTempY;

                    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctLX = ctLX+centerTempX;
                    ctLY = ctLY+centerTempY;

                    tempX = tRX-centerTempX;
                    tempY = tRY-centerTempY;

                    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctRX = ctRX+centerTempX;
                    ctRY = ctRY+centerTempY;

                    tempX = bLX-centerTempX;
                    tempY = bLY-centerTempY;

                    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbLX = cbLX+centerTempX;
                    cbLY = cbLY+centerTempY;

                    tempX = bRX-centerTempX;
                    tempY = bRY-centerTempY;

                    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbRX = cbRX+centerTempX;
                    cbRY = cbRY+centerTempY;

 //                   qDebug() <<"tRX "<<tRX<<tRY<<centerTempX<<centerTempY;

 //                   qDebug() <<"Pos obtained "<<ctLX<<ctLY<<ctRX<<ctRY<<cbLX<<cbLY<<cbRX<<cbRY;


             }

            if (resizeState==9)  //topRight
             {
               tLX = ctLX;
               tLY = ctLY+(tempCury1-tempCury);

               tRX = ctRX+(tempCurx1-tempCurx);
               tRY = ctRY+(tempCury1-tempCury);

               bLX = cbLX;
               bLY = cbLY;

               bRX = cbRX+(tempCurx1-tempCurx);
               bRY = cbRY;

               cTheta =(rTheta+dTheta)*(3.14/180);

               tempX = tLX-centerTempX;
               tempY = tLY-centerTempY;

                    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctLX = ctLX+centerTempX;
                    ctLY = ctLY+centerTempY;

                    tempX = tRX-centerTempX;
                    tempY = tRY-centerTempY;

                    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctRX = ctRX+centerTempX;
                    ctRY = ctRY+centerTempY;

                    tempX = bLX-centerTempX;
                    tempY = bLY-centerTempY;

                    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbLX = cbLX+centerTempX;
                    cbLY = cbLY+centerTempY;

                    tempX = bRX-centerTempX;
                    tempY = bRY-centerTempY;

                    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbRX = cbRX+centerTempX;
                    cbRY = cbRY+centerTempY;

 //                   qDebug() <<"tRX "<<tRX<<tRY<<centerTempX<<centerTempY;

 //                   qDebug() <<"Pos obtained "<<ctLX<<ctLY<<ctRX<<ctRY<<cbLX<<cbLY<<cbRX<<cbRY;


             }

            if (resizeState==6)  //bottomLeft
             {
               tLX = ctLX+(tempCurx1-tempCurx);
               tLY = ctLY;

               tRX = ctRX;
               tRY = ctRY;

               bLX = cbLX+(tempCurx1-tempCurx);
               bLY = cbLY+(tempCury1-tempCury);

               bRX = cbRX;
               bRY = cbRY+(tempCury1-tempCury);

               cTheta =(rTheta+dTheta)*(3.14/180);

               tempX = tLX-centerTempX;
               tempY = tLY-centerTempY;

                    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctLX = ctLX+centerTempX;
                    ctLY = ctLY+centerTempY;

                    tempX = tRX-centerTempX;
                    tempY = tRY-centerTempY;

                    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctRX = ctRX+centerTempX;
                    ctRY = ctRY+centerTempY;

                    tempX = bLX-centerTempX;
                    tempY = bLY-centerTempY;

                    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbLX = cbLX+centerTempX;
                    cbLY = cbLY+centerTempY;

                    tempX = bRX-centerTempX;
                    tempY = bRY-centerTempY;

                    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbRX = cbRX+centerTempX;
                    cbRY = cbRY+centerTempY;

 //                   qDebug() <<"tRX "<<tRX<<tRY<<centerTempX<<centerTempY;

 //                   qDebug() <<"Pos obtained "<<ctLX<<ctLY<<ctRX<<ctRY<<cbLX<<cbLY<<cbRX<<cbRY;


             }


            if (resizeState==10)  //bottomRight
             {
               tLX = ctLX;
               tLY = ctLY;

               tRX = ctRX+(tempCurx1-tempCurx);
               tRY = ctRY;

               bLX = cbLX;
               bLY = cbLY+(tempCury1-tempCury);

               bRX = cbRX+(tempCurx1-tempCurx);
               bRY = cbRY+(tempCury1-tempCury);

               cTheta =(rTheta+dTheta)*(3.14/180);

               tempX = tLX-centerTempX;
               tempY = tLY-centerTempY;

                    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctLX = ctLX+centerTempX;
                    ctLY = ctLY+centerTempY;

                    tempX = tRX-centerTempX;
                    tempY = tRY-centerTempY;

                    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctRX = ctRX+centerTempX;
                    ctRY = ctRY+centerTempY;

                    tempX = bLX-centerTempX;
                    tempY = bLY-centerTempY;

                    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbLX = cbLX+centerTempX;
                    cbLY = cbLY+centerTempY;

                    tempX = bRX-centerTempX;
                    tempY = bRY-centerTempY;

                    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbRX = cbRX+centerTempX;
                    cbRY = cbRY+centerTempY;

 //                   qDebug() <<"tRX "<<tRX<<tRY<<centerTempX<<centerTempY;

 //                   qDebug() <<"Pos obtained "<<ctLX<<ctLY<<ctRX<<ctRY<<cbLX<<cbLY<<cbRX<<cbRY;


             }


            if (resizeState==1)  //top
             {
               tLX = ctLX;
               tLY = ctLY+(tempCury1-tempCury);

               tRX = ctRX;
               tRY = ctRY+(tempCury1-tempCury);

               bLX = cbLX;
               bLY = cbLY;

               bRX = cbRX;
               bRY = cbRY;

               cTheta =(rTheta+dTheta)*(3.14/180);

               tempX = tLX-centerTempX;
               tempY = tLY-centerTempY;

                    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctLX = ctLX+centerTempX;
                    ctLY = ctLY+centerTempY;

                    tempX = tRX-centerTempX;
                    tempY = tRY-centerTempY;

                    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctRX = ctRX+centerTempX;
                    ctRY = ctRY+centerTempY;

                    tempX = bLX-centerTempX;
                    tempY = bLY-centerTempY;

                    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbLX = cbLX+centerTempX;
                    cbLY = cbLY+centerTempY;

                    tempX = bRX-centerTempX;
                    tempY = bRY-centerTempY;

                    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbRX = cbRX+centerTempX;
                    cbRY = cbRY+centerTempY;

 //                   qDebug() <<"tRX "<<tRX<<tRY<<centerTempX<<centerTempY;

 //                   qDebug() <<"Pos obtained "<<ctLX<<ctLY<<ctRX<<ctRY<<cbLX<<cbLY<<cbRX<<cbRY;


             }

            if (resizeState==4)  //Left
             {
               tLX = ctLX+(tempCurx1-tempCurx);
               tLY = ctLY;

               tRX = ctRX;
               tRY = ctRY;

               bLX = cbLX+(tempCurx1-tempCurx);
               bLY = cbLY;

               bRX = cbRX;
               bRY = cbRY;

               cTheta =(rTheta+dTheta)*(3.14/180);

               tempX = tLX-centerTempX;
               tempY = tLY-centerTempY;

                    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctLX = ctLX+centerTempX;
                    ctLY = ctLY+centerTempY;

                    tempX = tRX-centerTempX;
                    tempY = tRY-centerTempY;

                    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctRX = ctRX+centerTempX;
                    ctRY = ctRY+centerTempY;

                    tempX = bLX-centerTempX;
                    tempY = bLY-centerTempY;

                    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbLX = cbLX+centerTempX;
                    cbLY = cbLY+centerTempY;

                    tempX = bRX-centerTempX;
                    tempY = bRY-centerTempY;

                    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbRX = cbRX+centerTempX;
                    cbRY = cbRY+centerTempY;

 //                   qDebug() <<"tRX "<<tRX<<tRY<<centerTempX<<centerTempY;

 //                   qDebug() <<"Pos obtained "<<ctLX<<ctLY<<ctRX<<ctRY<<cbLX<<cbLY<<cbRX<<cbRY;


             }

            if (resizeState==8)  //Right
             {
               tLX = ctLX;
               tLY = ctLY;

               tRX = ctRX+(tempCurx1-tempCurx);
               tRY = ctRY;

               bLX = cbLX;
               bLY = cbLY;

               bRX = cbRX+(tempCurx1-tempCurx);
               bRY = cbRY;

               cTheta =(rTheta+dTheta)*(3.14/180);

               tempX = tLX-centerTempX;
               tempY = tLY-centerTempY;

                    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctLX = ctLX+centerTempX;
                    ctLY = ctLY+centerTempY;

                    tempX = tRX-centerTempX;
                    tempY = tRY-centerTempY;

                    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctRX = ctRX+centerTempX;
                    ctRY = ctRY+centerTempY;

                    tempX = bLX-centerTempX;
                    tempY = bLY-centerTempY;

                    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbLX = cbLX+centerTempX;
                    cbLY = cbLY+centerTempY;

                    tempX = bRX-centerTempX;
                    tempY = bRY-centerTempY;

                    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbRX = cbRX+centerTempX;
                    cbRY = cbRY+centerTempY;

 //                   qDebug() <<"tRX "<<tRX<<tRY<<centerTempX<<centerTempY;

 //                   qDebug() <<"Pos obtained "<<ctLX<<ctLY<<ctRX<<ctRY<<cbLX<<cbLY<<cbRX<<cbRY;


             }


            if (resizeState==2)  //bottom
             {
               tLX = ctLX;
               tLY = ctLY;

               tRX = ctRX;
               tRY = ctRY;

               bLX = cbLX;
               bLY = cbLY+(tempCury1-tempCury);

               bRX = cbRX;
               bRY = cbRY+(tempCury1-tempCury);

               cTheta =(rTheta+dTheta)*(3.14/180);

               tempX = tLX-centerTempX;
               tempY = tLY-centerTempY;

                    ctLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctLX = ctLX+centerTempX;
                    ctLY = ctLY+centerTempY;

                    tempX = tRX-centerTempX;
                    tempY = tRY-centerTempY;

                    ctRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    ctRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    ctRX = ctRX+centerTempX;
                    ctRY = ctRY+centerTempY;

                    tempX = bLX-centerTempX;
                    tempY = bLY-centerTempY;

                    cbLX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbLY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbLX = cbLX+centerTempX;
                    cbLY = cbLY+centerTempY;

                    tempX = bRX-centerTempX;
                    tempY = bRY-centerTempY;

                    cbRX = tempX*cos(cTheta)+tempY*sin(-cTheta);
                    cbRY = tempX*sin(cTheta)+tempY*cos(cTheta);

                    cbRX = cbRX+centerTempX;
                    cbRY = cbRY+centerTempY;

 //                   qDebug() <<"tRX "<<tRX<<tRY<<centerTempX<<centerTempY;



             }

            qDebug() <<"Pos obtained "<<ctLX<<ctLY<<ctRX<<ctRY<<cbLX<<cbLY<<cbRX<<cbRY;




}

QList<float> CustomScene::statsOfEllipse(QImage image, QRectF geometry)
{
    /*Assumes image is grayscale. geometry contains center and width ,height respectively.
     * returns a list of float containing number of pixels in, mean and standard deviation
     * of the pixels inside the given ellipse.*/

    QList<float> stats;
    QList<int> valuesIn;
    float mean=0;
    float sum=0;
    int count=0;
    float p;
  float rX= geometry.width()/2.0;
   float rY= geometry.height()/2.0;

    for (float x=0.0;x<image.width();x++)
    {
        for(float y=0.0;y<image.height();y++)
        {
            p=std::powf(((x-geometry.x())/rX),2)
                    +std::powf(((y-geometry.y())/rY),2);

            if(p<1)
            {
                count+=1;
                sum+=qGray(image.pixel(x,y));
                valuesIn.append(qGray(image.pixel(x,y)));
            }
        }
    }

    mean=sum/count;
    float var=0.0;
    for (int i=0;i<valuesIn.length();i++)
    {
        var+=std::powf((valuesIn.at(i)-mean),2);

    }
    var/=count;

    stats.append(count);
    stats.append(mean);
    stats.append(std::powf(var,0.5));

    return stats;
}

QList<float> CustomScene::statsOfRectangle(QImage image, QRectF geometry)
{

    qDebug()<<"pointsRect123"<<geometry.x() <<geometry.y()<<geometry.height()<<geometry.width()<<image.width()<<image.height() << image.pixel(1000,1000);

    QList<float> stats;
    QList<int> valuesIn;
    float mean=0;
    float sum=0;
    int count=0;
    float p;
    for (int x=0;x<image.width();x++)
    {
        for(int y=0;y<image.height();y++)
        {
            p= (x>=geometry.x() && x<(geometry.x()+geometry.width()))
                    &&(y>=geometry.y()&&y<(geometry.y()+geometry.height()));

            if(p)
            {
                count+=1;
                sum+=qGray(image.pixel(x,y));
                valuesIn.append(qGray(image.pixel(x,y)));
            }


        }
    }

    mean=sum/count;

    float var=0.0;
    for (int i=0;i<valuesIn.length();i++)
    {
        var+=std::powf((valuesIn.at(i)-mean),2);

    }
    var/=count;

    stats.append(count);
    stats.append(mean);
    stats.append(std::powf(var,0.5));

    return stats;
}

//QList<float> CustomScene::statsOfRectangle(QImage image, QRectF geometry)
//{

//    qDebug()<<"pointsRect123"<<geometry.x() <<geometry.y()<<geometry.height()<<geometry.width()<<image.width()<<image.height() << image.pixel(1000,1000);

//    QList<float> stats;
//    QList<int> valuesIn;
//    float mean=0;
//    float sum=0;
//    int count=0;
//    float p;
//    for (int x=0;x<image.width();x++)
//    {
//        for(int y=0;y<image.height();y++)
//        {
//            p= (x>=geometry.x() && x<(geometry.x()+geometry.width()))
//                    &&(y>=geometry.y()&&y<(geometry.y()+geometry.height()));

//            if(p)
//            {
//                count+=1;
//                sum+=qGray(image.pixel(x,y));
//                valuesIn.append(qGray(image.pixel(x,y)));
//            }


//        }
//    }

//    mean=sum/count;

//    float var=0.0;
//    for (int i=0;i<valuesIn.length();i++)
//    {
//        var+=std::powf((valuesIn.at(i)-mean),2);

//    }
//    var/=count;

//    stats.append(count);
//    stats.append(mean);
//    stats.append(std::powf(var,0.5));

//    return stats;
//}

