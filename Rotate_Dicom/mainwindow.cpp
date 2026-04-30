#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "itkGradientMagnitudeImageFilter.h"
#include "itkMeanImageFilter.h"
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

void MainWindow::on_PB_LoadImage_clicked()
{


    QString fileName = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.dcm",QDir::currentPath());
    reader->SetFileName(fileName.toStdString().c_str());
    reader->SetImageIO(gdcmImage);
    reader->Update();
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

    height = Rows.toInt();
    width = Cols.toInt();
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
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));

    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item/*,Qt::KeepAspectRatio*/);
//    scene->setSceneRect(0,0,width,height);
}

void MainWindow::on_PB_Rotate_clicked()
{

    typedef itk::Image<out_img,2>outImg1;

    typedef itk::GradientMagnitudeImageFilter<Img,outImg1>FilterType;
    outImg1::Pointer out=outImg1::New();
    FilterType::Pointer filter=FilterType::New();

    filter->SetInput(reader->GetOutput());
    filter->Update();


    out=filter->GetOutput();

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

    height = Rows.toInt();
    width = Cols.toInt();
    qDebug()<<"Hi"<<height;

    const unsigned short *pixelBuffer = out->GetBufferPointer();

    dispImg= new unsigned char[width*height];

    qDebug()<<"pixelbuffer-----"<<pixelBuffer[21];
    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = pixelBuffer[i]*255.0/65535.0;
//        if(dispImg[i]!=0)
//            qDebug()<<dispImg[i];
    }
    qDebug()<<dispImg[21];

    QImage q_image1 = QImage(dispImg,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image1));

    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
//    scene->setSceneRect(0,0,width,height);

}

void MainWindow::on_PB_MeanFilter_clicked()
{
    typedef itk::Image<out_img,2>outImg1;
    typedef itk::MeanImageFilter<Img,outImg1>FilterType;
    outImg1::Pointer out=outImg1::New();
    FilterType::Pointer filter=FilterType::New();

    Img::SizeType indexRadius;
    indexRadius[0]=1;
    indexRadius[1]=1;

    filter->SetRadius(indexRadius);

    filter->SetInput(reader->GetOutput());
    filter->Update();

    out=filter->GetOutput();

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

    height = Rows.toInt();
    width = Cols.toInt();
    qDebug()<<"Hi"<<height;

    const unsigned short *pixelBuffer = out->GetBufferPointer();

    dispImg= new unsigned char[width*height];

    qDebug()<<"pixelbuffer-----"<<pixelBuffer[21];
    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = pixelBuffer[i]*255/65535.0;
    }
    qDebug()<<dispImg[21];

    QImage q_image2 = QImage(dispImg,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image2));

    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
//    scene->setSceneRect(0,0,width,height);
}

void MainWindow::on_PB_Transform_clicked()
{
    typedef itk::Image<out_img,2>outImg1;

    typedef itk::ResampleImageFilter<Img,outImg1>FilterType;
    outImg1::Pointer out=outImg1::New();
    FilterType::Pointer filter=FilterType::New();

    typedef itk::AffineTransform<double,2>TransformType;
    TransformType::Pointer transform =TransformType::New();
    filter->SetTransform(transform);

    typedef itk::NearestNeighborInterpolateImageFunction<Img,double>InterpolaratorType;
    InterpolaratorType::Pointer interpolar =InterpolaratorType::New();
    filter->SetInterpolator(interpolar);

    reader->Update();
    const Img * image = reader->GetOutput();

    const Img::SpacingType & spacing=image->GetSpacing();
    const Img::PointType & origin=image->GetOrigin();
    Img::SizeType size=image->GetLargestPossibleRegion().GetSize();

    filter->SetOutputOrigin(origin);
    filter->SetOutputSpacing(spacing);
    filter->SetOutputDirection(image->GetDirection());
    filter->SetSize(size);


    TransformType::OutputVectorType translation1;
    const double imageCenterX=origin[0]+spacing[0]*size[0]/2.0;
    const double imageCenterY=origin[1]+spacing[1]*size[1]/2.0;


    translation1[0]=-imageCenterX;
    translation1[1]=-imageCenterY;
    transform->Translate(translation1);

    const double degreesToRadians= std::atan(1.0)/45.0;
    const double angleInDegrees=270;
    const double angle= angleInDegrees * degreesToRadians;
    transform->Rotate2D(-angle,false);

    TransformType::OutputVectorType translation2;
    translation2[0]=imageCenterX;
    translation2[1]=imageCenterY;
    transform->Translate(translation2,false);
    filter->SetTransform(transform);


    filter->SetInput(reader->GetOutput());
    filter->Update();

    out=filter->GetOutput();

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

    height = Rows.toInt();
    width = Cols.toInt();
    qDebug()<<"Hi"<<height;

    const unsigned short *pixelBuffer = out->GetBufferPointer();

    dispImg= new unsigned char[width*height];

    qDebug()<<"pixelbuffer-----"<<pixelBuffer[21];
    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = pixelBuffer[i]*255.0/65535.0;
    }
    qDebug()<<dispImg[21];

    QImage q_image3 = QImage(dispImg,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image3));

    scene= new QGraphicsScene(this);
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);

}
