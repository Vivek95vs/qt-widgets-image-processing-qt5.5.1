#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QFileDialog"
#include "QFile"
#include "QDebug"
#include "QByteArray"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Scene= new QGraphicsScene(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Folder_clicked()
{
    QString filename = QFileDialog::getExistingDirectory(this,"Open Test Image","D:/couchtop/*.raw");
    std::string fileNameCPP;

    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }

    for(int iProj=0;iProj <321; iProj++)
    {
        fileNameCPP = filename.toStdString() + "\\projD2_" + std::to_string(iProj+1) + ".raw";
        FILE * Img;
        fopen_s(&Img, fileNameCPP.c_str(), "rb+");  // Open projection file to read.

        width=1536;
        height=1536;

        dispImg= new unsigned char[width*height];
        radbuf = new unsigned short[width*height];

        img = new unsigned short[1536*1536];
        fread(img,sizeof(unsigned short),width*height,Img);
        fclose(Img);

        for(int i=0;i<width*height;++i)
        {
            dispImg[i] = img[i]*255.0/65535.0;
        }

        dispImg2=new unsigned char[1536*1536];
        qDebug()<<"disimage:"<<dispImg[0];
//        for(int i=0;i<1536*1536;++i)
//        {
//            dispImg2[i] = 255-dispImg[i];
//        }

        smooth = new unsigned short[1536*1536];

        for(int i=0;i<1536;i++)
        {
            for(int j=0;j<1536;j++)
            {
                if(dispImg2[i*1536+j]>=220)
                {
                    smooth[i*1536+j]=dispImg2[i*1536+j]*65535.0/255.0;
                }
                if(dispImg2[i*1536+j]<=160)
                {
                    smooth[i*1536+j]=160*65535.0/255.0;
                }
                if(dispImg2[i*1536+j]<220)
                {
                    smooth[i*1536+j]=220*65535.0/255.0;
                }
            }
        }

        QString filename2="D:\\output";
        std::string fileName3 = filename2.toStdString() + "\\Proj_" + std::to_string(iProj+1) + ".raw";
        FILE *fp;
        fopen_s(&fp,fileName3.c_str(),"wb+");
        fwrite(smooth,sizeof(unsigned short),1536*1536,fp);
        fclose(fp);
        qDebug()<<"write finished";

    }

    qDebug()<<"Image folder----";
}

void MainWindow::on_LoadRaw_clicked()
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
    Scene->addItem(item);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->fitInView(item);
}

void MainWindow::on_Inverting_clicked()
{

    qDebug()<<"disimage1:"<<dispImg2[0];

    dispImg2=new unsigned char[1536*1536];
    qDebug()<<"disimage:"<<dispImg[0];
    for(int i=0;i<1536*1536;++i)
    {
        dispImg2[i] = 255-dispImg[i];
    }

//    cv::Mat img;
//    cv::Mat imgbuf = cv::Mat(1536,1536,CV_8UC1,dispImg2);
//    imgbuf.convertTo(img,-1,1,0);

//    imgOut1=new uchar [1536*1536];
//    for(int i=0;i<1536*1536;i++)
//    {
//        imgOut1[i]=img.data[i];
//    }

    q_image2 = QImage(dispImg2,1536,1536,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image2));
//    scene= new QGraphicsScene(this);
    Scene->addItem(item);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->fitInView(item);

//    QString path="D:\\couchtop\\Raw_invert.raw";
//    FILE *fp;
//    fopen_s(&fp,path.toStdString().c_str(),"wb+");
//    fwrite(Invert,sizeof(unsigned short),1536*1536,fp);
//    fclose(fp);
//    qDebug()<<"write finished";
}

void MainWindow::on_PixCal_clicked()
{
    QRect area(294, 838, 1130, 1);
    image = QImage(dispImg2,1536,1536,QImage::Format_Grayscale8).copy(area);
    row= image.width();
    col= image.height();
    intensity= new unsigned char[row*col];
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
         intensity[i*row+j] = image.pixel(QPoint(j,i));
         qDebug()<<intensity[i*row+j];
        }

    }

    qDebug()<<"pixel value---"<<intensity[50]<<row<<col;
}

void MainWindow::on_Rowpixel_clicked()
{
    QRect area(294, 838, 1130, 1);
    q_image2 = QImage(imgOut1,1536,1536,QImage::Format_Grayscale8).copy(area);
    row= q_image2.width();
    RowPix= new unsigned char[row];

    for(int i=0;i<row;i++)
    {
        RowPix[i] = image.pixel(QPoint(i,0));
        qDebug()<<RowPix[i];
    }


    qDebug()<<"pixel value---"<<RowPix[50]<<row;
}

void MainWindow::on_Smothening_clicked()
{

    smooth = new unsigned short[1536*1536];

    for(int i=0;i<1536;i++)
    {
        for(int j=0;j<1536;j++)
        {
            if(dispImg2[i*1536+j]>=220)
            {
                smooth[i*1536+j]=dispImg2[i*1536+j]*65535.0/255.0;
            }
            if(dispImg2[i*1536+j]<=160)
            {
                smooth[i*1536+j]=160*65535.0/255.0;
            }
            if(dispImg2[i*1536+j]<220)
            {
                smooth[i*1536+j]=220*65535.0/255.0;
            }
        }
    }
    QString path="D:\\couchtop\\Proj_0.raw";
    FILE *fp;
    fopen_s(&fp,path.toStdString().c_str(),"wb+");
    fwrite(smooth,sizeof(unsigned short),1536*1536,fp);
    fclose(fp);
    qDebug()<<"write finished";
}


void MainWindow::on_Smooth_disp_clicked()
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
    Scene->addItem(item);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->fitInView(item);
}

void MainWindow::on_Load_clicked()
{
    QString filename = QFileDialog::getExistingDirectory(this,"Open Test Image","D:/couchtop/*.raw");
    std::string fileNameCPP;

    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }

//    QString filename2="D:\\half out";
//       FILE * Img;
//       Img= fopen(filename.toStdString().c_str(),"rb");

//       unsigned short* Image=new unsigned short[w*h];
//       fread(Image,1,w*h*sizeof(unsigned short),Img);

//       for(int i=0;i<1536;i++)
//       {
//           for(int k=730;k<1536;k++)
//           {
//               Image[i * 1536 + k]=65535;
//           }
//       }


//           std: tring fileName3 = filename2.toStdString() + "\\projD2_" + std::to_string(20) + ".raw";
//           FILE *fp;
//           fopen_s(&fp,fileName3.c_str(),"wb+");
//           fwrite(Image,sizeof(unsigned short),1536*1536,fp);
//           fclose(fp);

           for(int iProj=0;iProj <748; iProj++)
           {
               fileNameCPP = filename.toStdString() + "\\Proj_" + std::to_string(iProj+1) + ".raw";
               FILE * Img;
               fopen_s(&Img, fileNameCPP.c_str(), "rb+");  // Open projection file to read.
               qDebug()<<"file"<<filename;
               width=1536;
               height=1536;

               dispImg= new unsigned char[width*height];
               radbuf = new unsigned short[width*height];

               img = new unsigned short[1536*1536];
//                fread(Image,1,w*h*sizeof(unsigned short),Img);
               fread(img,sizeof(unsigned short),width*height,Img);
               fclose(Img);

//               for(int i=0;i<width*height;++i)
//               {
//                   dispImg[i] = img[i]*255.0/65535.0;
//               }

//               dispImg2=new unsigned char[1536*1536];
//               qDebug()<<"disimage:"<<dispImg[0];
//               for(int i=0;i<1536*1536;++i)
//               {
//                   dispImg2[i] = 255-dispImg[i];
//               }

               smooth = new unsigned short[1536*1536];

//               for(int i=0;i<1536;i++)
//               {
//                   for(int j=0;j<1536;j++)
//                   {
//                       if(dispImg2[i*1536+j]>=220)
//                       {
//                           smooth[i*1536+j]=dispImg2[i*1536+j]*65535.0/255.0;
//                       }
//                       if(dispImg2[i*1536+j]<=160)
//                       {
//                           smooth[i*1536+j]=160*65535.0/255.0;
//                       }
//                       if(dispImg2[i*1536+j]<220)
//                       {
//                           smooth[i*1536+j]=220*65535.0/255.0;
//                       }
//                   }
//               }

               for(int i=0;i<1536;i++)
               {
                   for(int k=0;k<200;k++)
                   {
                       img[i * 1536 + k]=65535;
                   }
               }

               QString filename2="D:\\output";
               std::string fileName3 = filename2.toStdString() + "\\ProjD1_" + std::to_string(iProj+1) + ".raw";
               FILE *fp;
               fopen_s(&fp,fileName3.c_str(),"wb+");
               fwrite(img,sizeof(unsigned short),1536*1536,fp);
               fclose(fp);
               qDebug()<<"write finished";

           }

}

void MainWindow::on_Dicom_raw_clicked()
{

}
