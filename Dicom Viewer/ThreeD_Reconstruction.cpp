#include "ThreeD_Reconstruction.h"
#include <vtkDecimatePro.h>
#include "vtkPiecewiseFunction.h"

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include <vtkImageAppend.h>
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
#include <vtkDICOMImageReader.h>


ThreeD_Reconstruction::ThreeD_Reconstruction(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

ThreeD_Reconstruction::ThreeD_Reconstruction(std::vector<std::string>* filenames_v, QWidget* parent)
{
    //
    ui.setupUi(this);
    m_Filenames = vtkSmartPointer<vtkStringArray>::New();
    for(int i=0;i<filenames_v->size();i++)
    {
        m_Filenames->InsertNextValue(filenames_v->at(i));
    }
    setWindowTitle(QStringLiteral("ÈýÎ¬ÖØ½¨-ÕýÔÚ½âËã..."));
}

ThreeD_Reconstruction::~ThreeD_Reconstruction()
{

}

void ThreeD_Reconstruction::OnReconstruction()
{
    //RenderPipeline_CPU(m_Filenames);
    RenderPipeline_GPU(m_Filenames);
}

void ThreeD_Reconstruction::RenderPipeline_CPU(vtkStringArray *_FilesYouWant)
{
    m_ThreeDRec_Renderer = vtkRenderer::New();
    m_ThreeDRec_RenderWindow = vtkRenderWindow::New();
    m_ThreeDRec_RenderWindow->AddRenderer(m_ThreeDRec_Renderer);

    ui.qvtkWidget_3DRec->SetRenderWindow(m_ThreeDRec_RenderWindow);

    renderWindowInteractor = vtkRenderWindowInteractor::New();
    renderWindowInteractor->SetRenderWindow(m_ThreeDRec_RenderWindow);

    vtkDecimatePro *deci = vtkDecimatePro::New();
    deci->SetTargetReduction(0.3);

    TrackballCamera = vtkInteractorStyleTrackballCamera::New();
    renderWindowInteractor->SetInteractorStyle(TrackballCamera);

    m_MyDICOMImageReader = vtkSmartPointer<vtkMyDICOMImageReader>::New();
    m_MyDICOMImageReader->SetFileNames(_FilesYouWant);

#if _DEBUG
    std::filebuf fb;
    fb.open("vtkdicomviewer.log", std::ios::out);
    std::ostream out(&fb);
    m_MyDICOMImageReader->Print(out);
    fb.close();
#endif
    m_MyDICOMImageReader->SetFileDimensionality(3);
    m_MyDICOMImageReader->SetDataScalarType(VTK_UNSIGNED_SHORT);
    m_MyDICOMImageReader->SetDataExtent(0, 255, 0, 255, 0, 62);
    m_MyDICOMImageReader->SetDataSpacing(0.9, 0.9, 0.9);

    m_ImageCast = vtkImageCast::New();
    m_ImageCast->SetInputConnection(m_MyDICOMImageReader->GetOutputPort());

    m_ImageCast->SetOutputScalarTypeToUnsignedShort();
    m_ImageCast->ClampOverflowOn();


    m_PiecewiseFunction = vtkPiecewiseFunction::New();
    m_PiecewiseFunction->AddPoint(20, 0.0);
    m_PiecewiseFunction->AddPoint(255, 0.2);

    m_colorTransferFunction = vtkColorTransferFunction::New();
    m_colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.5, 0.0);
    m_colorTransferFunction->AddRGBPoint(60.0, 1.0, 0.0, 0.0);
    m_colorTransferFunction->AddRGBPoint(128.0, 0.2, 0.1, 0.9);
    m_colorTransferFunction->AddRGBPoint(196.0, 0.27, 0.21, 0.1);
    m_colorTransferFunction->AddRGBPoint(255.0, 0.8, 0.8, 0.8);
    //vtkPiecewiseFunction *gradientTransferFunction = vtkPiecewiseFunction::New();
    //gradientTransferFunction->AddPoint(20, 0.0);
    //gradientTransferFunction->AddPoint(255, 2.0);
    //gradientTransferFunction->AddSegment (600, 0.73, 900, 0.9);
    //gradientTransferFunction->AddPoint(1300, 0.1);
    m_volumeProperty = vtkVolumeProperty::New();

    m_volumeProperty->SetColor(m_colorTransferFunction);
    m_volumeProperty->SetScalarOpacity(m_PiecewiseFunction);
                                                                     // m_volumeProperty->SetGradientOpacity(m_PiecewiseFunction);
    m_volumeProperty->ShadeOn();
    m_volumeProperty->SetInterpolationTypeToLinear();
    m_volumeProperty->SetAmbient(0.2);
    m_volumeProperty->SetDiffuse(0.9);
    m_volumeProperty->SetSpecular(0.2);
    m_volumeProperty->SetSpecularPower(10);


    // m_VolumeRayCastCompositeFunction = vtkVolumeRayCastCompositeFunction::New();
    //vtkVolumeRayCastIsosurfaceFunction *m_VolumeRayCastCompositeFunction = vtkVolumeRayCastIsosurfaceFunction::New();

    m_FixedPointVolumeRayCastMapper = vtkFixedPointVolumeRayCastMapper::New();
    //m_FixedPointVolumeRayCastMapper->SetVolumeRayCastFunction(m_VolumeRayCastCompositeFunction);
    m_FixedPointVolumeRayCastMapper->SetInputConnection(m_ImageCast->GetOutputPort());
    m_FixedPointVolumeRayCastMapper->SetNumberOfThreads(3);

    volume1 = vtkVolume::New();
    volume1->SetMapper(m_FixedPointVolumeRayCastMapper);
    volume1->SetProperty(m_volumeProperty);

#if _DEBUG
    // vtkVolumeWriter *wSP=vtkVolumeWriter::New();
    //// vtkVolume *wSP=vtkVolume::New();
    // wSP->SetInputConnection(m_ImageCast->GetOutputPort());
    // wSP->SetFileName("F://ct/mmmm.vtk");
    // wSP->Write();
    // wSP->Delete();
#endif
    m_ThreeDRec_Renderer->AddVolume(volume1);
    // m_ThreeDRec_Renderer->SetBackground(1, 1, 1);
    //m_ThreeDRec_Renderer->SetBackground(0, 0, 0);
    //m_ThreeDRec_Renderer->SetBackground(255, 255, 255);
    //m_ThreeDRec_RenderWindow->SetSize(600, 600);

    renderWindowInteractor->Initialize();
    this->setWindowTitle(QStringLiteral("ÈýÎ¬ÖØ½¨-CPU½âËãÍê³É"));
    renderWindowInteractor->Start();
    m_ThreeDRec_Renderer->ResetCameraClippingRange();

    m_ThreeDRec_RenderWindow->Render();
}

void ThreeD_Reconstruction::RenderPipeline_GPU(vtkStringArray *_FilesYouWant)
{
    m_ThreeDRec_Renderer = vtkRenderer::New();
    m_ThreeDRec_RenderWindow = vtkRenderWindow::New();
    m_ThreeDRec_RenderWindow->AddRenderer(m_ThreeDRec_Renderer);
    ui.qvtkWidget_3DRec->SetRenderWindow(m_ThreeDRec_RenderWindow);
    renderWindowInteractor = vtkRenderWindowInteractor::New();
    renderWindowInteractor->SetRenderWindow(m_ThreeDRec_RenderWindow);

    vtkDecimatePro *deci = vtkDecimatePro::New();
    deci->SetTargetReduction(0.3);

    TrackballCamera = vtkInteractorStyleTrackballCamera::New();
    renderWindowInteractor->SetInteractorStyle(TrackballCamera);

    m_MyDICOMImageReader = vtkSmartPointer<vtkMyDICOMImageReader>::New();
    m_MyDICOMImageReader->SetFileNames(_FilesYouWant);
    m_MyDICOMImageReader->SetFileDimensionality(3);
    m_MyDICOMImageReader->SetDataScalarType(VTK_UNSIGNED_SHORT);
    m_MyDICOMImageReader->SetDataExtent(0, 255, 0, 255, 0, 123);
    m_MyDICOMImageReader->SetDataSpacing(0.9, 0.9, 0.9);
    // reader->SetDataOrigin(0.0, 0.0, 0.0);
    m_ImageCast = vtkImageCast::New();
    m_ImageCast->SetInputConnection(m_MyDICOMImageReader->GetOutputPort());
    m_ImageCast->SetOutputScalarTypeToUnsignedShort();
    m_ImageCast->ClampOverflowOn();

    m_PiecewiseFunction = vtkPiecewiseFunction::New();
    m_PiecewiseFunction->AddPoint(20, 0.0);
    m_PiecewiseFunction->AddPoint(255, 0.2);

    m_colorTransferFunction = vtkColorTransferFunction::New();
    m_colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.5, 0.0);
    m_colorTransferFunction->AddRGBPoint(60.0, 1.0, 0.0, 0.0);
    m_colorTransferFunction->AddRGBPoint(128.0, 0.2, 0.1, 0.9);
    m_colorTransferFunction->AddRGBPoint(196.0, 0.27, 0.21, 0.1);
    m_colorTransferFunction->AddRGBPoint(255.0, 0.8, 0.8, 0.8);
    //vtkPiecewiseFunction *gradientTransferFunction = vtkPiecewiseFunction::New();
    //gradientTransferFunction->AddPoint(20, 0.0);
    //gradientTransferFunction->AddPoint(255, 2.0);
    //gradientTransferFunction->AddSegment (600, 0.73, 900, 0.9);
    //gradientTransferFunction->AddPoint(1300, 0.1);
    m_volumeProperty = vtkVolumeProperty::New();

    m_volumeProperty->SetColor(m_colorTransferFunction);
    m_volumeProperty->SetScalarOpacity(m_PiecewiseFunction);
    // m_volumeProperty->SetGradientOpacity(m_PiecewiseFunction);
    m_volumeProperty->ShadeOn();
    m_volumeProperty->SetInterpolationTypeToLinear();
    m_volumeProperty->SetAmbient(0.2);
    m_volumeProperty->SetDiffuse(0.9);
    m_volumeProperty->SetSpecular(0.2);
    m_volumeProperty->SetSpecularPower(10);
    // m_VolumeRayCastCompositeFunction = vtkVolumeRayCastCompositeFunction::New();
    //vtkVolumeRayCastIsosurfaceFunction *m_VolumeRayCastCompositeFunction = vtkVolumeRayCastIsosurfaceFunction::New();

    m_volumeMapper_gpu = vtkGPUVolumeRayCastMapper::New();
                                                             //m_FixedPointVolumeRayCastMapper->SetVolumeRayCastFunction(m_VolumeRayCastCompositeFunction);              //ÔØÈë»æÖÆ·½·¨
    m_volumeMapper_gpu->SetInputConnection(m_ImageCast->GetOutputPort());
    //m_volumeMapper_gpu->SetNumberOfThreads(3);
    volume1 = vtkVolume::New();
    volume1->SetMapper(m_volumeMapper_gpu);
    volume1->SetProperty(m_volumeProperty);

#if _DEBUG
    // vtkVolumeWriter *wSP=vtkVolumeWriter::New();
    // //vtkVolume *wSP=vtkVolume::New();
    // wSP->SetInputConnection(m_ImageCast->GetOutputPort());
    // wSP->SetFileName("F://ct/mmmm.vtk");
    // wSP->Write();
    // wSP->Delete();
#endif
    m_ThreeDRec_Renderer->AddVolume(volume1);
    // ren->SetBackground(1, 1, 1);
    //ren->SetBackground(0, 0, 0);
    //ren->SetBackground(255, 255, 255);
    //m_ThreeDRec_RenderWindow->SetSize(600, 600);
    m_ThreeDRec_RenderWindow->Render();
    renderWindowInteractor->Initialize();
    this->setWindowTitle(QStringLiteral("ÈýÎ¬ÖØ½¨-GPU½âËãÍê³É"));
    renderWindowInteractor->Start();
    m_ThreeDRec_Renderer->ResetCameraClippingRange();
}
