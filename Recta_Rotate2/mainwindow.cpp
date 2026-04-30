#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include "applogger.h"

int rulerMode;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new customscene();
    itemRuler=new myitem();
    AppLogger::Instance()->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::cropExposureRegion(unsigned short *img, float theta, float isoX, float isoY, float mPixSpacing, size_t imgSize)
{
    float cTheta=-theta*3.141519/180;

    float x,y;
    for(int j=0;j<(imgSize);j++){
        for(int i=0;i<(imgSize);i++){

            x = (i*mPixSpacing-isoX)*cos(cTheta)+(j*mPixSpacing-isoY)*sin(-cTheta);
            y = (i*mPixSpacing-isoX)*sin(cTheta)+(j*mPixSpacing-isoY)*cos(cTheta);

            if(x>jawX2CurrentPosition||x<jawX1CurrentPosition||y>-jawY1CurrentPosition||y<-jawY2CurrentPosition)

                img[i+j*imgSize]=0;

        }
    }
}


void MainWindow::on_PB_Load_Image_clicked()
{
    QString filename = ("D:/Workflow/Test images/rawImage_2.raw");
    FILE *Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short* Image=new unsigned short[radSize*radSize];
    fread(Image,1,radSize*radSize*sizeof(unsigned short),Img);
//    for(int i=0;i<radSize*radSize;i++)
//    {
//        arr[i]=((Image[i]*255)/65535);
//    }
//    myImage = QImage(arr,3072,3072,QImage::Format_Grayscale8);
//    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
//    scene = new QGraphicsScene();
//    view = new QGraphicsView(scene);

//    ui->graphicsView->setScene(scene);
//    ui->graphicsView->fitInView(item);
//    scene->addItem(item);
    float p=imaginPixelSpacing;
    float offsetX =detectorxShift+imagerXCurrentPosition-kVxShift;
    float offsetY =detectoryShift+imagerYCurrentPosition-kVyShift;

    isoCentreX    =(-offsetX)+(p*radSize/2);//mm
    isoCentreY    =(offsetY)+(p*radSize/2);//mm
//    QString Path =("D:/Workflow/Test images/5.raw");
//    FILE *fp;
//    fp=fopen(Path.toStdString().c_str(),"wb+");
//    fwrite(claheI,sizeof(unsigned short),ImageSize*ImageSize,fp);
//    fclose(fp);
    qApp->processEvents();
    cropExposureRegion(Image,colliThetaCurrentPosition,isoCentreX,isoCentreY,imaginPixelSpacing,radSize);

    imgSizeBoundary=radSize;
//    fread(Image,1,radSize*radSize*sizeof(unsigned short),Img);
    unsigned char* arr=new unsigned char[radSize*radSize];
    for(int i=0;i<radSize*radSize;i++)
      {
            arr[i]=((Image[i]*255)/65535);
      }
    ui->graphicsView->resetTransform();
    ui->graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    myImage=QImage(arr,radSize,radSize,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new customscene();
    view = new QGraphicsView(scene);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    scene->addItem(item);

    QApplication::processEvents();
    this->updateDilineatorInfo(radSize);
    qApp->processEvents();

}

void MainWindow::updateDilineatorInfo(size_t imgSize)
{
    /*calculating Pixel Pitch*/
    float p=imaginPixelSpacing;


    //detector mechanical shift and user adjustable
    float offsetX=detectorxShift+imagerXCurrentPosition;
    float offsetY=detectoryShift+imagerYCurrentPosition;

    //isoCenter w.r.t scene cordinates in mm
    isoCentreX = (-offsetX)+(p*imgSize/2);//mm
    isoCentreY = (offsetY)+(p*imgSize/2);//mm


    /*pass jaw rect,dilineator rect,iso center to sceneMLC*/

    float jawX,jawY,jawW,jawH;
    float x,y,w,h,cTheta;


    x= wireX1CurrentPosition+isoCentreX;
    y=-wireY2CurrentPosition+isoCentreY;

    w=abs(wireX2CurrentPosition-wireX1CurrentPosition);
    h=abs(wireY2CurrentPosition-wireY1CurrentPosition);

    jawX = jawX1CurrentPosition+isoCentreX;
    jawY = -jawY2CurrentPosition+isoCentreY;

    jawW = abs(jawX2CurrentPosition-jawX1CurrentPosition);
    jawH = abs(jawY2CurrentPosition-jawY1CurrentPosition);

    cTheta=colliThetaCurrentPosition;
    QRectF *mRect1=new QRectF(x/p,y/p,w/p,h/p);
    QRectF *mRect2=new QRectF(jawX/p,jawY/p,jawW/p,jawH/p);

    JawRect = new QRectF(jawX/p,jawY/p,jawW/p,jawH/p);

    scene->receiveDrawRectSignal(mRect1,mRect2,cTheta,isoCentreX,isoCentreY,p);

}


void MainWindow::on_PB_Clockwise_Rotate_clicked()
{

    double rotateStep =1;
    rotatorStep = +rotateStep;
    scene->rotateDrawRect(rotatorStep);
//    double rotateStep;
//    if (q < -1)
//    {
//          q++;

//        double rotateStep = q;
//        qDebug()<<"value q+++"<<q;

//        float p=imaginPixelSpacing;
//        float cTheta = -rTheta*(3.14/180);
//        dTheta = rotateStep;//rotation step
//        cTheta = (dTheta+rTheta)*(3.14/180);


        //detector mechanical shift and user adjustable

//        float offsetX=detectorxShift+imagerXCurrentPosition;
//        float offsetY=detectoryShift+imagerYCurrentPosition;

        //isoCenter w.r.t scene cordinates in mm

//        isoCentreX = (-offsetX)+(p*radSize/2);//mm
//        isoCentreY = (offsetY)+(p*radSize/2);//mm
//        scene->rectDefault1->setRotation((qreal)cTheta*(180/3.14));
//        scene->rectDefault1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);


//        rx1=(scene->rect7->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//        qDebug()<<"rx1-----:"<<rx1;
//        rx2=(scene->rect8->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//        qDebug()<<"rx2-----:"<<rx2;
//        ry1=(isoCentreY/p-scene->rect9->sceneBoundingRect().topLeft().y())*p;
//        qDebug()<<"ry1-----:"<<rx1;
//        ry2=(isoCentreY/p-scene->rect6->sceneBoundingRect().topLeft().y())*p;
//        qDebug()<<"ry2-----:"<<rx2;
//        cx1=(scene->centerDefault1->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//        qDebug()<<"cx1-----:"<<cx1;


//        qDebug()<<"TopLeft---:"<<QPointF(scene->rect1->sceneBoundingRect().topLeft().x(),scene->rect1->sceneBoundingRect().topLeft().y());
//        qDebug()<<"TopRight---:"<<QPointF(scene->rect3->sceneBoundingRect().topRight().x(),scene->rect3->sceneBoundingRect().topRight().y());
//        qDebug()<<"BottomLeft---:"<<QPointF(scene->rect4->sceneBoundingRect().bottomLeft().x(),scene->rect4->sceneBoundingRect().bottomLeft().y());
//        qDebug()<<"BottomRight---:"<<QPointF(scene->rect5->sceneBoundingRect().bottomRight().x(),scene->rect5->sceneBoundingRect().bottomRight().y());

//    }
//else
//    {
//    n++;
//    rotateStep = n;
//    qDebug()<<"value n+++"<<n;
//    float p=imaginPixelSpacing;
//    float cTheta = -rTheta*(3.14/180);
//    dTheta = rotateStep;//rotation step
//    cTheta = (dTheta+rTheta)*(3.14/180);
//    qDebug()<<"rrrr"<<rTheta;
//    qDebug()<<"ccccc"<<cTheta;


    //detector mechanical shift and user adjustable

//    float offsetX=detectorxShift+imagerXCurrentPosition;
//    float offsetY=detectoryShift+imagerYCurrentPosition;

    //isoCenter w.r.t scene cordinates in mm

//    isoCentreX = (-offsetX)+(p*radSize/2);//mm
//    isoCentreY = (offsetY)+(p*radSize/2);//mm
//    scene->rectDefault1->setRotation((qreal)cTheta*(180/3.14));
//    scene->rectDefault1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);


//    rx1=(scene->rect7->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//    qDebug()<<"rx1-----:"<<rx1;
//    rx2=(scene->rect8->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//    qDebug()<<"rx2-----:"<<rx2;
//    ry1=(isoCentreY/p-scene->rect9->sceneBoundingRect().topLeft().y())*p;
//    qDebug()<<"ry1-----:"<<rx1;
//    ry2=(isoCentreY/p-scene->rect6->sceneBoundingRect().topLeft().y())*p;
//    qDebug()<<"ry2-----:"<<rx2;
//    cx1=(scene->centerDefault1->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//    qDebug()<<"cx1-----:"<<cx1;


//    qDebug()<<"TopLeft---:"<<QPointF(scene->rect1->sceneBoundingRect().topLeft().x(),scene->rect1->sceneBoundingRect().topLeft().y());
//    qDebug()<<"TopRight---:"<<QPointF(scene->rect3->sceneBoundingRect().topRight().x(),scene->rect3->sceneBoundingRect().topRight().y());
//    qDebug()<<"BottomLeft---:"<<QPointF(scene->rect4->sceneBoundingRect().bottomLeft().x(),scene->rect4->sceneBoundingRect().bottomLeft().y());
//    qDebug()<<"BottomRight---:"<<QPointF(scene->rect5->sceneBoundingRect().bottomRight().x(),scene->rect5->sceneBoundingRect().bottomRight().y());

//    scene->rotaterect->setRotation((qreal)cTheta*(180/3.14));
//    scene->rotaterect->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);
//    scene->addItem(scene->rotaterect);

//    }

}

void MainWindow::on_PB_Anticlockwise_Rotate_clicked()
{
    double rotateStep =1;
    rotatorStep = -rotateStep;
    scene->rotateDrawRect(rotatorStep);
//    double rotateStep;
//    if (n>=0)
//    {
//        n--;
//        rotateStep = n;
//        qDebug()<<"value n---"<<n;
//        float p=imaginPixelSpacing;
//        float cTheta = -rTheta*(3.14/180);
//        dTheta = rotateStep;//rotation step
//        cTheta = (dTheta+rTheta)*(3.14/180);


        //detector mechanical shift and user adjustable

//        float offsetX=detectorxShift+imagerXCurrentPosition;
//        float offsetY=detectoryShift+imagerYCurrentPosition;

        //isoCenter w.r.t scene cordinates in mm

//        isoCentreX = (-offsetX)+(p*radSize/2);//mm
//        isoCentreY = (offsetY)+(p*radSize/2);//mm
//        scene->rectDefault1->setRotation((qreal)cTheta*(180/3.14));
//        scene->rectDefault1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);


//        Rx1=(scene->rect7->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//        qDebug()<<"Rx1-----:"<<Rx1;
//        Rx2=(scene->rect8->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//        qDebug()<<"Rx2-----:"<<Rx2;
//        Ry1=(isoCentreY/p-scene->rect9->sceneBoundingRect().topLeft().y())*p;
//        qDebug()<<"Ry1-----:"<<Rx1;
//        Ry2=(isoCentreY/p-scene->rect6->sceneBoundingRect().topLeft().y())*p;
//        qDebug()<<"Ry2-----:"<<Rx2;
//        Cx1=(scene->centerDefault1->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//        qDebug()<<"Cx1-----:"<<Cx1;


//        qDebug()<<"TopLeft---:"<<QPointF(scene->rect1->sceneBoundingRect().topLeft().x(),scene->rect1->sceneBoundingRect().topLeft().y());
//        qDebug()<<"TopRight---:"<<QPointF(scene->rect3->sceneBoundingRect().topRight().x(),scene->rect3->sceneBoundingRect().topRight().y());
//        qDebug()<<"BottomLeft---:"<<QPointF(scene->rect4->sceneBoundingRect().bottomLeft().x(),scene->rect4->sceneBoundingRect().bottomLeft().y());
//        qDebug()<<"BottomRight---:"<<QPointF(scene->rect5->sceneBoundingRect().bottomRight().x(),scene->rect5->sceneBoundingRect().bottomRight().y());

//    }
//    else
//    {
//        q--;
//        rotateStep = q;
//    qDebug()<<"value q---"<<q;
//    float p=imaginPixelSpacing;
//    float cTheta = -rTheta*(3.14/180);
//    dTheta = rotateStep;//rotation step
//    cTheta = (dTheta+rTheta)*(3.14/180);


    //detector mechanical shift and user adjustable

//    float offsetX=detectorxShift+imagerXCurrentPosition;
//    float offsetY=detectoryShift+imagerYCurrentPosition;

    //isoCenter w.r.t scene cordinates in mm

//    isoCentreX = (-offsetX)+(p*radSize/2);//mm
//    isoCentreY = (offsetY)+(p*radSize/2);//mm
//    scene->rectDefault1->setRotation((qreal)cTheta*(180/3.14));
//    scene->rectDefault1->setTransformOriginPoint(isoCentreX/p,isoCentreY/p);


//    Rx1=(scene->rect7->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//    qDebug()<<"Rx1-----:"<<Rx1;
//    Rx2=(scene->rect8->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//    qDebug()<<"Rx2-----:"<<Rx2;
//    Ry1=(isoCentreY/p-scene->rect9->sceneBoundingRect().topLeft().y())*p;
//    qDebug()<<"Ry1-----:"<<Rx1;
//    Ry2=(isoCentreY/p-scene->rect6->sceneBoundingRect().topLeft().y())*p;
//    qDebug()<<"Ry2-----:"<<Rx2;
//    Cx1=(scene->centerDefault1->sceneBoundingRect().topLeft().x()-isoCentreX/p)*p;
//    qDebug()<<"Cx1-----:"<<Cx1;


//    qDebug()<<"TopLeft---:"<<QPointF(scene->rect1->sceneBoundingRect().topLeft().x(),scene->rect1->sceneBoundingRect().topLeft().y());
//    qDebug()<<"TopRight---:"<<QPointF(scene->rect3->sceneBoundingRect().topRight().x(),scene->rect3->sceneBoundingRect().topRight().y());
//    qDebug()<<"BottomLeft---:"<<QPointF(scene->rect4->sceneBoundingRect().bottomLeft().x(),scene->rect4->sceneBoundingRect().bottomLeft().y());
//    qDebug()<<"BottomRight---:"<<QPointF(scene->rect5->sceneBoundingRect().bottomRight().x(),scene->rect5->sceneBoundingRect().bottomRight().y());

    //    }
}


//void MainWindow::on_PB_Draw_Anlgle_clicked()
//{

//}

//void MainWindow::on_PB_Vertical_Ruler_toggled(bool checked)
//{
//    rulerMode = 0;

//    if(checked)
//        ToggleScale=2;

//    if(ToggleScale==2)
//    {
//        if(ui->PB_Ruler_Horizontal->isChecked())
//        {
//            //  qDebug()<<"Horz";
//            ui->PB_Ruler_Horizontal->setChecked(false);
//            //  sceneMLC->removeItem(itemRuler);

//        }
//    }

//    if(ToggleScale==1)
//        rulerMode=1;

//    if(checked){
//        //   qDebug()<<"Vertical checked";
//        scene->addItem(itemRuler);

//        ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
//        scene->setMode(customscene::Mode::NoMode);

//        itemRuler->setFlag(QGraphicsItem::ItemIsMovable,false);
//        itemRuler->setPos(1,0);
//        itemRuler->setScale(1/imaginPixelSpacing);
//        if(dMode==1)
//            itemRuler->setWidthHeight(3072,3072,0);
//        else
//            itemRuler->setWidthHeight(1536,1536,0);
//        itemRuler->setRotation(0);

//    }
//    else
//    {
//        // qDebug()<<"Vertical Unchecked";
//        scene->removeItem(itemRuler);
//        scene->setMode(customscene::Mode::DilineatorMode);
//    }
//    qApp->processEvents();
//}


void MainWindow::on_PB_Ruler_Horizontal_clicked()
{
    rulerMode=1;
    if(ui->PB_Ruler_Horizontal->isChecked())
    {

      scene->addItem(itemRuler);

//      itemRuler->setFlag(QGraphicsItem::ItemIsMovable,false);

      itemRuler->setPos(1,0);

      itemRuler->setScale(1/imaginPixelSpacing);

      itemRuler->setWidthHeight(3072,3072,0);
    }

    else
    {
        scene->removeItem(itemRuler);
    }

    qApp->processEvents();

}

void MainWindow::on_PB_Vertical_Ruler_clicked()
{
    rulerMode=0;
    if(ui->PB_Vertical_Ruler->isChecked())
    {

      scene->addItem(itemRuler);

      itemRuler->setPos(1,0);

      itemRuler->setScale(1/imaginPixelSpacing);

      itemRuler->setWidthHeight(3072,3072,0);
    }

    else
    {
        scene->removeItem(itemRuler);
    }
    qApp->processEvents();

}

void MainWindow::on_PB_Drawline_clicked()
{
    
}
