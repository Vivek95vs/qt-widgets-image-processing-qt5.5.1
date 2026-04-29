#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "itkImageFileReader.h"
#include "itkGDCMImageIO.h"
#include "itkMetaDataObject.h"
#include "itkMetaDataDictionary.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "QString"
#include "QFileDialog"
#include "QFile"

#include "qsqlrecord.h"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlResult"
#include "QtSql/qsqlresult.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enhancer = new ImageEnhancementNew();

    QString dbName = "MLCShaper";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};Server=(local);Database="+dbName+";Uid=sa;Pwd=panacea");

    if(db.open())
    {
        QSqlQuery* Query = new QSqlQuery();
//        Query->setNumericalPrecisionPolicy(QSql::LowPrecisionDouble);
        Query->prepare("SELECT Alpha FROM ALPHA");
        Query->exec();

        while(Query->next())
        {
            for(int i=0;i<Query->record().count();i++)
            {
//                doulist.append(Query->value(i).toDouble());
            //                        Helplist.append(Query->value(i).toString());
                AlphaList.append(Query->value(i).toDouble());
//                qDebug()<<"value"<<AlphaList;
            }
        }

    }
    db.close();

    for(int j=0;j<AlphaList.length();j++)
    {
         QString AlphaVal1 = QString::number(AlphaList[j]);
         AlphaVal.append(AlphaVal1);
//         qDebug()<<"value123"<<AlphaVal1;
    }

    ui->combo1->addItems(AlphaVal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_LoadDicom_Image_clicked()
{
    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;
    Reader::Pointer reader=Reader::New();
    Img::Pointer image;
    QString fileName = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.dcm",QDir::currentPath());
    reader->SetFileName(fileName.toStdString().c_str());
    typedef itk::GDCMImageIO ImageType;
    ImageType::Pointer gdcmImage=ImageType::New();
    reader->SetImageIO(gdcmImage);
    try
    {
        reader->Update();
    }
    catch (itk::ExceptionObject & e)
    {
        std::cerr << "exception in file reader " << std::endl;
        std::cerr << e << std::endl;
        return;
    }
    image = reader->GetOutput();

    itk::MetaDataDictionary dict;
    dict = reader->GetMetaDataDictionary();

    std::string Rows1;
    itk::ExposeMetaData(dict,"0028|0010",Rows1);

    std::string Cols1;
    itk::ExposeMetaData(dict,"0028|0011",Cols1);


    QString Rows=Rows1.c_str();
    QString Cols=Cols1.c_str();
    qDebug()<<Rows;
    qDebug()<<Cols;

    int height = Rows.toInt();
    int width = Cols.toInt();
    qDebug()<<"Hi"<<height;

    const unsigned short *pixelBuffer = image->GetBufferPointer();

    dispImg= new unsigned char[width*height];

    qDebug()<<pixelBuffer[0];
    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = pixelBuffer[i]*255/65535;
    }
    qDebug()<<dispImg[0];

    q_image = QImage(dispImg,width,height,QImage::Format_Grayscale8);
//    q_image=q_image.scaled(3072,3072);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));

    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item/*,Qt::KeepAspectRatio*/);
//    scene->setSceneRect(0,0,width,height);
}

void MainWindow::on_PB_MedianFilter_clicked()
{
    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg);

    cv::medianBlur(imgbuf,img,5);

    uchar* imgOut=new uchar [height*width];
    for(int i=0;i<height*width;i++)
    {
        imgOut[i]=img.data[i];
    }
    QImage q_image1 = QImage(imgOut,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image1));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);

}
void MainWindow::on_PB_Invert_Filter_clicked()
{
    unsigned char* dispImg2=new unsigned char[height*width];
    qDebug()<<"disimage:"<<dispImg[0];
    for(int i=0;i<width*height;++i)
    {
        dispImg2[i] = 255-dispImg[i];
    }
    qDebug()<<"disimage1:"<<dispImg2[0];
    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg2);
    imgbuf.convertTo(img,-1,1,0);

    uchar* imgOut1=new uchar [height*width];
    for(int i=0;i<height*width;i++)
    {
        imgOut1[i]=img.data[i];
    }

    QImage q_image2 = QImage(imgOut1,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image2));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
}

void MainWindow::on_PB_Reset_clicked()
{
    cv::Mat img;
    img= cv::Mat(height,width,CV_8UC1,dispImg);
    uchar* imgOut2=new uchar [height*width];
    for(int i=0;i<height*width;i++)
    {
        imgOut2[i]=img.data[i];
    }
    QImage q_image3 = QImage(imgOut2,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image3));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
}

void MainWindow::on_Slider_Bright_valueChanged(int value)
{
    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg);

    imgbuf.convertTo(img,-1,1,value);
    uchar* imgOut3=new uchar [height*width];
    for(int i=0;i<height*width;i++)
    {
        imgOut3[i]=img.data[i];
    }
//    beta =ui->Slider_Contrast->value();
//    alpha=(value);
    QImage q_image4 = QImage(imgOut3,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image4));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    ui->Slider_Bright->setToolTip(QString::number(value));
    ui->Bright->setText(QString::number(value));
}

void MainWindow::on_Slider_Contrast_valueChanged(int value)
{
    alpha=ui->Slider_Contrast->value();
    beta=value;
    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg);
    imgbuf.convertTo(img,-1,alpha/100*3.0,beta);

    uchar* imgOut4=new uchar [height*width];
    for(int i=0;i<height*width;i++)
    {
        imgOut4[i]=img.data[i];
    }
    QImage q_image5 = QImage(imgOut4,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image5));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    ui->Slider_Contrast->setToolTip(QString::number(value));
    ui->Contrast->setText(QString::number(value));
}

void MainWindow::on_Slider_WC_valueChanged(int value)
{
    double WCvalue,WWValue;
    qDebug()<<"value wc" <<value<<ui->Slider_WC->value() ;
    WCvalue = ((value*2000)/100.0f)-1000;
    qDebug()<<"WC_val" <<WCvalue;
    WWValue = ((ui->Slider_WC->value()*2000)/100.0f);
    qDebug()<<"WW_val" <<WWValue;
    cv::Mat img;
    img= cv::Mat(height,width,CV_8UC1,dispImg);

    lowerThreshold = WCvalue - WWValue / 2.0f > -1000 ? WCvalue - WWValue / 2.0f : -1000;
    upperThreshold = (WWValue/2.0f + WCvalue);
    qDebug()<<"WW_lowerThreshold" <<lowerThreshold;
    qDebug()<<"WW_upperThreshold" <<upperThreshold;

    uchar* imgOut5=new uchar [height*width];
    double imgPixelValue;
    for(int i=0;i<height*width;i++)
    {
        imgPixelValue=(((img.data[i]*2000)/255.0f)-1000);
        if(imgPixelValue <=lowerThreshold)
        {
            imgOut5[i]=0;
        }
        else if(imgPixelValue >=upperThreshold)
        {
            imgOut5[i]=255;
        }
        else
        {
            imgOut5[i]=img.data[i];
        }
    }
    QImage q_image6 = QImage(imgOut5,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image6));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    ui->Slider_WC->setToolTip(QString::number(value));
    ui->WC->setText(QString::number(value));
}

void MainWindow::on_Slider_WW_valueChanged(int value)
{    double WCvalue,WWValue;
     qDebug()<<"value wc" <<value<<ui->Slider_WC->value() ;
     WCvalue = ((value*2000)/100.0f)-1000;;
     qDebug()<<"WC_val" <<WCvalue;
     WWValue = ((ui->Slider_WC->value()*2000)/100.0f);
     qDebug()<<"WW_val" <<WWValue;
     cv::Mat img;
     img = cv::Mat(height,width,CV_8UC1,dispImg);
     lowerThreshold = WCvalue - WWValue / 2.0f > -1000 ? WCvalue - WWValue / 2.0f : -1000;
     upperThreshold = (WWValue/2.0f + WCvalue);
     qDebug()<<"WW_lowerThreshold" <<lowerThreshold;
     qDebug()<<"WW_upperThreshold" <<upperThreshold;



     uchar* imgOut6=new uchar [height*width];
     double imgPixelValue;
     for(int i=0;i<height*width;i++)
     {
         imgPixelValue=(((img.data[i]*2000)/255.0f)-1000);
         if(imgPixelValue <=lowerThreshold)
         {
             imgOut6[i]=0;
         }
         else if(imgPixelValue >=upperThreshold)
         {
             imgOut6[i]=255;
         }
         else
         {
             imgOut6[i]=img.data[i];
         }
     }
     QImage q_image7 = QImage(imgOut6,width,height,QImage::Format_Grayscale8);
     item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image7));
     scene= new QGraphicsScene(this);
     scene->addItem(item);
 //    view = new QGraphicsView(scene);
     ui->graphicsView->setScene(scene);
     ui->graphicsView->fitInView(item);
     ui->Slider_WW->setToolTip(QString::number(value));
     ui->WW->setText(QString::number(value));
}

void MainWindow::on_Load_Raw_clicked()
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


//    width = ImgWidth;
//    height = ImgHeight;

    dispImg= new unsigned char[width*height];
    radbuf = new unsigned short[1536*1536];

    fread(radbuf,sizeof(unsigned short),1536*1536,Img);

    qDebug()<<"Image----";


    img = new unsigned short[1536*1536];
    enhancer->StartImageEnhancement(radbuf,img,width,height);

    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = img/*image->GetBufferPointer()*/[i]*255.0/65535.0;
    }
    qDebug()<<"Image----"<<img[100];

    myImage = QImage(dispImg,1536,1536,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
}

