#include "customescene.h"
#include <QApplication>
extern double xS;
extern double yS;
extern double wS;
extern double hS;
bool EnableHandle[8];

customescene *scene1;
customescene *scene2;
customescene *scene3;
int sceneMode1;
QRectF output;
int axialSliderMax;
extern int axialSliderValue;

extern int ctDIM1;
extern int ctDIM2;
extern int ctDIM3;
QPointF resizeOffset1=QPointF(0,0);
QPointF resizeOffset2=QPointF(0,0);
QPointF resizeOffset3=QPointF(0,0);

namespace
{
class RectResizer : public SizeGripItem::Resizer
{
public:
    virtual void operator()(QGraphicsItem* item, const QRectF& rect)
    {
        //        QGraphicsRectItem* rectItem =
        //                dynamic_cast<QGraphicsRectItem*>(item);
        CustomItem* rectItem = dynamic_cast<CustomItem*>(item);

        if (rectItem)
        {
            rectItem->setRect(rect);
        }
    }
};

class EllipseResizer : public SizeGripItem::Resizer
{
public:
    virtual void operator()(QGraphicsItem* item, const QRectF& rect)
    {
        qDebug()<<"eneerellip";
        CustomItemEllipse* ellipseItem =  dynamic_cast<CustomItemEllipse*>(item);

        if (ellipseItem)
        {
            ellipseItem->setRect(rect);
        }
    }
};
}

customescene::customescene()
{
        drawPenContour=QPen(Qt::red, 1, Qt::SolidLine);
        ellip=0;

        var1=0;
        var2=0;
        var3=512;
        var4=512;
        ctDIM1=512;
        ctDIM2=512;
        ctDIM3=512;

}

void customescene::setScene(customescene *sceneA,customescene *sceneB,customescene *sceneC,customescene::Mode mode)
{
    scene1=sceneA;
    scene2=sceneB;
    scene3=sceneC;
    sceneMode1=mode;
    sceneMode=mode;
    axialSliderMax=511;

}

void customescene::setMode(customescene::Mode mode)
{
    sceneMode=mode;
}

void customescene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug()<<"sceneMode "<<sceneMode;
    if(sceneMode==DrawEllipse)
    {
        origPoint = event->scenePos();

    }
//    else
//        break;

    QGraphicsScene::mousePressEvent(event);


}

void customescene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode==DrawEllipse)
    {

    qDebug()<<"qqqqqqqqqqqqq";

    qDebug()<<"moveretgfg"<<var1<<var2<<var3<<var4<<origPoint;

    QPointF point = event->scenePos(); // Get the current mouse position

    /* Find out how much mouse has moved from the initial point
         * X Direction movement = width of rectangle,y direction movement = height of rectangle*/


    int w = point.x()-origPoint.x();
    int h = point.y()-origPoint.y();
    //            std::cout << "w: " << w << " h:" << h << std::endl;


    if(!ellip){
        if((origPoint.x()>var1 && origPoint.x()<var1+var3) && (origPoint.y()>var2 && origPoint.y()<var2+var4))
        {
            // create new rectangle item
            ellip = new QGraphicsEllipseItem;

            this->addItem(ellip);
//            if(cbctloaded==0)
                ellip->setPen(drawPenContour);
//            else
//               ellip->setPen(drawPen);

            ellip->setFlag(QGraphicsItem::ItemIsMovable,true);
            //                rect->setFlag(QGraphicsItem::ItemSendsScenePositionChanges,true);
            ellip->setZValue(1);


        }
    }
    // adjust position
    if(ellip!=0 && (event->scenePos().x()>var1 && event->scenePos().x()<var1+var3) &&(event->scenePos().y()>var2 && event->scenePos().y()<var2+var4))
    {
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
    }
    }
    QGraphicsScene::mouseMoveEvent(event);
//    else
//        break;


}

void customescene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode==DrawEllipse)
    {
//        this->setMode(customescene::Mode::NoMode);
//        return;
    if(ellip==NULL)
        return;

//    ROIDrawn = 2;

    output = ellip->mapRectToScene(ellip->rect());
    this->removeItem(ellip);

    delete ellip;
    ellip = NULL;
  //  count++;

    /*save the ROI's (type, position)to structure Drawing(both in scene1 and scene2)*/
    myDrawingA=new Drawing;
    myDrawingA->type="ellipse";
    myDrawingA->rect1 = output;

    myDrawingB = new Drawing;
    myDrawingB->type = "rectangle";
    myDrawingB->rect1 = output;


    scene1->setMode(customescene::Mode::NoMode);
    scene2->setMode(customescene::Mode::NoMode);

    myDrawingC = new Drawing;
    myDrawingC->type = "rectangle";
    myDrawingC->rect1 = output;

    scene3->setMode(customescene::Mode::NoMode);

    this->DrawRectSlot(output);
    }

    QGraphicsScene::mouseReleaseEvent(event);
//    else
//        break;
}


void customescene::DrawRectSlot(QRectF output)
{
//
    ellipseItem1 = new CustomItemEllipse;
    ellipseItem1->setRect(QRectF(0,0,output.width(),output.height()));
    ellipseItem1->setPos(output.x(),output.y());
    ellipseItem1->setPen(drawPenContour);

    ellipseItem1->setFlag(QGraphicsItem::ItemIsMovable);

    for(int i=0;i<8;i++)
    {
        EnableHandle[i]=1;
    }

    scene1->addItem(ellipseItem1);

        xS = -4*(ctDIM1/512.0);
        yS = -4*(ctDIM2/512.0);
        wS = 8*(ctDIM1/512.0);
        hS = 8*(ctDIM2/512.0);

      rectSizeGripItem1 =new SizeGripItem(xS,yS,wS,hS,new EllipseResizer, ellipseItem1);

   // rectSizeGripItem1 =new SizeGripItem(new EllipseResizer, ellipseItem1);

    QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem(QRectF,int)));
    QObject::connect(ellipseItem1,SIGNAL(itemChanged(QPointF)),this,SLOT(respondToitemChange(QPointF)));

//    return;

    rectItem2 = new CustomItem;
    rectItem2->setRect(QRectF(0,0,output.width(),(output.height()*(axialSliderMax+1))/ctDIM2));

    //rectItem2->setRect(QRectF(0,0,output.width(),output.height()));

    rectItem2->setPos(output.x(),((((axialSliderMax-axialSliderValue)*var4)/ctDIM3-((output.height()/2)*var4)/ctDIM2)* ctDIM3)/var4);

       // rectItem2->setPos(output.x(),axialSliderMax-axialSliderValue-output.height()/2);
//        rectItem2->setPos(axialSliderMax-output.width()+1-output.x(),output.y()+(axialSliderMax-axialSliderValue-output.y()));

    rectItem2->setPen(drawPenContour);


    scene2->addItem(rectItem2);





    rect2 = rectItem2->mapRectToScene(rectItem2->rect());


        xS = -4*(ctDIM1/512.0);
        yS = -4*(ctDIM3/512.0);
        wS = 8*(ctDIM1/512.0);
        hS = 8*(ctDIM3/512.0);


      rectSizeGripItem2 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, rectItem2);

  //  rectSizeGripItem2 =new SizeGripItem(new RectResizer, rectItem2);

    QObject::connect(rectSizeGripItem2,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem1(QRectF,int)));
    QObject::connect(rectItem2,SIGNAL(itemChanged(QPointF)),this,SLOT(respondToitemChange1(QPointF)));



    // for 3D, add rectangle to 3rd scene

        for(int i=0;i<8;i++)
        {
                EnableHandle[i]=1;
        }

        rectItem3 = new CustomItem;
        rectItem3->setRect(QRectF(0,0,(output.width()*ctDIM2)/ctDIM1,(output.height()*(axialSliderMax+1))/ctDIM2));

       // rectItem3->setRect(QRectF(0,0,output.width(),output.height()));
       // rectItem3->setPos(output.y(),output.y()+(axialSliderMax-axialSliderValue-output.y()));

        rectItem3->setPos(output.y(),((((axialSliderMax-axialSliderValue)*var4)/ctDIM3-((output.height()/2)*var4)/ctDIM2)* ctDIM3)/var4);

       // rectItem3->setPos(output.y(),axialSliderMax-axialSliderValue-output.height()/2);

        rectItem3->setPen(drawPenContour);
        scene3->addItem(rectItem3);

        rect3 = rectItem3->mapRectToScene(rectItem3->rect());

        xS = -4*(ctDIM2/512.0);
        yS = -4*(ctDIM3/512.0);
        wS = 8*(ctDIM2/512.0);
        hS = 8*(ctDIM3/512.0);

        rectSizeGripItem3 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, rectItem3);

       // rectSizeGripItem3 =new SizeGripItem(new RectResizer, rectItem3);
        QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));
        QObject::connect(rectItem3,SIGNAL(itemChanged(QPointF)),this,SLOT(respondToitemChange2(QPointF)));




        rectSizeGripItem1->itemChanged(ellipseItem1->rect(),1);
        ellipseItem1->itemChanged(ellipseItem1->pos());

//        rectSizeGripItem1->setFlag(QGraphicsItem::ItemIsMovable);




}

void customescene::respondToitem(QRectF rectn, int k)
{
//    return;
    //differentiate between move and resize

//   / return;
    qDebug()<<"respondToitem  "<<rectn<<k;

    try
    {

     rect2 = (rectItem2->rect());



    // when the scene1 ROI item is moved but not resized using size grip item
    if(k==0)
    {

            //qDebug()<<"Hello:"<<rectItem3->pos()<<rectItem3->rect()<<rectItem3->scenePos()<<rectItem3->sceneBoundingRect()<<rectItem3->boundingRect();
            // ignore signals from scene2 ROI item movement
            rectItem2->blockSignals(true);
            // set to postion from size grip item
           // rectItem2->setX(axialSliderMax-rectn.width()+1-rectn.x());
           rectItem2->setX(rectn.x()); //Commented on 28-11-2020

            // allow signals from scene2 ROI item movement
            rectItem2->blockSignals(false);

            rect3 = (rectItem3->rect());
            // for scene3 ROI item
            rectItem3->blockSignals(true);
            rectItem3->setX(rectn.y());

           // rectItem3->setX( /*axialSliderMax-*/axialSliderValue+1-rectn.height()/2);



            rectItem3->blockSignals(false);

            xS = -4*(ctDIM2/512.0);
            yS = -4*(ctDIM3/512.0);
            wS = 8*(ctDIM2/512.0);
            hS = 8*(ctDIM3/512.0);

            if(rectSizeGripItem3!=NULL)
            {
                delete rectSizeGripItem3;
               // rectSizeGripItem3->handleItems_.clear();
                rectSizeGripItem3=NULL;
            }

            rectSizeGripItem3 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, rectItem3);
            scene3->update(); // for Axial 01/09/2021
            _sleep(200); // Delay
//            qApp->processEvents();


            QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));


            myDrawingC->rect1 = rectItem3->mapRectToScene(rectItem3->rect());

    }


    // when the scene1 ROI item is resized using size grip item
    else
    {
        //        mover=k;
        //        posPoints.setX(rectn.x());
        //        posPoints.setY(rectn.y());


            xS = -4*(ctDIM2/512.0);
            yS = -4*(ctDIM3/512.0);
            wS = 8*(ctDIM2/512.0);
            hS = 8*(ctDIM3/512.0);

            // adjust the position& size of scene2 & scene3 ROI items
            rectItem2->setRect(QRectF(rectn.x(),rect2.y(),rectn.width(),rect2.height()));
            rect3 = (rectItem3->rect());
//            rectItem3->setRect(QRectF(rectn.y(),rect3.y(),rectn.height(),rect3.height()));

//            rectItem3->setRect(QRectF(axialSliderValue+1-rectn.height()/2,rect3.y(),rectn.height(),rect3.height()));
//            rectItem3->setRect(QRectF(axialSliderMax-axialSliderValue+1-rectn.height()/2,rect3.y(),rectn.height(),rect3.height()));

            rectItem3->setRect(QRectF(0,rect3.y(),rectn.height(),rect3.height()));

    // 31/08/2021      //  qDebug()<<"rectss value "<<axialSliderMax-axialSliderValue+1-rectn.height()/2<<rect3.y()<<rectn.height()<<rect3.height();

            if(rectSizeGripItem3!=NULL)
            {
                delete rectSizeGripItem3;
//                rectSizeGripItem3->handleItems_.clear();
                rectSizeGripItem3=NULL;
            }

//            qApp->processEvents();


            qDebug()<<"rectss value1 ";

            rectSizeGripItem3 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, rectItem3);
             scene3->update();  //01/09/2021
            _sleep(200); // Delay
            QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));

            myDrawingC->rect1 = rectItem3->mapRectToScene(rectItem3->rect());


    }


        xS = -4*(ctDIM1/512.0);
        yS = -4*(ctDIM3/512.0);
        wS = 8*(ctDIM1/512.0);
        hS = 8*(ctDIM3/512.0);



    qDebug()<<"rectss value2 ";

     if(rectSizeGripItem2!=NULL)
     {
         try
         {
         delete rectSizeGripItem2;
         }
         catch(std::exception &err)
         {
             qDebug()<<"Exception came in respond to item"<<err.what();
         }
         //rectSizeGripItem2->handleItems_.clear();
         rectSizeGripItem2=NULL;
     }


     rectSizeGripItem2 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, rectItem2);
     scene2->update();   //01/09/2021
   _sleep(200); // Dealy
//     qApp->processEvents();


     qDebug()<<"rectss value3 ";


    QObject::connect(rectSizeGripItem2,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem1(QRectF,int)));

    if(k==0)
    {
        myDrawingA->rect1 = QRectF(rectn.x()+resizeOffset1.x(),rectn.y()+resizeOffset1.y(),rectn.width(),rectn.height());

    }
    else
    {

        resizeOffset1=rectn.topLeft();

        qDebug()<<"rectss value4";
        // ellipse mode
            myDrawingA->rect1 = ellipseItem1->mapRectToScene(rectn);



        // rectangle mode


        qDebug()<<"rectss value5";

        //        else if(sceneMode1==5)
        //            myDrawingA->pos = myDrawingA->pos+resizeOffset1;


    }



    myDrawingB->rect1 = rectItem2->mapRectToScene(rectItem2->rect());

//    SizeGripposition = tempGrip;
//    rectSizeGripItem2->setFlag(QGraphicsItem::ItemIsMovable);
//    rectSizeGripItem3->setFlag(QGraphicsItem::ItemIsMovable);



    qDebug()<<"Crashchevk" <<(rectSizeGripItem1==NULL)<<(rectSizeGripItem2==NULL)<<(rectSizeGripItem3==NULL);

//    rectSizeGripItem1 =new SizeGripItem(xS,yS,wS,hS,new EllipseResizer, ellipseItem1);
//    rectSizeGripItem2 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, rectItem2);
//    rectSizeGripItem3 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, rectItem2);



    qDebug()<<"rectss value6";
    }
    catch(std::exception &err)
    {
        qDebug()<<"Exception came in respond to item"<<err.what();
    }

    qApp->processEvents();




}

void customescene::respondToitem1(QRectF rectn, int k)
{

//    return;
    try
    {
    // when the scene2 ROI item is moved but not resized using size grip item

        qDebug()<<"Entered";

        rect1 = (ellipseItem1->rect());
        if(k==0)
        {
            // ignore signals from scene1 ROI item movement
            // set to postion from size grip item
            // allow signals from scene1 ROI item movement

                ellipseItem1->blockSignals(true);
                // ellipseItem1->setX(rectn.x());
                ellipseItem1->setX(/*axialSliderMax-rectn.width()+1-*/rectn.x());
                ellipseItem1->blockSignals(false);



        }
        // when the scene2 ROI item is resized using size grip item
        // adjust the position& size of scene1  ROI item
        else
        {

                ellipseItem1->setRect(QRectF(rectn.x(),rect1.y(),rectn.width(),rect1.height()));


                xS = -4*(ctDIM1/512.0);
                yS = -4*(ctDIM2/512.0);
                wS = 8*(ctDIM1/512.0);
                hS = 8*(ctDIM2/512.0);


            if(rectSizeGripItem1!=NULL)
            {
                scene1->removeItem(rectSizeGripItem1);

                delete rectSizeGripItem1;
                //rectSizeGripItem1->handleItems_.clear();
                rectSizeGripItem1=NULL;
            }


            rectSizeGripItem1 =new SizeGripItem(xS,yS,wS,hS,new EllipseResizer, ellipseItem1);
            scene1->update();   //01/09/2021
             _sleep(200); // Delay

//            qApp->processEvents();


            QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem(QRectF,int)));

            //            myDrawingA->rect1 = ellipseItem1->mapRectToScene(ellipseItem1->rect());;

        }
        myDrawingA->rect1 = ellipseItem1->mapRectToScene(ellipseItem1->rect());;





    // adjust the position& size of scene3  ROI item

        rect3 = (rectItem3->rect());
        if(k==0){
            rectItem3->blockSignals(true);
            rectItem3->setY(rectn.y());
            rectItem3->blockSignals(false);
        }
        else
            rectItem3->setRect(QRectF(rect3.x(),rectn.y(),rect3.width(),rectn.height()));

        xS = -4*(ctDIM2/512.0);
        yS = -4*(ctDIM3/512.0);
        wS = 8*(ctDIM2/512.0);
        hS = 8*(ctDIM3/512.0);

        qDebug()<<"respond1";

        if(rectSizeGripItem3!=NULL)  // From Here
        {
            try
            {
                scene3->removeItem(rectSizeGripItem3);
                delete rectSizeGripItem3;
            }
            catch(std::exception &err)
            {
                qDebug()<<"Exception came in respond to item1"<<err.what();
            }
           // rectSizeGripItem3->handleItems_.clear();
            rectSizeGripItem3=NULL;
        }

        _sleep(200); // Delay

        qDebug()<<"respond11";


        rectSizeGripItem3 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, rectItem3);
         scene3->update();   //01/09/2021
        _sleep(200); // Delay

//        qApp->processEvents();

        qDebug()<<"respond111";

        QObject::connect(rectSizeGripItem3,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem2(QRectF,int)));

        myDrawingC->rect1 = rectItem3->mapRectToScene(rectItem3->rect());


    ///CAUT
    if(k==0)
    {
        // myDrawingB->rect1 = rectn;

        myDrawingB->rect1 = QRectF(rectn.x()+resizeOffset2.x(),rectn.y()+resizeOffset2.y(),rectn.width(),rectn.height());




    }///CAUT
    else
    {

//        qDebug()<<"respond3";

        myDrawingB->rect1 = rectItem2->mapRectToScene(rectn);
        resizeOffset2=rectn.topLeft();

//        qDebug()<<"respond4";


    }
    }
    catch(std::exception &err)
    {
        qDebug()<<"Exception came in respond to item1"<<err.what();
    }

    qDebug()<<"respond111";

    _sleep(200);
//    qApp->processEvents();

}



void customescene::respondToitem2(QRectF rectn, int k)
{
//    return;
    try
    {



        rect1 = (ellipseItem1->rect());
        // when the scene3 ROI item is moved but not resized using size grip item
        if(k==0)
        {
            // ignore signals from scene1 ROI item movement
            // set to postion from size grip item
            // allow signals from scene1 ROI item movement
            ellipseItem1->blockSignals(true);
            ellipseItem1->setY(rectn.x());
            ellipseItem1->blockSignals(false);
        }
        // when the scene3 ROI item is resized using size grip item
        // adjust the position& size of scene3  ROI item
        else
        {
            ellipseItem1->setRect(QRectF(rect1.x(),rectn.x(),rect1.width(),rectn.width()));
        }

        xS = -4*(ctDIM1/512.0);
        yS = -4*(ctDIM2/512.0);
        wS = 8*(ctDIM1/512.0);
        hS = 8*(ctDIM2/512.0);



        if(rectSizeGripItem1!=NULL)
        {
            delete rectSizeGripItem1;
            rectSizeGripItem1=NULL;
        }


        rectSizeGripItem1 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, ellipseItem1);
         scene1->update();   //01/09/2021
        _sleep(200); // Delay
//        qApp->processEvents();


        QObject::connect(rectSizeGripItem1,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem(QRectF,int)));

        myDrawingA->rect1 = ellipseItem1->mapRectToScene(ellipseItem1->rect());

        rect2 = (rectItem2->rect());

    // when the scene3 ROI item is moved but not resized using size grip item
    // ignore signals from scene2 ROI item movement
    // set to postion from size grip item
    // allow signals from scene2 ROI item movement
    if(k==0)
    {
        rectItem2->blockSignals(true);
        rectItem2->setY(rectn.y());
        rectItem2->blockSignals(false);
    }
    // when the scene3 ROI item is resized using size grip item
    // adjust the position& size of scene2  ROI item
    else
        rectItem2->setRect(QRectF(rect2.x(),rectn.y(),rect2.width(),rectn.height()));


    xS = -4*(ctDIM1/512.0);
    yS = -4*(ctDIM3/512.0);
    wS = 8*(ctDIM1/512.0);
    hS = 8*(ctDIM3/512.0);



    if(rectSizeGripItem2!=NULL)
    {
        delete rectSizeGripItem2;
        rectSizeGripItem2=NULL;
    }


    rectSizeGripItem2 =new SizeGripItem(xS,yS,wS,hS,new RectResizer, rectItem2);
     scene2->update();   //01/09/2021
    _sleep(200); // Delay
//    qApp->processEvents();


    QObject::connect(rectSizeGripItem2,SIGNAL(itemChanged(QRectF,int)),this,SLOT(respondToitem1(QRectF,int)));

    myDrawingB->rect1 = rectItem2->mapRectToScene(rectItem2->rect());

    ///CAUT
    if(k==0)
    {
        //myDrawingC->rect1 = rectn;
        myDrawingC->rect1 = QRectF(rectn.x()+resizeOffset3.x(),rectn.y()+resizeOffset3.y(),rectn.width(),rectn.height());


    }
    else ///CAUT
    {
        myDrawingC->rect1 = rectItem3->mapRectToScene(rectn);
        resizeOffset3=rectn.topLeft();
    }
    }
    catch(std::exception &err)
    {
        qDebug()<<"Exception came in respond to item2"<<err.what();
    }

    qApp->processEvents();


}





void customescene::respondToitemChange(QPointF pos)
{




    // when the scene1 ROI is moved, get the current positions


        rect1 = ellipseItem1->mapRectToScene(ellipseItem1->rect());




    QRectF rectangle;



    qDebug()<<"check for pos"<<pos.x()<<pos.y()<<rect1.width()<<rect1.height();
    rectangle = QRectF(pos.x(),pos.y(),rect1.width(),rect1.height());


    // call function to respond to the change in position of scene1 ROI
    this->respondToitem(rectangle,0);

}

void customescene::respondToitemChange1(QPointF pos)
{
    // when the scene2 ROI is moved, get the current positions
    rect2 = rectItem2->mapRectToScene(rectItem2->rect());

    QRectF rectangle = QRectF(pos.x(),pos.y(),rect2.width(),rect2.height());


    // call function to respond to the change in position of scene2 ROI
    this->respondToitem1(rectangle,0);
}

void customescene::respondToitemChange2(QPointF pos)
{
    // when the scene3 ROI is moved, get the current positions
    rect3 = rectItem3->mapRectToScene(rectItem3->rect());
    QRectF rectangle = QRectF(pos.x(),pos.y(),rect3.width(),rect3.height());
    // call function to respond to the change in position of scene3 ROI
    this->respondToitem2(rectangle,0);
}
