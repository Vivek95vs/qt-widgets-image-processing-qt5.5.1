#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug()<<"Program Initiated"<<endl;
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

//    double size[2];
//    const unsigned int Dimension = 2;
//    //typedef unsigned short InputPixelType;
//    typedef unsigned float InputPixelType;

//    typedef itk::Image< InputPixelType, 2 > FixedImageType;
//    FixedImageType::Pointer Fixedptr = FixedImageType::New();

//    typedef itk::Image< InputPixelType, 2 > MovingImageType;
//    MovingImageType::Pointer Moveptr = MovingImageType::New();

//    typedef itk::ImageFileReader< FixedImageType > ReaderType;
//    ReaderType::Pointer Fixedreader = ReaderType::New();

//    typedef itk::ImageFileReader< MovingImageType > ReaderType;
//    ReaderType::Pointer Movereader = ReaderType::New();

//    typedef itk::GDCMImageIO ImageIOType;
//    ImageIOType::Pointer gdcmImageIO_Fixed = ImageIOType::New();

//    typedef itk::GDCMImageIO ImageIOType;
//    ImageIOType::Pointer gdcmImageIO_Move = ImageIOType::New();

//    qDebug()<<"Major Declaration completed"<<endl;

//    Fixedreader->SetImageIO(gdcmImageIO_Fixed);
//    Fixedreader->SetFileName("C:/Users/raviranjan.k/Desktop/Raw_Image/Img_2.dcm");
//    try
//    {
//        Fixedreader->Update();
//    }
//    catch (itk::ExceptionObject &e)
//    {
//        std::cerr << " Exception in File reader " << std::endl;
//        std::cerr << e << std::endl;
//    }
//  //  Fixedptr = Fixedreader->GetOutput();
//    qDebug()<<"FixedImage Input Completed"<<endl;

//    Movereader->SetImageIO(gdcmImageIO_Move);
//    Movereader->SetFileName("C:/Users/raviranjan.k/Desktop/Raw_Image/Img_2.dcm");
//    try
//    {
//        Movereader->Update();
//    }
//    catch (itk::ExceptionObject &e)
//    {
//        std::cerr << " Exception in File reader " << std::endl;
//        std::cerr << e << std::endl;
//    }
// //   Moveptr = Movereader->GetOutput();
//    qDebug()<<"Moving Image Input comleted"<<endl;

//    typedef itk::TranslationTransform< double, 2 > TransformType;
//    TransformType::Pointer transform = TransformType::New();

//    typedef itk::RegularStepGradientDescentOptimizer OptimizerType;
//    OptimizerType::Pointer optimizer = OptimizerType::New();

//    // *****
//    typedef itk::MeanSquaresImageToImageMetric< FixedImageType, MovingImageType > MetricType;
//    MetricType::Pointer metric = MetricType::New();
//    //registration->SetMetric( metric );
//    // *****

//    typedef itk::LinearInterpolateImageFunction< MovingImageType, double > InterpolatorType;
//    InterpolatorType::Pointer interpolator = InterpolatorType::New();

//    typedef itk::ImageRegistrationMethod< FixedImageType, MovingImageType > RegistrationType;
//    RegistrationType::Pointer registration = RegistrationType::New();

//    qDebug()<<"Major Declaration for registration comleted"<<endl;
//    registration->SetTransform( transform );
//    registration->SetOptimizer( optimizer );
//    registration->SetMetric( metric );
//    registration->SetInterpolator( interpolator );

//    qDebug()<<"registration is connect to the operations"<<endl;

//    registration->SetFixedImage( Fixedreader->GetOutput() );
//    registration->SetFixedImage( Movereader->GetOutput() );

//    qDebug()<<"Both Image pass through registration"<<endl;

//    registration->SetFixedImageRegion( Fixedreader->GetOutput()->GetBufferedRegion() );

//    typedef RegistrationType::ParametersType ParametersType;
//    ParametersType initialParameters( transform->GetNumberOfParameters() );

//    initialParameters[0] = 0.0; // Initial offset in mm along X
//    initialParameters[1] = 0.0; // Initial offset in mm along Y

//    registration->SetInitialTransformParameters( initialParameters );

//    optimizer->SetMaximumStepLength( 2.00 );
//    optimizer->SetMinimumStepLength( 0.01 );
//    optimizer->SetNumberOfIterations( 200 );

//    qDebug()<<"Optimization Initiated"<<endl;

//    try
//    {
//        registration->Update();
//    }
//    catch (itk::ExceptionObject &e)
//    {
//        std::cerr << " Exception in File reader " << std::endl;
//        std::cerr << e << std::endl;
//    }

//    // The result of registration process is an array of parameters that defines the spatial
//    // transformation in an uniquue way. This final result is obtained using the GetLastTransformParameters() method

//    ParametersType finalParameters = registration->GetLastTransformParameters();

//    const double TranslationAlongX = finalParameters[0];
//    const double TranslationAlongY = finalParameters[1];

//    const unsigned int numberOfIterations = optimizer->GetCurrentIteration();

//    const double bestValue = optimizer->GetValue();

//    qDebug()<<"Optimization Done"<<endl;



// //    filter->Update();

// //    try
// //    {
// //        filter->Update();
// //    }
// //    catch (itk::ExceptionObject &e)
// //    {
// //        std::cerr << " Exception in File reader " << std::endl;
// //        std::cerr << e << std::endl;
// //    }

//    qDebug()<<"First Filter Update"<<endl;

//    Fixedptr = Fixedreader->GetOutput();
//    try
//    {
//        Fixedptr->Update();
//    }
//    catch (itk::ExceptionObject &e)
//    {
//        std::cerr << " Exception in File reader " << std::endl;
//        std::cerr << e << std::endl;
//    }

//    typedef itk::ResampleImageFilter< FixedImageType, MovingImageType > ResampleFilterType;
//    ResampleFilterType::Pointer filter = ResampleFilterType::New();
//    filter->SetInput(Movereader->GetOutput() );

//    // **********************************************
//   // filter->SetTransform( registration->GetOutput()->Get() );
//    //
// //    typedef itk::AffineTransform< double, 2 > TransformType;
// //    TransformType::Pointer transform = TransformType::New();

// //    TransformType::OutputVectorType translaton;
// //    translaton[0] =0;
// //    translaton[1] =0;

// //   // transform->SetTranslation(translaton);
// //    filter->SetTransform(transform);
//    //

//    size[0] = Fixedptr->GetLargestPossibleRegion().GetSize()[0];
//    qDebug()<<"Size(X) :"<<size[0]<<endl;
//    size[1] = Fixedptr->GetLargestPossibleRegion().GetSize()[1];
//    qDebug()<<"Size(Y) "<<size[1]<<endl;

//    filter->SetSize( Fixedptr->GetLargestPossibleRegion().GetSize() );

//    const double origin[2] = {0,0};
//    filter->SetOutputOrigin( origin );

//    double spacing[2];
//    spacing[0] = Fixedptr->GetSpacing()[0];
//    spacing[1] = Fixedptr->GetSpacing()[1];
//    qDebug()<<"spacing"<<spacing[0]<<"or"<<spacing[1]<<endl;
//    filter->SetOutputSpacing( Fixedptr->GetSpacing() );

//    FixedImageType::DirectionType direction;
//    direction.SetIdentity();
//    filter->SetOutputDirection( /*Fixedptr->*/ direction );
//    qDebug()<<"Direction taken"<<endl;

//    filter->SetDefaultPixelValue( 1 );

//     qDebug()<<"gggdfgdfgdfgdfn"<<endl;

//    try
//    {
//        filter->Update();
//    }
//    catch (itk::ExceptionObject &e)
//    {
//        std::cerr << " Exception in File reader " << std::endl;
//        std::cerr << e << std::endl;
//    }
//     qDebug()<<"filter update ***************"<<endl;

// //    qDebug()<<"Next step started for showing the result"<<endl;

// //    Moveptr = filter->GetOutput();
// //    try
// //    {
// //        Moveptr->Update();
// //    }
// //    catch (itk::ExceptionObject &e)
// //    {
// //        std::cerr << " Exception in File reader " << std::endl;
// //        std::cerr << e << std::endl;
// //    }

// //     unsigned char *Image = new unsigned char[size[0]*size[1]];
// //     for(int i = 0; i < size[0]*size[1]; ++i)
// //     {
// //         Image[i] = ((Moveptr->GetBufferPointer()[i])*255.0)/65535.0;
// //     }

// //     QImage *Image1 = new QImage(Image, size[0], size[1], QImage::Format_Indexed8);
// //     QGraphicsPixmapItem *Image2= new QGraphicsPixmapItem(QPixmap::fromImage(*Image1));

// //     qDebug()<<"All operatons completed to go on UI"<<endl;

// //     scene->addItem(Image2);
// //     scene->setSceneRect(0,0,3072,3072);
// //     ui->graphicsView->setScene(scene);
// //     ui->graphicsView->fitInView(Image2);
// //     qDebug()<<"Program Exicuted Successfully"<<endl;

//      typedef unsigned short OutputPixelType;
//      typedef itk::Image< OutputPixelType, 2 > OutputImageType;
//      //typedef itk::CastImageFilter< FixedImageType, OutputImageType > CastFilterType;
//    typedef itk::CastImageFilter< FixedImageType, OutputImageType > CastFilterType;
//    CastFilterType::Pointer caster = CastFilterType::New();

//     // CastFilterType::Pointer caster = CastFilterType::New();

//      caster->SetInput(filter->GetOutput() );
//      try
//          {
//              caster->Update();
//          }
//          catch (itk::ExceptionObject &e)
//          {
//              std::cerr << " Exception in File reader " << std::endl;
//              std::cerr << e << std::endl;
//          }

//      // find difference between the fixed image and moving image
//     // using itk::SubtractImgeFIlter.

//      typedef itk::SubtractImageFilter< FixedImageType, FixedImageType, FixedImageType >DifferenceFilterType;
//      DifferenceFilterType::Pointer difference = DifferenceFilterType::New();
//      difference->SetInput1( Fixedreader->GetOutput() );
//      difference->SetInput2( filter->GetOutput() );

//      try
//          {
//              difference->Update();
//          }
//          catch (itk::ExceptionObject &e)
//          {
//              std::cerr << " Exception in File reader " << std::endl;
//              std::cerr << e << std::endl;
//          }
//        unsigned char *Image = new unsigned char[size[0]*size[1]];
//          for(int i = 0; i < size[0]*size[1]; ++i)
//          {
//              Image[i]=(difference->GetInput()->GetBufferPointer()[i]*255.0)/65535.0;
// //              Image[i] = ((difference->GetBufferPointer()[i])*255.0)/65535.0;
//          }

//          QImage *Image1 = new QImage(Image, size[0], size[1], QImage::Format_Indexed8);
//          QGraphicsPixmapItem *Image2= new QGraphicsPixmapItem(QPixmap::fromImage(*Image1));

//          qDebug()<<"All operatons completed to go on UI"<<endl;

//          scene->addItem(Image2);
//          scene->setSceneRect(0,0,3072,3072);
//          ui->graphicsView->setScene(scene);
//          ui->graphicsView->fitInView(Image2);
//          qDebug()<<"Program Exicuted Successfully"<<endl;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Result

    double size[2];
    const unsigned int Dimension = 2;
    //typedef unsigned short InputPixelType;
    typedef unsigned float InputPixelType;  // input Pixel Type

    typedef itk::Image< InputPixelType, 2 > FixedImageType;   // Fixed image type
    FixedImageType::Pointer Fixedptr = FixedImageType::New(); // fixed image type pointer

    typedef itk::Image< InputPixelType, 2 > MovingImageType;  // moving image type
    MovingImageType::Pointer Moveptr = MovingImageType::New(); // moving imge type pointer

    typedef itk::ImageFileReader< FixedImageType > ReaderType;  //reader for fixed image type
    ReaderType::Pointer Fixedreader = ReaderType::New();   // reader pointer for fixed image type

    typedef itk::ImageFileReader< MovingImageType > ReaderType; // reader for mioving image type
    ReaderType::Pointer Movereader = ReaderType::New();   // reader pointer for moving image type

    typedef itk::GDCMImageIO ImageIOType;   // fot DICOM type reader
    ImageIOType::Pointer gdcmImageIO_Fixed = ImageIOType::New(); // for DICOM type reader pointer for fixed image

    typedef itk::GDCMImageIO ImageIOType;  // for DICOM type reader
    ImageIOType::Pointer gdcmImageIO_Move = ImageIOType::New();  // for DICOM type reader pointer for moving image

    qDebug()<<"Major Declaration completed"<<endl;

    Fixedreader->SetImageIO(gdcmImageIO_Fixed);
    Fixedreader->SetFileName("C:/Users/raviranjan.k/Desktop/Raw_Image/Img_2.dcm");  // fixed image input
    try
    {
        Fixedreader->Update();  // fixed image reader update
    }
    catch (itk::ExceptionObject &e)
    {
        std::cerr << " Exception in File reader " << std::endl;
        std::cerr << e << std::endl;
    }
  //  Fixedptr = Fixedreader->GetOutput();
    qDebug()<<"FixedImage Input Completed"<<endl;

    Movereader->SetImageIO(gdcmImageIO_Move);
    //Movereader->SetFileName("C:/Users/raviranjan.k/Desktop/Raw_Image/Img_2.dcm");
    Movereader->SetFileName("C:/Users/raviranjan.k/Desktop/Raw_Image/a_1.dcm");  // moving image input

    try
    {
        Movereader->Update();  // moving image reader update
    }
    catch (itk::ExceptionObject &e)
    {
        std::cerr << " Exception in File reader " << std::endl;
        std::cerr << e << std::endl;
    }
 //   Moveptr = Movereader->GetOutput();
    qDebug()<<"Moving Image Input comleted"<<endl;

    typedef itk::TranslationTransform< double, 2 > TransformType;   // translation initialted of transform type
    TransformType::Pointer transform = TransformType::New();      // tranform type pointer

    typedef itk::RegularStepGradientDescentOptimizer OptimizerType;  // optimizer initiated
    OptimizerType::Pointer optimizer = OptimizerType::New();   // optimizer type pointer

    // *****
    typedef itk::MeanSquaresImageToImageMetric< FixedImageType, MovingImageType > MetricType;  // meansquares iamge to image metric to compaore both the image pixel by pixel analysis
    MetricType::Pointer metric = MetricType::New();  // pointer to compaire the both image pixel by pixel
    //registration->SetMetric( metric );
    // *****

    typedef itk::LinearInterpolateImageFunction< MovingImageType, double > InterpolatorType; // linear interplator initialted
    InterpolatorType::Pointer interpolator = InterpolatorType::New(); // interpolator tyep pointer

    typedef itk::ImageRegistrationMethod< FixedImageType, MovingImageType > RegistrationType; //image registration method initiated
    RegistrationType::Pointer registration = RegistrationType::New();  // image registration type pointer to start registration process

    qDebug()<<"Major Declaration for registration comleted"<<endl;
    registration->SetTransform( transform );
    registration->SetOptimizer( optimizer );
    registration->SetMetric( metric );
    registration->SetInterpolator( interpolator );

    qDebug()<<"registration is connect to the operations"<<endl;

    registration->SetFixedImage( Fixedreader->GetOutput() ); // output of fixedreader type pointer pass to the registration
    registration->SetFixedImage( Movereader->GetOutput() );  // output of movereader type pointer pass to the registration

    qDebug()<<"Both Image pass through registration"<<endl;

    registration->SetFixedImageRegion( Fixedreader->GetOutput()->GetBufferedRegion() );

    typedef RegistrationType::ParametersType ParametersType;
    ParametersType initialParameters( transform->GetNumberOfParameters() );

    initialParameters[0] = 0.0; // Initial offset in mm along X
    initialParameters[1] = 0.0; // Initial offset in mm along Y

    registration->SetInitialTransformParameters( initialParameters );

    optimizer->SetMaximumStepLength( 4.00 );  // maximum step size of optimizer
    optimizer->SetMinimumStepLength( 0.01 );  // minimum strp size of optimizer
    optimizer->SetNumberOfIterations( 200 );  // no. of optimization step total

    qDebug()<<"Optimization Initiated"<<endl;

    try
    {
        registration->Update();  // update registraiton
    }
    catch (itk::ExceptionObject &e)
    {
        std::cerr << " Exception in File reader " << std::endl;
        std::cerr << e << std::endl;
    }

    // The result of registration process is an array of parameters that defines the spatial
    // transformation in an uniquue way. This final result is obtained using the GetLastTransformParameters() method

    ParametersType finalParameters = registration->GetLastTransformParameters();

    const double TranslationAlongX = finalParameters[0];
    const double TranslationAlongY = finalParameters[1];

    const unsigned int numberOfIterations = optimizer->GetCurrentIteration();

    const double bestValue = optimizer->GetValue();

    qDebug()<<"Optimization Done"<<bestValue<<endl;


//    filter->Update();

//    try
//    {
//        filter->Update();
//    }
//    catch (itk::ExceptionObject &e)
//    {
//        std::cerr << " Exception in File reader " << std::endl;
//        std::cerr << e << std::endl;
//    }

    qDebug()<<"First Filter Update"<<endl;

    Fixedptr = Fixedreader->GetOutput();
    try
    {
        Fixedptr->Update();
    }
    catch (itk::ExceptionObject &e)
    {
        std::cerr << " Exception in File reader " << std::endl;
        std::cerr << e << std::endl;
    }

    typedef itk::ResampleImageFilter< FixedImageType, MovingImageType > ResampleFilterType; // resampleimage filter initiated
    ResampleFilterType::Pointer filter = ResampleFilterType::New();   // filter pointer of resampleiamge filter crated
    filter->SetInput(Movereader->GetOutput() );   // filter get input from mmovereader

    // **********************************************
   // filter->SetTransform( registration->GetOutput()->Get() );
    //
//    typedef itk::AffineTransform< double, 2 > TransformType;
//    TransformType::Pointer transform = TransformType::New();

//    TransformType::OutputVectorType translaton;
//    translaton[0] =0;
//    translaton[1] =0;

//   // transform->SetTranslation(translaton);
//    filter->SetTransform(transform);
    //

    size[0] = Fixedptr->GetLargestPossibleRegion().GetSize()[0];
    qDebug()<<"Size(X) :"<<size[0]<<endl;
    size[1] = Fixedptr->GetLargestPossibleRegion().GetSize()[1];
    qDebug()<<"Size(Y) "<<size[1]<<endl;

    filter->SetSize( Fixedptr->GetLargestPossibleRegion().GetSize() ); // filter get size as the image of fixedimage type

    const double origin[2] = {0,0};
    filter->SetOutputOrigin( origin );

    double spacing[2];
    spacing[0] = Fixedptr->GetSpacing()[0];
    spacing[1] = Fixedptr->GetSpacing()[1];
    qDebug()<<"spacing"<<spacing[0]<<"or"<<spacing[1]<<endl;
    filter->SetOutputSpacing( Fixedptr->GetSpacing() );

    FixedImageType::DirectionType direction;
    direction.SetIdentity();
    filter->SetOutputDirection( /*Fixedptr->*/ direction );
    qDebug()<<"Direction taken"<<endl;

    filter->SetDefaultPixelValue( 1 );

     qDebug()<<"gggdfgdfgdfgdfn"<<endl;

    try
    {
        filter->Update();
    }
    catch (itk::ExceptionObject &e)
    {
        std::cerr << " Exception in File reader " << std::endl;
        std::cerr << e << std::endl;
    }
     qDebug()<<"filter update ***************"<<endl;

//    qDebug()<<"Next step started for showing the result"<<endl;

//    Moveptr = filter->GetOutput();
//    try
//    {
//        Moveptr->Update();
//    }
//    catch (itk::ExceptionObject &e)
//    {
//        std::cerr << " Exception in File reader " << std::endl;
//        std::cerr << e << std::endl;
//    }

//     unsigned char *Image = new unsigned char[size[0]*size[1]];
//     for(int i = 0; i < size[0]*size[1]; ++i)
//     {
//         Image[i] = ((Moveptr->GetBufferPointer()[i])*255.0)/65535.0;
//     }

//     QImage *Image1 = new QImage(Image, size[0], size[1], QImage::Format_Indexed8);
//     QGraphicsPixmapItem *Image2= new QGraphicsPixmapItem(QPixmap::fromImage(*Image1));

//     qDebug()<<"All operatons completed to go on UI"<<endl;

//     scene->addItem(Image2);
//     scene->setSceneRect(0,0,3072,3072);
//     ui->graphicsView->setScene(scene);
//     ui->graphicsView->fitInView(Image2);
//     qDebug()<<"Program Exicuted Successfully"<<endl;

      typedef unsigned short OutputPixelType;
      typedef itk::Image< OutputPixelType, 2 > OutputImageType;
     OutputImageType::Pointer ptrout = OutputImageType::New();

      //typedef itk::CastImageFilter< FixedImageType, OutputImageType > CastFilterType;
     // *************************************************
     typedef itk::CastImageFilter< FixedImageType, OutputImageType > CastFilterType;
     typedef itk::CastImageFilter< MovingImageType, OutputImageType > CastFilterType;
     // **********************************************
    CastFilterType::Pointer caster = CastFilterType::New();

     // CastFilterType::Pointer caster = CastFilterType::New();

      caster->SetInput(filter->GetOutput() );
      try
          {
              caster->Update();
          }
          catch (itk::ExceptionObject &e)
          {
              std::cerr << " Exception in File reader " << std::endl;
              std::cerr << e << std::endl;
          }

      // find difference between the fixed image and moving image
     // using itk::SubtractImgeFIlter.

      typedef itk::SubtractImageFilter< FixedImageType, FixedImageType, FixedImageType >DifferenceFilterType;
      //typedef itk::SubtractImageFilter< FixedImageType, MovingImageType, OutputImageType >DifferenceFilterType;
      DifferenceFilterType::Pointer difference = DifferenceFilterType::New();
     // DifferenceFilterType::Pointer difference1 = DifferenceFilterType::New();
     // DifferenceFilterType::Pointer difference2 = DifferenceFilterType::New();

      difference->SetInput( Fixedreader->GetOutput() );
     // difference->SetInput1( Movereader->GetOutput() );
      difference->SetInput2( filter->GetOutput() );
      //difference11->SetInput( Fixedreader->GetOutput() - Movereader->GetOutput());
      //      difference1->SetInput( difference->SetInput1( Fixedreader->GetOutput()) - difference2->SetInput2( Movereader->GetOutput()));
      //difference->SetInput2( filter->GetOutput() );

      try
          {
              difference->Update();
          }
          catch (itk::ExceptionObject &e)
          {
              std::cerr << " Exception in File reader " << std::endl;
              std::cerr << e << std::endl;
          }
        unsigned char *Image = new unsigned char[size[0]*size[1]];
          for(int i = 0; i < size[0]*size[1]; ++i)
          {
              Image[i]=(difference->GetInput()->GetBufferPointer()[i]*255.0)/65535.0;
//              Image[i] = ((difference->GetBufferPointer()[i])*255.0)/65535.0;
          }

          QImage *Image1 = new QImage(Image, size[0], size[1], QImage::Format_Indexed8);
          QGraphicsPixmapItem *Image2= new QGraphicsPixmapItem(QPixmap::fromImage(*Image1));

          qDebug()<<"All operatons completed to go on UI"<<endl;

          scene->addItem(Image2);
          scene->setSceneRect(0,0,3072,3072);
          ui->graphicsView->setScene(scene);
          ui->graphicsView->fitInView(Image2);
          qDebug()<<"Program Exicuted Successfully"<<endl;
}
