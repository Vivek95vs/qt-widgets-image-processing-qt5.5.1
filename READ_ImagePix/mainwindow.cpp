#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "itkImageFileReader.h"
#include "itkGDCMImageIO.h"
#include "itkMetaDataObject.h"
#include "itkMetaDataDictionary.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    scene= new QGraphicsScene(this);
    scene->addItem(item);
    view = new QGraphicsView(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->graphicsView->setScene(scene);
//    scene->setSceneRect(0,0,width,height);
}

MainWindow::~MainWindow()
{
    delete ui;
}
