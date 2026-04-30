#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QDirIterator>
#include "itkRealToHalfHermitianForwardFFTImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkSmoothingRecursiveGaussianImageFilter.h"
#include <rtkConstantImageSource.h>
#include <rtkThreeDCircularProjectionGeometryXMLFileWriter.h>
#include <rtkRayEllipsoidIntersectionImageFilter.h>
#include <rtkCudaFDKConeBeamReconstructionFilter.h>
#include <rtkFieldOfViewImageFilter.h>



#include "rtkConfiguration.h"
#include "rtkTestConfiguration.h"
//#include "rtkTest.h"
#include "rtkSheppLoganPhantomFilter.h"
#include "rtkDrawSheppLoganFilter.h"
#include "rtkConstantImageSource.h"
#include "rtkFieldOfViewImageFilter.h"
#include "rtkIterativeFDKConeBeamReconstructionFilter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool deleteFile(const QString &filePath)
{
    QFile file(filePath);

    if (!file.exists() || !file.remove()) {
        return false;
    }

    return true;
}

void compareAndDeleteNonMatchingFiles(const QString &sourceFolder, const QString &destinationFolder)
 {
     QDir sourceDir(sourceFolder);
     QDir destinationDir(destinationFolder);

     if (!sourceDir.exists() || !destinationDir.exists()) {
         QMessageBox::critical(nullptr, "Error", "Source or destination folder does not exist.");
         return;
     }

     QStringList sourceFiles = sourceDir.entryList(QDir::Files);
     QStringList destinationFiles = destinationDir.entryList(QDir::Files);

     for (const QString &destinationFile : destinationFiles) {
         if (!sourceFiles.contains(destinationFile)) {
             QString destinationFilePath = destinationDir.filePath(destinationFile);

             if (deleteFile(destinationFilePath)) {
                 qDebug() << "Deleted:" << destinationFile;
             } else {
                 qDebug() << "Error deleting:" << destinationFile;
             }
         }
     }

     qDebug() << "Comparison and deletion complete.";
 }

void processFiles(const QString& folderPath)
{

//    QDir dir(folderPath);
    QDirIterator it(folderPath, QStringList() << "*.h", QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

       while (it.hasNext()) {
           it.next();
           QString filePath = it.filePath();

           // Create a new folder for ".h" files
           QString newFolderPath = "D:\\New Build\\HeaderFilesRtk";
           QDir().mkpath(newFolderPath);

           // Move each ".h" file to the new folder
           QString newFilePath = newFolderPath + "/" + it.fileName();

           if (QFile::rename(filePath, newFilePath)) {
               qDebug() << "Moved" << it.fileName() << "to" << newFolderPath;
           } else {
               qWarning() << "Failed to move" << it.fileName();
           }
       }
}

void MainWindow::on_pushButton_clicked()
{
//QString folderPath="D:\\New Build\\RTK-2.4.0";
//processFiles(folderPath);

// Replace these paths with your source and destination folder paths
//    QString sourceFolder = "D:\\New Build\\Compare";
//    QString destinationFolder = "D:\\New Build\\HeaderFilesRtk";
//    compareAndDeleteNonMatchingFiles(sourceFolder,destinationFolder);

    // Defines the image type
    constexpr unsigned int Dimension = 3;
      using OutputPixelType = float;
//    #ifdef USE_CUDA
//      using OutputImageType = itk::CudaImage<OutputPixelType, Dimension>;
//    #else
      using OutputImageType = itk::Image<OutputPixelType, Dimension>;
//    #endif

//    #if FAST_TESTS_NO_CHECKS
//      constexpr unsigned int NumberOfProjectionImages = 3;
//    #else
      constexpr unsigned int NumberOfProjectionImages = 180;
//    #endif

      // Constant image sources
      using ConstantImageSourceType = rtk::ConstantImageSource<OutputImageType>;
      ConstantImageSourceType::PointType   origin;
      ConstantImageSourceType::SizeType    size;
      ConstantImageSourceType::SpacingType spacing;

      ConstantImageSourceType::Pointer tomographySource = ConstantImageSourceType::New();
      origin[0] = -127.;
      origin[1] = -127.;
      origin[2] = -127.;
//    #if FAST_TESTS_NO_CHECKS
//      size[0] = 32;
//      size[1] = 32;
//      size[2] = 32;
//      spacing[0] = 8.;
//      spacing[1] = 8.;
//      spacing[2] = 8.;
//    #else
      size[0] = 128;
      size[1] = 128;
      size[2] = 128;
      spacing[0] = 2.;
      spacing[1] = 2.;
      spacing[2] = 2.;
//    #endif
      tomographySource->SetOrigin(origin);
      tomographySource->SetSpacing(spacing);
      tomographySource->SetSize(size);
      tomographySource->SetConstant(0.);

      ConstantImageSourceType::Pointer projectionsSource = ConstantImageSourceType::New();
      origin[0] = -254.;
      origin[1] = -254.;
      origin[2] = -254.;
//    #if FAST_TESTS_NO_CHECKS
//      size[0] = 32;
//      size[1] = 32;
//      size[2] = NumberOfProjectionImages;
//      spacing[0] = 32.;
//      spacing[1] = 32.;
//      spacing[2] = 32.;
//    #else
      size[0] = 128;
      size[1] = 128;
      size[2] = NumberOfProjectionImages;
      spacing[0] = 4.;
      spacing[1] = 4.;
      spacing[2] = 4.;
//    #endif
      projectionsSource->SetOrigin(origin);
      projectionsSource->SetSpacing(spacing);
      projectionsSource->SetSize(size);
      projectionsSource->SetConstant(0.);

      // Geometry object
      using GeometryType = rtk::ThreeDCircularProjectionGeometry;
      GeometryType::Pointer geometry = GeometryType::New();
      for (unsigned int noProj = 0; noProj < NumberOfProjectionImages; noProj++)
        geometry->AddProjection(600., 1200., noProj * 360. / NumberOfProjectionImages, 0, 0, 0, 0, 20, 15);

      // Shepp Logan projections filter
      using SLPType = rtk::SheppLoganPhantomFilter<OutputImageType, OutputImageType>;
      SLPType::Pointer slp = SLPType::New();
      slp->SetInput(projectionsSource->GetOutput());
      slp->SetGeometry(geometry);
      slp->SetPhantomScale(116);
      try{
          slp->Update();
      }
      catch(itk::ExceptionObject e){
          std::cerr<<"error shepp logan"<<e.GetDescription();
      }

      // Create a reference object (in this case a 3D phantom reference).
      using DSLType = rtk::DrawSheppLoganFilter<OutputImageType, OutputImageType>;
      DSLType::Pointer dsl = DSLType::New();
      dsl->SetInput(tomographySource->GetOutput());
      dsl->SetPhantomScale(116);
      try{
          dsl->Update();
       }
      catch(itk::ExceptionObject e){
          std::cerr<<"error shepp logan"<<e.GetDescription();
      }

      // FDK reconstruction filtering
//    #ifdef USE_CUDA
//      using FDKType = rtk::CudaIterativeFDKConeBeamReconstructionFilter;
//    #else
      using FDKType = rtk::IterativeFDKConeBeamReconstructionFilter<OutputImageType>;
//    #endif
      FDKType::Pointer ifdk = FDKType::New();
      ifdk->SetInput(0, tomographySource->GetOutput());
      ifdk->SetInput(1, slp->GetOutput());
      ifdk->SetGeometry(geometry);
      ifdk->SetNumberOfIterations(3);
//    #ifdef USE_CUDA
//      ifdk->SetForwardProjectionFilter(FDKType::FP_CUDARAYCAST);
//    #else
      ifdk->SetForwardProjectionFilter(FDKType::FP_JOSEPH);
      ifdk->SetEnforcePositivity(false);
      ifdk->SetLambda(0.3);
//    #endif
      try{
          ifdk->Update();
       }
      catch(itk::ExceptionObject e){
          std::cerr<<"error FDK"<<e.GetDescription();
      }
      qDebug()<<"FDK done";
      // FOV
      using FOVFilterType = rtk::FieldOfViewImageFilter<OutputImageType, OutputImageType>;
      FOVFilterType::Pointer fov = FOVFilterType::New();
      fov->SetInput(0, ifdk->GetOutput());
      fov->SetProjectionsStack(slp->GetOutput());
      fov->SetGeometry(geometry);
      try{
          fov->Update();
       }
      catch(itk::ExceptionObject e){
          std::cerr<<"error FOV"<<e.GetDescription();
      }
     qDebug()<<"FOV done";
      using WriterType = itk::ImageFileWriter<OutputImageType>;
       WriterType::Pointer writer = WriterType::New();
       writer->SetFileName("D:\\Output.png");
       writer->SetInput(fov->GetOutput());
       writer->Update();
}

