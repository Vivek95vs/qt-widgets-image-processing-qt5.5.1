#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qcustomplot.h"
#include <QVector>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ptr = new unsigned short[3072*3072];
    ImageF = new unsigned short[3072*3072];
    ImagePix = new unsigned short[3072*3072];

    plotGraphF();

//    FixedI = new QCustomPlot(this);
//    MoveI  = new QCustomPlot(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



//FixedImageType::Pointer MainWindow::ReadFixedImage()
/*void*/ unsigned short *MainWindow::ReadFixedImage()
{
     // Read Fixed Image Using ITK
    qDebug()<<"Entered Into ReadFixedImage() function";
    double sizeF[2];
    typedef unsigned short InputPixelType; // input pixel

    typedef itk::Image< InputPixelType, 2 > FixedImageType; // Fixed Image
    FixedImageType::Pointer  FixedImage = FixedImageType::New();

    typedef itk::ImageFileReader< FixedImageType > ReaderType;
    ReaderType::Pointer Fixedreader = ReaderType::New();

    typedef itk::GDCMImageIO ImageIOType;
    ImageIOType::Pointer gdcmImageIO = ImageIOType::New();

    Fixedreader->SetImageIO(gdcmImageIO);
    Fixedreader->SetFileName("D://Test//fgc_1.dcm");

//    unsigned short *ptr = new unsigned short[3072*3072];
    qDebug()<<"Size--- ";
    try
    {
        qDebug()<<"Size---123ad ";
        Fixedreader->Update();
        qDebug()<<"Size---12323 ";
    }
    catch(std::exception &e)
    {
        std::cout<<"Exception found in Fixedreader for Histogram calculation"<<&e;
        return 0;
    }
    qDebug()<<"Size---123 ";
    FixedImage = Fixedreader->GetOutput();

    qDebug()<<"Size "<<FixedImage->GetBufferedRegion().GetSize()[0];

    try
    {
        FixedImage->Update();
    }
    catch(itk::ExceptionObject &err)
    {
        qDebug()<<"Exception found in FixedImage smart pointer update"<<&err;
        return 0;
    }

    qDebug()<<"Entered Into ReadFixedImage() function-----";


    ptr = FixedImage->GetBufferPointer();  // Return FixedImage (unsigned short -> 16 bits)


//    for(int i = 0; i < 3072*3072; i++)
//    {
//        //qDebug()<<"ioi"<<i;
////        ImageF
//        if(/*ptr[3072*3072-1]*//* != 0 && ptr[i] > 15000*/i ==3072*3072-1 )
//        {
//            qDebug()<<"Not Zero"<<i<<ptr[i];
//        }
//    }

    for(int i = 0; i < 3072*3072; i++)
    {
        if(ptr[i] != /*NULL*/ 612 && ptr[i] != NULL)
        {
          //  qDebug()<<"ptr pointer has NULL value"<<ptr[i];
        }
    }

//    for(int i = 0; i < 3072*3072; i++)
//    {
//      if(FixedImage->GetBufferPointer()[i] == NULL)
//      {
//          qDebug()<<"Data NULL"<<FixedImage->GetBufferPointer()[i];
//      }
    qDebug()<<"Entered Into ReadFixedImage() function-----3434";
//    }
    return ptr;

}

//void MainWindow::ReadMovingImage()
MovingImageType::Pointer MainWindow::ReadMovingImage()
{
     // Read Moving Image Using ITK
    qDebug()<<"Entered Into ReadMovingImage() function";
    double size[2];
    /*MovingImageType::Pointer*/ MovingImage = MovingImageType::New();

    typedef itk::ImageFileReader<MovingImageType>ImageFileReaderType;
    ImageFileReaderType::Pointer movereader = ImageFileReaderType::New();

    typedef itk::GDCMImageIO ImageIoType;
    ImageIoType::Pointer gdcmmoveImage = ImageIoType::New();

    movereader->SetImageIO(gdcmmoveImage);

    movereader->SetFileName("D:/1008/DICOM/AP_LAT/Image_0.dcm");

    try
    {
        movereader->Update();
    }
    catch(itk::ExceptionObject &err)
    {
        qDebug()<<"Error found in movereader smart pointer update"<<&err;
        return 0;
    }

    MovingImage = movereader->GetOutput();

    try
    {
        MovingImage -> Update();
    }
    catch(itk::ExceptionObject &err)
    {
        qDebug()<<"Error found in movingImage smart pointer update"<<err.GetDescription();
    }

    size[0] = MovingImage->GetLargestPossibleRegion().GetSize()[0];
    size[1] = MovingImage->GetLargestPossibleRegion().GetSize()[1];
    for(int i = 0; i < size[0]*size[1]; i++)
    {
        if(MovingImage->GetBufferPointer()[i] != 0)
        {
            qDebug()<<"Get Non-Zero Value"<<MovingImage->GetBufferPointer()[i]<<"Index"<<i;
        }

    }

    return MovingImage;
}

QVector <double> MainWindow::HistogramFixed()
{
    // Calcualte Histogram for Fixed Image
    qDebug()<<"Entered Into HisogramFixed() function";
   /* unsigned short *ImageF = new unsigned short[3072*3072];
    ImageF = ReadFixedImage();*/
//    qApp->processEvents();

//     unsigned short *ImageF;

     ImageF = ReadFixedImage();

     QVector <double>PixelCountF;
     int count=0;


         for(int j=0;j< 3072*3072;j++)
         {

          ImagePix[j]= ImageF[j];

          qDebug()<<ImagePix[j]<<ImageF[j];

         }
     qDebug()<<"Readfixed over"<<count;
//     for(int i = 0; i < 3072*3072; i++)
//     {
//         if(ImageF[i] == NULL)
//         {
//             qDebug()<<"ImageF is NULL"<<ImageF[i];
//         }
//     }


//     try
//     {

//         if(ptr >= 0)
//         {
//             qDebug()<<"PTR Data become null";
//             return PixelCountF;
//         }

//    for(int i = 0; i < 3072*3072; i++)
//    {
////        qDebug()<<"ioi"<<i;
////        ImageF
//        if(ptr[i] != 0)
//        {
//            qDebug()<<"Not Zero"<<ptr[i];
//        }
//    }

    //ImageF->GetBufferPointer();

    /*[65535]*/;
//    QVector <int>x;

//    for(int j=0;j<65535;j++)
//    {
//        PixelCountF.push_back(0);
//        x.push_back(j);
//    }

////    for(int j = 0; j < 65535; j++)
////    {
////        x[j] = j;
////    }
//    qDebug()<<"value"<<x;
//    int count = 0;
//    for(int i =0; i < 65535; ++i)
//    {
//        for(int j = 0; j < 3072*3072; j++)
//           {


////        PixelCountF[ImageF->GetBufferPointer()[i]] = PixelCountF[ImageF->GetBufferPointer()[i]]+1;
//        if(ImageF[i] == ImageF[j])
//        {
//            count++;
//        }

//        PixelCountF.push_back(count);
////        PixelCountF.replace(ptr[i],PixelCountF[ptr[i]]+1);
////        if(ptr[i]!=0)
////            qDebug()<<"Fjdfjdf"<<ptr[i]<<i;
////        PixelCountF[ImageF[i]] = PixelCountF[ImageF[i]]+1;
//       // PixelCountF[ImageF->GetBufferPointer()[i]]=PixelCountF[ImageF->GetBufferPointer()[i]]+1;

//          }

//    }

    qDebug()<<"pixelcount"<<PixelCountF;

//    for(int i = 0; i < 65535; i++)
//    {
//        if(PixelCountF[i] == NULL)
//        {
//            qDebug()<<"Pixel count F is NULL";
//        }
//        else
//        {
//            qDebug()<<"Pixel count in not NULL";
//        }
//    }


//    for(int k = 0; k < 65535; k++)
//    {
//        if(k==52685)
//            qDebug()<<"Fjdfjdf"<<k<<PixelCountF.at(k);
//        if(PixelCountF[k] != 0)
//        {
//            qDebug()<<"Get Non zero PixelCoutnF"<<PixelCountF[k];
//        }
//    }
    return PixelCountF;
}

QVector<double> MainWindow::HistogramMove()
{
    // Calculate Histogram  for Moving Image
    qDebug()<<"Entered Into HistogramMove() function";

   // unsigned short *ImageM = new unsigned short[3072*3072];

    MovingImageType::Pointer ImageM = MovingImageType::New();

    ImageM = ReadMovingImage();
    for(int i = 0; i < 3072*3072; i++)
    {
        if(ImageM->GetBufferPointer()[i] != 0)
        {
            qDebug()<<"Get Non Zero ImageM"<<ImageM->GetBufferPointer()[i];
        }
    }

    QVector<double> PixelCountM/*[65535]*/;
    QVector<int> x/*[65535]*/;

    for(int i = 0; i < 65535; i++)
    {
        PixelCountM[i] = 0;
        x[i] = 0;
    }

    for(int j = 0; j < 65535; j++)
    {
        x[j] = 0;
    }

    for(int j = 0; j < 3072*3072; j++)
    {
        PixelCountM[ImageM->GetBufferPointer()[j]] = PixelCountM[ImageM->GetBufferPointer()[j]]+1;
    }

    for(int k = 0; k < 65535; k++)
    {
        if(PixelCountM[k] != 0)
        {
            qDebug()<<"Non zero PixelCountM"<<PixelCountM[k];
        }
    }

    return PixelCountM;

}

void MainWindow::plotGraphF()
{
    // Plot Graphs of Histogram for Fixed Image
    qDebug()<<"Entered into plotGraphF() fucntion";
    QVector<double>x/*[65535]*/;
//    for(int j = 0; j < 65535; j++)
//    {
//        x[j] = 0;
//    }
    for(int i = 0; i < 65535; i ++)
    {
        x.push_back(i);
    }

    QVector<double> y/*(65536)*/;

//    for(int j = 0; j < 65535; j++)
//    {
//        y[j] = 0;
//    }

      qDebug()<<"Entered into plotGraphF() fucntion";

    y = HistogramFixed();
    qDebug()<<"Histofixed over";

    for(int i = 0; i < 65535; i++)
    {
        if(y[i] == NULL)
        {
            qDebug()<<"Y become NULL (check HistogramFixed() function and PlotGraph() function"<<y[i];
        }

    }


    ui->FixedI ->addGraph();

//    ui->FixedI->addGraph(0)->setData();
    //ui->FixedI->addGraph(0)->setData(x,y);
//    ui->FixedI ->graph(0)->setData(x,y);
    ui->FixedI->graph(0)->setData(x,y);
    ui->FixedI ->xAxis->setLabel("Pixel Value");
    ui->FixedI ->yAxis->setLabel("Frequency");
    ui->FixedI ->xAxis->setRange(0, 65535);
    ui->FixedI ->yAxis->setRange(0, 65535); //
    ui->FixedI ->replot();
    ui->FixedI ->show();

}

void MainWindow::plotGraphM()
{
    // Plot Graphs of Histogram for Moving Image
    qDebug()<<"Entered into plotGraphM() fucntion";

    QVector<double>x;
    for(int j = 0; j < 65535; j++)
    {
        x[j] = 0;
    }
    for(int i = 0; i < 65535; i ++)
    {
        x[i] = i;
    }

    QVector<double > y;

    for(int j = 0; j < 65535; j++)
    {
        y[j] = 0;
    }

    y = HistogramMove();


    ui->MoveI ->addGraph();
    ui->MoveI ->graph(0)->setData(x,y);
    ui->MoveI ->xAxis->setLabel("Pixel Value");
    ui->MoveI ->yAxis->setLabel("Frequency");
    ui->MoveI ->xAxis->setRange(0, 65535);
    ui->MoveI ->yAxis->setRange(0, 65535); //
    ui->MoveI ->replot();
    ui->MoveI ->show();
}
