#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <gdcmUIDGenerator.h>
#include <itkCommand.h>
#include "itkImageFileWriter.h"
#include <itkGDCMImageIO.h>
#include "itkMetaDataObject.h"
#include <itkMetaDataDictionary.h>
#include "itkImportImageFilter.h"
#include "itkImage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    display();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/p1/*.dcm",QDir::currentPath());

    typedef unsigned short img;
    typedef unsigned short out_img;

    typedef itk::Image< img,2>Img;
    Img::Pointer image;
    typedef itk::ImageFileReader<Img>ReaderType;
    ReaderType::Pointer reader = ReaderType::New();
    typedef itk::GDCMImageIO  ImageTypeIO;
    reader->SetFileName(filename.toStdString().c_str());
    ImageTypeIO::Pointer gdcmImage = ImageTypeIO::New();

    reader->SetImageIO( gdcmImage);
    reader->Update();


    itk::MetaDataDictionary dict2;
    dict2 = reader->GetMetaDataDictionary();

    std::string Rows1;
    itk::ExposeMetaData(dict2,"0028|0010",Rows1);
    Rows3 =  std::stoi(Rows1);

    std::string Cols1;
    itk::ExposeMetaData(dict2,"0028|0011",Cols1);
    Cols = std::stoi(Cols1);

    std::string pixs;
    itk::ExposeMetaData(dict2,"0028|0030",pixs);

    QString RowS=Rows1.c_str();
    QString ColS=Cols1.c_str();
    qDebug()<<"R"<<RowS;
    qDebug()<<"c"<<ColS;

    Rows3=RowS.toInt();
    Cols=ColS.toInt();

    qDebug()<<"Row"<<Rows3;
    qDebug()<<"col"<<Cols;

    Size.clear();
    Size<<QPoint(RowS.toDouble(),ColS.toDouble());

    qDebug()<<"image loaded for write";

    image = reader->GetOutput();

    unsigned short *pixelBuffer = image->GetBufferPointer();

    dispImg= new unsigned short[Rows3*Cols];

    enhancer=new ImageEnhacement();
    enhancer->StartImageEnhancement(pixelBuffer,dispImg,Rows3,Cols);

    disp=new unsigned char[Rows3*Cols];

    for(int i=0;i<Rows3*Cols;++i)
    {
//        if(pixelBuffer[i]!=0)
//        {
//        qDebug()<<pixelBuffer[i];
//        }

//        dispImg[i] = pixelBuffer[i]*255.0/65535.0; //convert 16 bit image to 8 bit image for display in qt
//        if(dispImg[i]!=0)
//        {
//        qDebug()<<dispImg[i];
//        }
        disp[i] = (dispImg[i]*255.0/65535.0)/**100.0*/;
    }
    qDebug()<<"dispImage"<<dispImg[1200];
    qDebug()<<"disp"<<disp[1200];

    unsigned char* dispImg2=new unsigned char[Rows3*Cols];
    qDebug()<<"disimage:"<<dispImg[0];
    for(int i=0;i<Rows3*Cols;++i)
    {
        dispImg2[i] = 255-disp[i];
    }
//    qDebug()<<"disimage1:"<<dispImg2[0];
//    cv::Mat img1;
//    cv::Mat imgbuf = cv::Mat(Rows,Cols,CV_8UC1,dispImg2);
//    imgbuf.convertTo(img1,-1,1,0);

//    uchar* imgout =new uchar [Rows*Cols];
//    for(int i=0;i<Rows*Cols;i++)
//    {
//        imgout[i]=img1.data[i];
//    }

    q_image = QImage(dispImg2,Rows3,Cols,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item->boundingRect());
}
