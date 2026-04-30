#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::write()
{
    DcmFileFormat fileformat;

    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/p1/*.dcm",QDir::currentPath());

    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;
    Reader::Pointer reader=Reader::New();
    Img::Pointer image;
    reader->SetFileName(filename.toStdString().c_str());

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

    fileformat.loadFile(filename.toStdString().c_str());

    DcmElement *dcmIso;
    DcmDataset *dataset = fileformat.getDataset();

    qDebug()<<"image loaded for write";

    if(dataset->findAndGetElement(DCM_IsocenterPosition,dcmIso).good())
    {
        itk::MetaDataDictionary dict2;
        dict2 = reader->GetMetaDataDictionary();
        std::string isocen;
        itk::ExposeMetaData(dict2,"300a|012c",isocen);

//    dataset->putAndInsertString(DCM_PatientName,"Test123");
//    dataset->putAndInsertString(DCM_IsocenterPosition,300,300,-18.0);
//    dataset->putAndInsertString(DCM_PatientID,"1234");
//    dataset->putAndInsertString(DCM_PatientSex,"M");
//    dataset->putAndInsertString(DCM_PatientAge,"24");

        QString Cen = isocen.c_str();QString c1;
        if(Cen==" "||Cen=="")
        {
            PointCen.setX(Size[0].rx()/2+1);
            PointCen.setY(Size[0].ry()/2+1);
            Cancer_center.append(PointCen);
        }
        else
        {
            QStringList Cen1 = Cen.split("\\");
            c1 =Cen1.at(0);
            PointCen.setX(c1.toFloat()/PixelPitch.rx());
            c1 =Cen1.at(1);
            PointCen.setY(c1.toFloat()/PixelPitch.ry());
            Cancer_center.append(PointCen);
        }
    }
    else
    {
        PointCen.setX(Size[0].rx()/2+1);
        PointCen.setY(Size[0].ry()/2+1);
        Cancer_center.append(PointCen);
    }
    std::string eBM;
    itk::MetaDataDictionary dict2;
    dict2 = reader->GetMetaDataDictionary();
    itk::ExposeMetaData(dict2,"3002|0002",eBM);
    editBeamName =QString(eBM.c_str()).trimmed();

    Contentlist2.append(TagList1);
    IsoCentres.removeAt(i);

    IsoCentres.insert(i,QPointF(PointCen.x()*PixelPitch.rx(),PointCen.y()*PixelPitch.ry()));

    height = Rows;
    width = Cols;

    slice = new unsigned char[Rows*Cols];

    image = reader->GetOutput();

    const unsigned short *pixelBuffer = image->GetBufferPointer();

    dispImg= new unsigned char[width*height];

    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = pixelBuffer[i]*255/65535; //convert 16 bit image to 8 bit image for display in qt
    }

    //    if(MirrorAddToggle!=1)
    //    {
    ////            //load buffer to qImage
    q_image = QImage(dispImg,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
    view = new QGraphicsView(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->graphicsView->setScene(scene);

//    QString filename1("D:/P1/RP_60d188b3ee70d5e9.dcm");
//    fileformat.saveFile(filename1.toStdString().c_str(),EXS_LittleEndianExplicit);

}
