#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QFileDialog"
#include "QFile"
#include "QDebug"
#include "QByteArray"
#include "applogger.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

QFile file("D:\\pixel.csv");
QTextStream stream(&file);

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

void MainWindow::plotgraph(QCustomPlot *customPlot)
{
    QVector<double>y(2000);

    for (int i=0;i<256;i++)
    {
        y[i]= i;
    }

    QVector<double>x(2000);

    qDebug()<<"Intensity"<<intensity[50]<<QString(intensity[50]).toDouble();

    row= image.width();

//    float *f = new float[row];

//    memcpy(intensity, f, sizeof(f));

    QByteArray  writeData;

    for(int i=0;i< row;i++)
    {
        writeData= QByteArray(reinterpret_cast<char*>(intensity), sizeof(intensity));
    }

//    for(int i=0;i< row;i++)
//    {
//        qDebug()<<"float "<<f[i];
//    }

    unsigned char var1=image.pixel(QPoint(50,0));
    QString sa = var1;


    qDebug()<<"byte array"<<sa;
    for(int i=0;i< row;i++)
    {
        unsigned char var=image.pixel(QPoint(i,0));
 //         x = image.pixel(QPoint(i,0))*255.0/65535.0;
         x.push_back(QString(var).toDouble());
    }
    qDebug()<<"pixel value---"<<x[50]<<dispImg[50];

    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(0,200);
    customPlot->yAxis->setRange(0,256);

//    QRect area(0, 0, 100, 100);
//    QImage image = QImage(dispImg,1536,1536,QImage::Format_Grayscale8).copy(area);
//    double row= image.width();
// //    double intensity;
//    intensity= new unsigned char[1536];
//    for(int i=0;i<row;i++)
//    {
//         intensity[i] = image.pixel(QPoint(i,0));

//    }
//    qDebug()<<"pixel value---"<<intensity[99];

}

void MainWindow::on_Load_Image_clicked()
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

    dispImg= new unsigned char[width*height];
    radbuf = new unsigned short[width*height];

    img = new unsigned short[1536*1536];

    fread(img,sizeof(unsigned short),width*height,Img);

    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = img[i]*255.0/65535.0;
    }
    qDebug()<<"Image----"<<img[100];

    myImage = QImage(dispImg,1536,1536,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    Evt->addItem(item);
    ui->graphicsView->setScene(Evt);
    ui->graphicsView->fitInView(item);
}

void MainWindow::on_Select_ROI_clicked()
{
     Evt->selectedTool=1;
}

void MainWindow::on_Pix_Cal_clicked()
{
//    qDebug()<<"Rectangle"<<Evt->newrect.width()<<Evt->newrect.height();
    QRect area(294, 838, 1130, 1);
    image = QImage(dispImg,1536,1536,QImage::Format_Grayscale8).copy(area);
    row= image.width();
    col= image.height();
    intensity= new unsigned char[row*col];
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
         intensity[i*row+j] = image.pixel(QPoint(j,i));
//         qDebug()<<intensity[i*row+j];
        }

    }

    qDebug()<<"pixel value---"<<intensity[50]<<row<<col;
}

void MainWindow::on_Graph_plot_clicked()
{
    plotgraph(ui->customPlot);
    ui->customPlot->replot();
}

void MainWindow::on_smoothening_clicked()
{
    smooth = new unsigned short[1536*1536];

    for(int i=0;i<1536;i++)
    {
        for(int j=0;j<1536;j++)
        {
            if(dispImg[i*1536+j]>=200)
            {
                smooth[i*1536+j]=dispImg[i*1536+j]*65535.0/255.0;
            }
            if(dispImg[i*1536+j]<=40)
            {
                smooth[i*1536+j]=dispImg[i*1536+j]*65535.0/255.0;
            }
            if(dispImg[i*1536+j]>40)
            {
                smooth[i*1536+j]=40*65535.0/255.0;
            }
        }
    }
    QString path="D:\\couchtop\\projD1_215.raw";
    FILE *fp;
    fopen_s(&fp,path.toStdString().c_str(),"wb+");
    fwrite(smooth,sizeof(unsigned short),1536*1536,fp);
    fclose(fp);
    qDebug()<<"write finished";

}

void MainWindow::on_Invert_clicked()
{
    unsigned char* dispImg2=new unsigned char[1536*1536];
    qDebug()<<"disimage:"<<dispImg[0];
    for(int i=0;i<1536*1536;++i)
    {
        dispImg2[i] = 255-dispImg[i];
    }
    qDebug()<<"disimage1:"<<dispImg2[0];
    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(1536,1536,CV_8UC1,dispImg2);
    imgbuf.convertTo(img,-1,1,0);

    imgOut1=new uchar [1536*1536];
    for(int i=0;i<1536*1536;i++)
    {
        imgOut1[i]=img.data[i];
    }

    QImage q_image2 = QImage(imgOut1,1536,1536,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image2));
//    scene= new QGraphicsScene(this);
    Evt->addItem(item);
    ui->graphicsView->setScene(Evt);
    ui->graphicsView->fitInView(item);
}


void MainWindow::on_Row_clicked()
{

}

void MainWindow::on_pix_clicked()
{
    QRect area(294, 838, 1130, 1);
    q_image2 = QImage(imgOut1,1536,1536,QImage::Format_Grayscale8).copy(area);
    row= image.width();
    RowPix= new unsigned char[row];

    for(int i=0;i<row;i++)
    {
        RowPix[i] = image.pixel(QPoint(i,0));
        qDebug()<<RowPix[i];
    }


    qDebug()<<"pixel value---"<<intensity[50]<<row<<col;
}
