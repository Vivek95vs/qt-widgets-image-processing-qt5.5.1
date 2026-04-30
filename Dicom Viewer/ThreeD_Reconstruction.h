#ifndef THREED_RECONSTRUCTION_H
#define THREED_RECONSTRUCTION_H

#include <QWidget>
#include "ui_ThreeD_Reconstruction.h"
#include <vtkStringArray.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include "vtkMyDICOMImageReader.h"
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkImageCast.h>


class ThreeD_Reconstruction : public QWidget
{
    Q_OBJECT

public:
    ThreeD_Reconstruction(QWidget *parent = Q_NULLPTR);//Ä¬ÈÏ¹¹Ôì
    ThreeD_Reconstruction(std::vector<std::string>*filenames_v,QWidget *parent = Q_NULLPTR);//´øÊý¾Ý¹¹Ôì
    ~ThreeD_Reconstruction();

    void OnReconstruction();
private:
    vtkRenderer * m_ThreeDRec_Renderer;
    vtkRenderWindow *m_ThreeDRec_RenderWindow;
    vtkImageCast *m_ImageCast;
    vtkPiecewiseFunction *m_PiecewiseFunction;
    vtkColorTransferFunction *m_colorTransferFunction;
    vtkVolumeProperty *m_volumeProperty;
    vtkVolumeRayCastCompositeFunction *m_VolumeRayCastCompositeFunction;
    vtkFixedPointVolumeRayCastMapper *m_FixedPointVolumeRayCastMapper;
    vtkVolume *volume1;
    vtkSmartPointer<vtkMyDICOMImageReader> m_MyDICOMImageReader;
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> TrackballCamera;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
    vtkGPUVolumeRayCastMapper *m_volumeMapper_gpu;

    vtkSmartPointer<vtkStringArray> m_Filenames;
private:
    Ui::ThreeD_Reconstruction ui;
    void RenderPipeline_CPU(vtkStringArray*);
    void RenderPipeline_GPU(vtkStringArray*);
};


#endif // THREED_RECONSTRUCTION_H
