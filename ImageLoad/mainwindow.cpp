#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsscene.h"
#include <stdio.h>
#include <string.h>
#include <QCheckBox>

#define DEBUG


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new GraphicsScene();


//    ui->GraphicsScene->setscene(scene);
    QObject::connect(scene,SIGNAL(measuredrawn(QGraphicsItem*)),this,SLOT(Updatemeasuredrawn(QGraphicsItem*)));

}

void MainWindow::Updatemeasuredrawn(QGraphicsItem *measureitem)
{

    Graphicitemlist<< measureitem;
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadPushButton_clicked()
{

    int width = 3072;
    int height = 3072;
    int offset = 16;

    char strInputFile[]  = "D:\\0.Method - Copy\\New folder\\FinImage.raw";




        FILE* pInput  = NULL;
        buf = new unsigned short[width*height];

        pInput  = fopen( "D:\\Workflow\\Test images\\rawImage_2.raw","r" );
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




#ifdef DEBUG
    qDebug() << "File: " <<Pix;
    qDebug() << "Depth: " << p.depth();
    qDebug() << "Width: " << p.width();
    qDebug() << "Height: " << p.height();

#endif

//    if (sene)
//    {
        qDebug() << "No Scene!";

//        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->fitInView(itm,Qt::KeepAspectRatio);
        scene->addItem(itm);




//        scene->addPixmap(p);
//    }

}


void MainWindow::on_clearPushButton_clicked()
{
//    scene->removeItem(itm);
//    delete itm
       qDebug()<<"Entering clear--1";
       for(int i=0; i<Graphicitemlist.length();i++)
       {
           scene->removeItem(Graphicitemlist.at(i));

       }



//    scene->clr();

    itm=NULL;
    str=NULL;
    buf=NULL;


//    }
}

void MainWindow::on_checkBox_clicked()
{
    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);

    scene->temp(GraphicsScene::Line);

}

void MainWindow::on_checkBox_2_clicked()
{
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(false);
    scene->temp(GraphicsScene::Ellipse);
}

void MainWindow::on_checkBox_3_clicked()
{
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(true);
    scene->temp(GraphicsScene::Rectangle);
}
