#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <string.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QHoverEvent>
#include <QScrollArea>
#include <iostream>
#include <QCoreApplication>
#include <opencv/cv.h>
#include <QGraphicsSceneMouseEvent>
#include <QObject>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sne = new mouse();
    wid=QApplication::desktop()->screenGeometry().width()/2;
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QObject::connect(sne,SIGNAL(buttonclick()),this,SLOT(onRightClicked()));
    QObject::connect(sne,SIGNAL(doubleclick()),this,SLOT(onDoubleClicked()));

}



MainWindow::~MainWindow()
{


    delete ui;
}


void MainWindow::onRightClicked()
{
    qDebug() << "right clicked";
//    qDebug()<<" main window delta values"<<sne->deltaX<<sne->deltaY;

    sne->deltaY = abs(sne->deltaY);
    sne->deltaX = abs(sne->deltaX);

//    qDebug()<<"deltaY"<<sne->deltaY<<sne->deltaY/3072.0;
//    qDebug()<<"deltaX"<<sne->deltaX<<sne->deltaX/3072.0;
//       widh = (sne->deltaX/3072.0)*4;
      qDebug()<<"angle"<<sne->angleInDegrees;



    if(sne->angleInDegrees >=45)
    {
        if(sne->angleInDegrees <=135)
        {
            sne->vartical = true;
            sne->heigh = (sne->deltaY/3072.0)*100;
           qDebug()<<"brightness"<<sne->heigh;
           if(sne->heigh>100)
           {
               sne->heigh=100;
               qDebug()<<"brightness"<<sne->heigh;
           }
//            qDebug()<<"vretical value1"<<sne->vartical<<"horizantal value1"<<sne->horizantal;
        }
        else
        {
           sne->vartical=false;
        }

    }

    if(sne->angleInDegrees >=0)
    {
        if(sne->angleInDegrees<=44)
        {
            sne->horizantal= true;
            sne->widh = (sne->deltaX/3072.0)*4;
           qDebug()<<"contrast"<<sne->widh;
           if(sne->widh>4)
           {
               sne->widh= 4;
                qDebug()<<"contrast"<<sne->widh;
           }


//            qDebug()<<"horizantal value1"<<sne->horizantal<<"vretical value1"<<sne->vartical;
        }
        else
         {
            sne->horizantal=false;
         }
    }
    if(sne->angleInDegrees  >=136)
    {
        if(sne->angleInDegrees  <=180)
        {
            sne->horizantal= true;
            sne->widh = (sne->deltaX/3072.0)*4;
           qDebug()<<"contrast"<<sne->widh;
           if(sne->widh>4)
           {
               sne->widh= 4;
                qDebug()<<" contrast"<<sne->widh;
           }
//            qDebug()<<"horizantal value2"<<sne->horizantal<<"vretical value2"<<sne->vartical;
        }
        else
         {
            sne->horizantal=false;
         }

    }

//    sne->heigh = sne->heigh +  sne->deltaY;
//    sne->widh = sne->widh +  sne->deltaX;

//    qDebug()<<" main window angleInDegrees "<<sne->angleInDegrees ;

//    qDebug()<<"value of vertical"<<sne->vartical<<"value of hotizanta"<<sne->horizantal;
    if(sne->vartical==true)
    {
        qDebug()<<"adjust the bright ness";
    }
    if(sne->horizantal==true)
    {
        qDebug()<<" adjust the constrst";
    }


    qDebug()<<"mainwindow"<< sne->angleInDegrees;

       cv::Mat image=cv::Mat(3072,3072,CV_8UC1,str);

       Mat imageBrighnessHigh100;
       if(sne->vartical==true)
       {
           image.convertTo(imageBrighnessHigh100, -1,1,sne->heigh);
           qDebug()<<"brightness"<<sne->heigh;
       }
      else
       {
          image.convertTo(imageBrighnessHigh100, -1,sne->widh,1);
          qDebug()<<"constrst"<<sne->widh;
       }

   //    qDebug()<<"cvmat1";

       QImage imgIn= QImage((uchar*) imageBrighnessHigh100.data,3072,3072,QImage::Format_Grayscale8);
//       qDebug()<<"cvmat2"<<heigh<<widh;
       Pix2 = QPixmap::fromImage(imgIn);
       itm2 = new QGraphicsPixmapItem(Pix2);
       sne->addItem(itm2);

}

void MainWindow::onDoubleClicked()
{
    cv::Mat image=cv::Mat(3072,3072,CV_8UC1,str);

    Mat imageBrighnessHigh100;
    image.convertTo(imageBrighnessHigh100, -1,1,1);
    qDebug()<<"double";
    QImage imgIn= QImage((uchar*) imageBrighnessHigh100.data,3072,3072,QImage::Format_Grayscale8);
    Pix2 = QPixmap::fromImage(imgIn);
    itm2 = new QGraphicsPixmapItem(Pix2);
    sne->addItem(itm2);
}


void MainWindow::wheelEvent(QWheelEvent *event)
{
    val = event->delta();

     cur = this->cursor().pos().x();
     double scaleFactor =1.1;
     if(cur<=wid)
     {

         if(event->delta()>0)
         {
             ui->graphicsView->scale(scaleFactor,scaleFactor);

         }
         else
         {
             ui->graphicsView->scale(1.0/scaleFactor,1.0/scaleFactor);
         }
     }
     else
     {
//         qDebug()<<"second view"<<cur;
         if(event->delta()>0)
         {
             ui->graphicsView_2->scale(scaleFactor,scaleFactor);
//              qDebug()<<"maptoscenegraphics2"<<ui->graphicsView_2->mapToScene(event->pos());
         }
         else
         {
             ui->graphicsView_2->scale(1.0/scaleFactor,1.0/scaleFactor);
         }
     }

}

void MainWindow::on_pushButton_clicked()
{


        int width = 3072;
        int height = 3072;
        int offset = 16;

        char strInputFile[]  = "D:/rawImage_23_09_2019_10_34_15.raw";





            FILE* pInput  = NULL;
            buf = new unsigned short[width*height];

            pInput  = fopen( "D:/rawImage_23_09_2019_10_34_15.raw","r" );
            qDebug()<<"fopen";

            fread(buf,sizeof(unsigned short),width*height,pInput);
            fclose(pInput);
            qDebug()<<"buffer"<<buf[720]<<sizeof(unsigned short);

            str = new unsigned char[width*height];
            sene = new QGraphicsScene(/*this*/);


            for (int i = 0; i < width*height; i++)
            {

               str[i] = (buf[i]/65535.0)*255;
            }
            qDebug()<<"str"<<str[704];


            Img = QImage(str, 3072, 3072, QImage::Format_Grayscale8);

            Pix = QPixmap::fromImage(Img);
            itm = new QGraphicsPixmapItem(Pix);
            QPixmap p(Pix);
            qDebug()<<"no scene!";
            qDebug() << "File: " <<Pix;
            qDebug() << "Depth: " << p.depth();
            qDebug() << "Width: " << p.width();
            qDebug() << "Height: " << p.height();
            hei= p.height();


            ui->graphicsView->setScene(sne);
            ui->graphicsView->fitInView(itm,Qt::KeepAspectRatio);
            sne->addItem(itm);



            FILE* pInput1  = NULL;
            buf1 = new unsigned short[width*height];

            pInput1  = fopen( "D:/rawImage_23_09_2019_10_34_15.raw","r" );
            qDebug()<<"fopen1";

            fread(buf1,sizeof(unsigned short),width*height,pInput1);
             qDebug()<<"fopen2";
            fclose(pInput1);
            qDebug()<<"buffer"<<buf1[720]<<sizeof(unsigned short);

            str1 = new unsigned char[width*height];
            sene = new QGraphicsScene(/*this*/);


            for (int i = 0; i < width*height; i++)
            {

               str1[i] = (buf1[i]/65535.0)*255;
            }
            qDebug()<<"str"<<str1[704];

            Img1 = QImage(str1, 3072, 3072, QImage::Format_Grayscale8);
            Pix1 = QPixmap::fromImage(Img1);
            itm1 = new QGraphicsPixmapItem(Pix1);


//        QGraphicsScene *sene = new QGraphicsScene(this);

        ui->graphicsView_2->setScene(sene);
        ui->graphicsView_2->fitInView(itm1,Qt::KeepAspectRatio);
        sene->addItem(itm1);



}



void MainWindow::on_pushButton_2_clicked()
{

// qDebug()<<"mainwindow"<< sne->angleInDegrees;

////        qDebug()<<"cvmat";
//    cv::Mat image=cv::Mat(3072,3072,CV_8UC1,str);

//    Mat imageBrighnessHigh100;
//    if(sne->vartical=)
//    image.convertTo(imageBrighnessHigh100, -1,widh,heigh);
////    qDebug()<<"cvmat1";

//    QImage imgIn= QImage((uchar*) imageBrighnessHigh100.data,3072,3072,QImage::Format_Grayscale8);
//    qDebug()<<"cvmat2"<<heigh<<widh;
//    Pix2 = QPixmap::fromImage(imgIn);
//    itm2 = new QGraphicsPixmapItem(Pix2);
////    qDebug()<<"custom scene";
//    sne->addItem(itm2);
////    qDebug()<<"custom scene exit";


}





