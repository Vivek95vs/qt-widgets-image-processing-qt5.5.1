#ifndef VTKIMAGESEGMENTCALLBACK_H
#define VTKIMAGESEGMENTCALLBACK_H

#include <head_all.h>
#include <QVTKWidget.h>
#include <itkImageToVTKImageFilter.h>
#include "itkGDCMImageIO.h"

enum  SegmentFunc
{
    NULL_Seg,
    Seg_connectedthres,
    Seg_neighconnected,
    Seg_confidconnected,
    Seg_waterseg,
    Seg_fastmarching,
    Seg_shapedectection,
    Seg_gibblsprior
};


class MyStyle : public vtkInteractorStyleImage
{
public:
    static MyStyle* New();
    void OnLeftButtonDown() override;
};
class vtkImageSegmentCallback : public vtkCommand
{
    //const unsigned int Dimension = 2;
    typedef  float  InputPixelType;
    typedef  float  OutputPixelType;
    typedef  float  InternalPixelType;

    typedef itk::Image< InputPixelType, 2 >   InputImageType;
    typedef itk::Image< InternalPixelType, 2 >  InternalImageType;
    typedef itk::Image< OutputPixelType, 2 > OutputImageType;

    typedef itk::ImageToVTKImageFilter<OutputImageType>   ConnectorType;
    typedef itk::ImageFileReader< InternalImageType > ReaderType;
    typedef itk::ImageFileWriter<  OutputImageType  > WriterType;
    typedef itk::GDCMImageIO      ImageIOType;
    typedef itk::CastImageFilter< InternalImageType, OutputImageType >CastingFilterType;
    typedef itk::CurvatureFlowImageFilter< InternalImageType, InternalImageType > CurvatureFlowImageFilterType;//Æ½»¬ÓÃµÄ
public:
    static vtkImageSegmentCallback *New();
    vtkImageSegmentCallback();
    ~vtkImageSegmentCallback();
    void SetPicker(vtkPropPicker *picker);
    void SetAnnotation(vtkCornerAnnotation *annotation);
    void SetViewer(vtkImageViewer2 *viewer);
    void SetDir(std::string dir);
    void SetQvtk(QVTKWidget* qvtk);
    void SetCount(int count);
    virtual void Execute(vtkObject *, unsigned long event, void *);
private:

    void seg_connectedthres(std::string filename,double pos_x,double pos_y,double pixel_f,double pixel_s);
    void seg_neighconnected(std::string filename, double pos_x, double pos_y, double pixel_f, double pixel_s);
    void seg_confidconnected(std::string filename, double pos_x, double pos_y);
    void seg_waterseg(std::string filename, double NumberOfIterations,double ConductanceParameter,
                                    double UsePrincipleComponents, double watershedLevel, double Threshold);
    void seg_fastmarching(std::string filename, double pos_x, double pos_y, double alpha, double beta,
                                    double sigma, double UpperThreshold, double StoppingValue);
    void seg_shapedectection(std::string filename, double pos_x, double pos_y, double seedValue, double alpha,
                                    double beta, double sigma,double curvatureScaling, double propagationScaling);

private:

    vtkImageViewer2 *Viewer;
    vtkPropPicker *Picker;
    vtkCornerAnnotation *Annotation;
    vtkPointData* PointData;
    QVTKWidget* qvtk;
    int count;
};
#endif // VTKIMAGESEGMENTCALLBACK_H
