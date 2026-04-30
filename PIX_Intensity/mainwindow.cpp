#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QFileDialog"
#include "QFile"
#include "QDebug"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

bool leftDown=false,leftup=false;
Mat img;
Point cor1,cor2;
Rect box;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Evt = new Disp_Evt(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/couchtop/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");


    width=1536;
    height=1536;

     qDebug()<<"Image----";

    dispImg= new unsigned char[width*height];
    radbuf = new unsigned short[width*height];

    img = new unsigned short[1536*1536];

    fread(img,sizeof(unsigned short),width*height,Img);

    qDebug()<<"Image----";

    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = img[i]*255.0/65535.0;
    }
    qDebug()<<"Image----"<<img[100];

    myImage = QImage(dispImg,1536,1536,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
//    Evt= new QGraphicsScene(this);
    Evt->addItem(item);
    ui->graphicsView->setScene(Evt);
    ui->graphicsView->fitInView(item);

//    setMouseCallback("Original",mouse_call);

}


void MainWindow::on_Area_select_clicked()
{
    Evt->selectedTool=1;
}

void MainWindow::on_pushButton_2_clicked()
{
    QRect area(0, 0, 100, 100);
    QImage image = QImage(dispImg,1536,1536,QImage::Format_Grayscale8).copy(area);
    double row= image.width();
//    double intensity;
    intensity= new unsigned char[1536*1536];
    for(int i=0;i<row;i++)
    {
         intensity[i] = image.pixel(QPoint(i,0))*255.0/65535.0;
    }
    qDebug()<<"pixel value"<<intensity[100];
}

