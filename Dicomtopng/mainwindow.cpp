#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <QImage>
#include <QFile>
#include "QDebug"
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
#include "itkResampleImageFilter.h"
#include "itkAffineTransform.h"
#include "itkNearestNeighborInterpolateImageFunction.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DicomToPng_clicked()
{
    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;
    Reader::Pointer reader=Reader::New();
    Img::Pointer image;
    QString fileName = QFileDialog::getOpenFileName(this,"Open Test Image","D:/*.dcm",QDir::currentPath());
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
    itk::MetaDataDictionary dict;
    dict = reader->GetMetaDataDictionary();

    std::string Rows1;
    itk::ExposeMetaData(dict,"0028|0010",Rows1);

    std::string Cols1;
    itk::ExposeMetaData(dict,"0028|0011",Cols1);


    QString Rows=Rows1.c_str();
    QString Cols=Cols1.c_str();
    qDebug()<<"rows"<<Rows;
    qDebug()<<"cols"<<Cols;

    int height = Rows.toInt();
    int width = Cols.toInt();

    image = reader->GetOutput();


    const unsigned short *pixelBuffer = image->GetBufferPointer();

    dispImg= new unsigned char[width*height];
//    unsigned char* arr=new unsigned char[w*h];
    for(int i=0;i<3072*3072;i++)
    {
        arr[i]=((pixelBuffer[i]*255)/65535);
    }
//    QImage rawImage(reinterpret_cast<const uchar*>(arr), 500, 500, QImage::Format_RGB888);
    myImage = QImage(arr,3072,3072,QImage::Format_Grayscale8);

    // Save QImage as PNG
    QString outputPath = "D:\\KV test result\\Small focal spot_KV1\\DailyImages\\DICOM\\Image_2.png"; // Change this to your desired output path
    bool saved = myImage.save(outputPath, "PNG");

    if (saved) {
        qDebug() << "Image saved as PNG: " << outputPath;
    } else {
        qDebug() << "Failed to save image as PNG.";
    }

    //qDebug() << "Raw image converted and saved as PNG:" << pngFilePath;

}

void MainWindow::on_RawToPng_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short* Image=new unsigned short[3072*3072];
    fread(Image,1,3072*3072*sizeof(unsigned short),Img);
//    unsigned char* arr=new unsigned char[w*h];
    for(int i=0;i<3072*3072;i++)
    {
        arr[i]=((Image[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,3072,3072,QImage::Format_Grayscale8);

    QString outputPath = "D:\\KV test result\\Small focal spot_KV1\\DailyImages\\Raw\\proj_2.png"; // Change this to your desired output path
    bool saved = myImage.save(outputPath, "PNG");

    if (saved) {
        qDebug() << "Image saved as PNG: " << outputPath;
    } else {
        qDebug() << "Failed to save image as PNG.";
    }
}
