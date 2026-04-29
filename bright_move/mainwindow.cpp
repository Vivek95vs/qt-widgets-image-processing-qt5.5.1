#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "itkImageFileReader.h"
#include "itkGDCMImageIO.h"
#include "itkMetaDataObject.h"
#include "itkMetaDataDictionary.h"
#include <QDebug>

int mouseval=0;
unsigned char *tempBuffer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mousescene = new sceneclass();
    item1 = new QGraphicsPixmapItem();


    connect(mousescene,SIGNAL(distancevalue(int)),this,SLOT(on_brightness_valueChanged(int)));
    connect(mousescene,SIGNAL(valuechanged(int)),this,SLOT(on_horizontalSlider_2_valueChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Load_Image_clicked()
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
    qDebug()<<Rows;
    qDebug()<<Cols;

    int height = Rows.toInt();
    int width = Cols.toInt();

    image = reader->GetOutput();


    const unsigned short *pixelBuffer = image->GetBufferPointer();

    dispImg= new unsigned char[width*height];

    qDebug()<<pixelBuffer[0];
    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = pixelBuffer[i]*255/65535.0;
    }
    qDebug()<<dispImg[0];

    q_image = QImage(dispImg,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));
    view = new QGraphicsView(mousescene);
    ui->graphicsView->setScene(mousescene);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
    mousescene->addItem(item);

}

void MainWindow::on_Brightness_clicked()
{
   qDebug()<<"Enter";
   ui->Brightness->setMouseTracking(mousescene->pressed);
}

void MainWindow::on_Contrast_clicked()
{
    mousescene->selectedTool=2;
}

void MainWindow::on_Window_width_clicked()
{

}

void MainWindow::on_Window_center_clicked()
{

}

void MainWindow::getbrightness()
{

}


void MainWindow::on_brightness_valueChanged(int value)
{
    double beta =static_cast<double> (value);
    double alpha=static_cast<double>(ui->brightness->value());

    EnhanceImage enhancer;
    tempBuffer = enhancer.enhanceBrightness(dispImg,3072,3072,alpha,beta);
    q_image = QImage(tempBuffer,w,h,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));
    view = new QGraphicsView(mousescene);
    ui->graphicsView->setScene(mousescene);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
    mousescene->addItem(item);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{

}
