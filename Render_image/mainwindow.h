#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QVTKWidget.h"
#include <QVTKWidget.h>
#include <vtkImageImport.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkMatrix4x4.h>
#include <vtkSmartPointer.h>
#include <vtkDICOMReader.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageShiftScale.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <itkImageToVTKImageFilter.h>
#include <vtkImageCast.h>
#include <vtkImageImport.h>
#include <vtkImageData.h>
#include <vtkTransform.h>
#include <vtkImageReslice.h>
#include <vtkCamera.h>

//ITK
#include <itkImageToVTKImageFilter.h>
#include <itkVTKImageImport.h>
#include <itkVTKImageExport.h>

#include <itkImage.h>
#include <itkPoint.h>
#include <itkImageSliceIteratorWithIndex.h>
#include <itkImageIteratorWithIndex.h>
#include <itkPointSetToImageFilter.h>
#include <itkExtractImageFilter.h>
#include <itkGroupSpatialObject.h>
#include <itkSpatialObjectToImageFilter.h>
#include <itkPolygonSpatialObject.h>
#include <itkImageFileWriter.h>
#include <itkImageFileReader.h>
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include <gdcmTypes.h>
#include <gdcmReader.h>
#include <gdcmSmartPointer.h>
#include <gdcmAttribute.h>
#include <gdcmSequenceOfItems.h>
#include <gdcmFileMetaInformation.h>
#include <itkRGBPixel.h>
#include <itkPNGImageIO.h>
#include <itkNiftiImageIO.h>
#include <itkNiftiImageIOFactory.h>
#include <nifti1_io.h>
#include <itkAndImageFilter.h>
#include <itkTranslationTransform.h>

#include <vtkDICOMDirectory.h>
#include <vtkStringArray.h>
#include <vtkDICOMMetaData.h>
#include <vtkSetGet.h> // not need

#include <vtkRenderer.h>
#include <vtkWidgetEvent.h>

#include <QWidget>

#include <QSlider>

#include <vtkImageExport.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    const int *dimension;
    vtkColorTransferFunction *colorFunc;
    vtkPiecewiseFunction *alphaChannelFunc;
    vtkRenderer *ren;

private slots:
    void on_PB_Load_clicked();

private:
    Ui::MainWindow *ui;
    QVTKWidget *vtkWidget;
    short *v;
    int volSize1,volSize2,volSize3;
    float* newvolume=NULL;
    unsigned char* newslice=NULL;
    int scaleFactor;
    QList<double> pixSpacingCBCT;

    vtkImageImport* volumeImport=NULL;
};

#endif // MAINWINDOW_H
