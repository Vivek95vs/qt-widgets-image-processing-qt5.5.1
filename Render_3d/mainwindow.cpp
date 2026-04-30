#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderingVolumeModule.h"
#include "vtkRenderingOpenGL2Module.h"
#include "vtkRenderingVolumeOpenGL2Module.h"
#include "vtkSmartPointer.h"
#include "vtkMarchingCubes.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "itkImage.h"
#include "itkImageToVTKImageFilter.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "gdcmUIDGenerator.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkMaskImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkMaskImageFilter.h"
#include "QDebug"
#include "vtk3DS.h"
#include "vtk3DSImporter.h"
#include "vtk3DWidget.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkAutoInit.h"

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkInteractionStyle)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    scene= new custumscene();
    Scene= new MyWidget();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_load_clicked()
{
    //Dicom Reading
    int ctrlSwitch = 3;

    typedef float InPixelType;
    typedef signed short OutPixelType;
    const unsigned int Dimension = 3;

    typedef itk::Image< InPixelType, Dimension > InputImageType;
    typedef itk::Image< OutPixelType, Dimension > OutputImageType;

    typedef itk::ImageSeriesReader< InputImageType >ReaderType;
    ReaderType::Pointer reader = ReaderType::New();

    typedef itk::GDCMImageIO ImageIOType;
    ImageIOType::Pointer gdcmIO = ImageIOType::New();

    typedef itk::GDCMSeriesFileNames InputNamesGeneratorType;
    InputNamesGeneratorType::Pointer inputNames =InputNamesGeneratorType::New();

    inputNames->SetInputDirectory("D:\\CBCT");
    qDebug()<<"Images are loaded";

    const ReaderType::FileNamesContainer & filenames = inputNames->GetInputFileNames();
    reader->SetImageIO( gdcmIO );
    reader->SetFileNames( filenames );
    try
    {
       reader->Update();
       qDebug()<<"Updated--1";
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files--1";
        return;
    }

    //Pre-processing step

    typedef itk::CurvatureFlowImageFilter< InputImageType, InputImageType >CurvatureFlowImageFilterType;
    CurvatureFlowImageFilterType::Pointer smoothing =CurvatureFlowImageFilterType::New();
    smoothing->SetInput( reader->GetOutput() );
    smoothing->SetNumberOfIterations( 1);
    smoothing->SetTimeStep( 0.01 );
    qDebug()<<"Pre-processing done";

//    //Region grow segmentation

    typedef itk::ConnectedThresholdImageFilter< InputImageType,InputImageType > ConnectedFilterType;
    ConnectedFilterType::Pointer connectedThreshold1 =ConnectedFilterType::New();
    const InPixelType lowerThreshold1 = -1000;
    const InPixelType upperThreshold1 = 1000;
    InputImageType::IndexType index;
    index[0] = 152;
    index[1] = 277;
    index[2] = 152;

    connectedThreshold1->SetInput(smoothing->GetOutput());
    connectedThreshold1->SetLower(lowerThreshold1);
    connectedThreshold1->SetUpper(upperThreshold1);
    connectedThreshold1->SetReplaceValue(255);
    connectedThreshold1->SetSeed( index );

    try
    {
       connectedThreshold1->Update();
       qDebug()<<"Updated--2";
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files--2";
        return;
    }

    //Masking and rescaling

    typedef itk::MaskImageFilter< InputImageType, InputImageType >MaskFilterType1;
    MaskFilterType1::Pointer maskFilter1 = MaskFilterType1::New();

    typedef itk::RescaleIntensityImageFilter< InputImageType, InputImageType> RescaleFilterType1;
    RescaleFilterType1::Pointer rescaleFilter1 = RescaleFilterType1::New();

    maskFilter1->SetInput(reader->GetOutput());
    maskFilter1->SetMaskImage(connectedThreshold1->GetOutput());
    try
    {
       maskFilter1->Update();
       qDebug()<<"Updated--3";
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files--3";
        return;
    }

//        switch (ctrlSwitch) {
//        case 1:
//            rescaleFilter1->SetInput(reader->GetOutput()); // 1 ==> Full CT input image
//            break;
//        case 2:
//            rescaleFilter1->SetInput(reader->GetOutput()); // 2 ==> Full CT input image without cover
//            break;
//        case 3:
//            rescaleFilter1->SetInput(maskFilter1->GetOutput()); // 3 ==>segmented image (opaque)
//            break;
//        case 4:
//            rescaleFilter1->SetInput(maskFilter1->GetOutput()); // 4 ==>segmented image (transparent)
//            break;
//        default:
//            break;
//        }

    rescaleFilter1->SetInput(maskFilter1->GetOutput());
    rescaleFilter1->SetOutputMinimum(0);
    rescaleFilter1->SetOutputMaximum(255);
    try
    {
        rescaleFilter1->Update();
        qDebug()<<"Updated--4";
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files--4";
        return;
    }

    //ITK to VTK conversion and 3D Visualization via QT
    typedef itk::CastImageFilter< InputImageType, OutputImageType>CastingFilterType;
    CastingFilterType::Pointer caster1 = CastingFilterType::New();

    typedef itk::ImageToVTKImageFilter<OutputImageType> ConnectorType;
    ConnectorType::Pointer connector1 = ConnectorType::New();

    vtkSmartPointer<vtkImageData> volume1 = vtkSmartPointer<vtkImageData>::New();
    vtkSmartPointer<vtkMarchingCubes> surface1 = vtkSmartPointer<vtkMarchingCubes>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    caster1->SetInput( rescaleFilter1->GetOutput() );
    try
    {
            caster1->Update();
            qDebug()<<"Updated--5";
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files--5";
        return;
    }
    connector1->SetInput(caster1->GetOutput());

    try
    {
        connector1->Update();
        qDebug()<<"Updated--6";
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files--6";
        return;
    }

    //VTK display
    volume1->DeepCopy(connector1->GetOutput());

    surface1->SetInputData(volume1);
    surface1->ComputeNormalsOn();
    surface1->SetValue(0,180);

//    surface1->GenerateValues(9, 0, 255);

    mapper1->SetInputConnection(surface1->GetOutputPort());
    mapper1->ScalarVisibilityOff();

    actor1->SetMapper(mapper1);

    actor1->GetProperty()->SetColor(1.000,0.3882,0.2784);
    actor1->RotateX(30.0);
    actor1->RotateY(-45.0);

    vtkSmartPointer<vtkRenderer>ren1=vtkSmartPointer<vtkRenderer>::New();

    ren1->AddActor(actor1);
    ren1->SetBackground(255,255,255);
//    renWin->SetSize(200,200);

    vtkWidget = new QVTKWidget(this);
    ui->verticalLayout->addWidget(vtkWidget);
    vtkWidget->GetRenderWindow()->AddRenderer(ren1);

    ren1->ResetCamera();

    vtkWidget->GetRenderWindow()->Render();
    vtkWidget->update();
    qDebug()<<"over";

}

void MainWindow::on_PB_Rect_clicked()
{
//    scene->selectedTool=1;
}

void MainWindow::on_PB_Ellipse_clicked()
{
    Scene->selectedTool=1;
}

void MainWindow::on_PB_FreeHand_clicked()
{
//    scene->selectedTool=3;
}
