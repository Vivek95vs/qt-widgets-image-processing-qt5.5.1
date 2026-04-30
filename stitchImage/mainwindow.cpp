#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkPasteImageFilter.h>

#include "QDebug"

using PixelType = unsigned char;
/* constexpr*/ const unsigned int Dimension = 2;

using ImageType = itk::Image<PixelType, Dimension>;


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


void MainWindow::on_pushButton_clicked()
{
//    int w=1536,h=1536;
//    QString filename1 = "D:\\2D Images\\projD1_35.raw";
//    if (filename1.isEmpty())
//       {
//           qDebug()<<"Could not open file";
//       }
//    FILE * Img1;
//    Img1= fopen(filename1.toStdString().c_str(),"rb");

//    unsigned short* Image_1=new unsigned short[w*h];
//    fread(Image_1,1,w*h*sizeof(unsigned short),Img1);
//    arr1=new unsigned char[w*h];
//    for(int i=0;i<w*h;i++)
//    {
//        arr1[i]=((Image_1[i]*255)/65535);
//    }

//    QString filename2 = "D:\\2D Images\\projD1_36.raw";
//    if (filename2.isEmpty())
//       {
//           qDebug()<<"Could not open file";
//       }
//    FILE * Img2;
//    Img2= fopen(filename2.toStdString().c_str(),"rb");

//    unsigned short* Image_2=new unsigned short[w*h];
//    fread(Image_2,1,w*h*sizeof(unsigned short),Img2);
//    arr2=new unsigned char[w*h];
//    for(int i=0;i<w*h;i++)
//    {
//        arr2[i]=((Image_2[i]*255)/65535);

//    }

////    int size1=w*h;
////    int size2=w*h;

////    int newsize=size1+size2;

////    qDebug()<<"Size"<<size1<<size2<<newsize;

//    arr3 = new unsigned char[w*h];


////    // Copy the first array into the result array
////    std::memcpy(arr3, arr1, size1);

////    // Copy the second array into the result array, starting from where the first array left off
////    std::memcpy(arr3 + size1, arr2, size2);


//    QString filename3="D:\\2D Images";
//    std::string fileName4 = filename3.toStdString() + "\\Image_" + std::to_string(1) + ".raw";
//    FILE *fp;
//    fopen_s(&fp,fileName4.c_str(),"wb+");
//    fwrite(arr3,sizeof(unsigned char),w*h,fp);
//    fclose(fp);
//    qDebug()<<"w,h 123"<<w<<h;

//    myImage=QImage(arr3,w,h,QImage::Format_Grayscale8);
//    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));

//    scene = new QGraphicsScene();
//    view = new QGraphicsView(scene);
//    ui->graphicsView->setScene(scene);
//    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
//    scene->addItem(item);



    QString fileName = "D:\\2D Images\\projD1_35.raw";

    using ReaderType = itk::ImageFileReader<ImageType>;
    ReaderType::Pointer reader1 = ReaderType::New();
    reader1->SetFileName(fileName.toStdString());
    try {
        reader1->Update();
    } catch (itk::ExceptionObject &ex) {
        std::cerr << "Exception caught during image reading:\n" << ex << std::endl;
//        return EXIT_FAILURE;
    }

    qDebug()<<"Writing image.........2";

    ReaderType::Pointer reader2 = ReaderType::New();
    reader2->SetFileName("D:\\2D Images\\projD1_36.raw");
    reader2->Update();

    ImageType::Pointer outputImage = ImageType::New();
    ImageType::RegionType region;

    region.SetSize(0, std::max(reader1->GetOutput()->GetLargestPossibleRegion().GetSize(0),
                               reader2->GetOutput()->GetLargestPossibleRegion().GetSize(0)));
    region.SetSize(1, reader1->GetOutput()->GetLargestPossibleRegion().GetSize(1) +
                      reader2->GetOutput()->GetLargestPossibleRegion().GetSize(1));

    outputImage->SetRegions(region);
    outputImage->Allocate();

    qDebug()<<"Writing image.........1";
    using PasteFilterType = itk::PasteImageFilter<ImageType, ImageType>;
    PasteFilterType::Pointer pasteFilter = PasteFilterType::New();

    pasteFilter->SetSourceImage(reader1->GetOutput());
    pasteFilter->SetDestinationImage(outputImage);
    pasteFilter->SetSourceRegion(reader1->GetOutput()->GetLargestPossibleRegion());
    pasteFilter->SetDestinationIndex({0, 0});  // Paste at the top-left corner
    pasteFilter->Update();

    pasteFilter->SetSourceImage(reader2->GetOutput());
    pasteFilter->SetDestinationImage(pasteFilter->GetOutput());
    pasteFilter->SetSourceRegion(reader2->GetOutput()->GetLargestPossibleRegion());
    pasteFilter->SetDestinationIndex({0, reader1->GetOutput()->GetLargestPossibleRegion().GetSize(1)});
    pasteFilter->Update();

    qDebug()<<"Writing image.........";

    // Write the stitched image to a file
    using WriterType = itk::ImageFileWriter<ImageType>;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName("D:\\2D Images\\output_stitched_image.raw");
    writer->SetInput(outputImage);
    writer->Update();


}
