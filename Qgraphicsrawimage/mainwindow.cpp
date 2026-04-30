#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new drawit(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_6_clicked()
{
    //LOAD
   FILE* input=NULL;
   int w=3072;
   int h=3072;
   unsigned short* buf=new unsigned short[w*h];
   unsigned char* buff=new unsigned char[w*h];
   //unsigned short buff[3072][3072];
   memset(buf,0,w*h);
   memset(buff,0,w*h);
   input=fopen("D:\\RAD\\proj_1.raw","r");
   if(input){
     fread(buf,(w*h*sizeof(short)),1,input);
   }
    for(int j=0;j<=w*h-1;j++){
       buff[j]=(buf[j]*255)/65535;
   }
   //unsigned char* t= (unsigned char*)&buf[0];
   QImage myimage(&buff[0],w,h,QImage::Format_Grayscale8);
  // myimage = myimage.scaled(512, 512, Qt::IgnoreAspectRatio);
   //QImage myimage(t,w,h,QImage::Format_RGB16);
   scene->addPixmap(QPixmap::fromImage(myimage));
   ui->graphicsView->setScene(scene);
   ui->graphicsView->show();
   ui->graphicsView->fitInView(0,0,w,h,Qt::KeepAspectRatio);
}

void MainWindow::on_pushButton_7_clicked()
{
    //CLEAR
   FILE* input=NULL;
   int w=3072;
   int h=3072;
   unsigned short* buf=new unsigned short[w*h];
   unsigned char* buff=new unsigned char[w*h];
   //unsigned short buff[3072][3072];
   //memset(buf,0,w*h);
   input=fopen("D:\\PRITAM\\PRITAM\\QT\\task2(display and edit 8bit raw img)\\Qgraphicsrawimage\\rawImage_23_09_2019_10_34_15.raw","rb");
   if(input){
     fread(buf,w*h,0,input);
   }
    for(int j=0;j<=w*h;j++){
       buff[j]=(buf[j]*255)/65535;
   }
   //unsigned char* t= (unsigned char*)&buf[0];
   QImage myimage(&buff[0],w,h,QImage::Format_Grayscale8);
   //QImage myimage(t,w,h,QImage::Format_RGB16);
   scene->addPixmap(QPixmap::fromImage(myimage));
   ui->graphicsView->setScene(scene);
   ui->graphicsView->show();
   ui->graphicsView->fitInView(0,0,3072,3072,Qt::KeepAspectRatio);
}

void MainWindow::on_pushButton_8_clicked()
{
    //DEL ALL
  QList<QGraphicsItem*> AllGraphicsItems = scene->items();
  for(int i = 0; i < AllGraphicsItems.size()-1; i++)
  {
  QGraphicsItem *graphicItem = AllGraphicsItems[i];
  scene->removeItem(graphicItem);
  delete graphicItem;
  scene->update();
  }
  qDebug()<<"End of hideButtons()";
}

void MainWindow::on_pushButton_9_clicked()
{
    //DEL SEL
    QList<QGraphicsItem*> AllGraphicsItems = scene->selectedItems();
    for(int i = 0; i < AllGraphicsItems.size(); i++)
    {
    QGraphicsItem *graphicItem = AllGraphicsItems[i];
    scene->removeItem(graphicItem);
    delete graphicItem;
    scene->update();
    }
    qDebug()<<"End of hideButtons()";
  }



void MainWindow::on_pushButton_clicked()
{
    //RECT
    scene->selected=2;
}

void MainWindow::on_pushButton_2_clicked()
{
    //LINE
    scene->selected=1;
}

void MainWindow::on_pushButton_3_clicked()
{
    //FREE HAND
    scene->selected=5;
}

void MainWindow::on_pushButton_4_clicked()
{
    //ELLIPSE
    scene->selected=3;
}

void MainWindow::on_pushButton_5_clicked()
{
    //ANGLE
    scene->selected=4;
}

void MainWindow::on_Redraw_free_clicked()
{
    scene->redrawPaths();
}
