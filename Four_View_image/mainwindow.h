#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QDebug>

#include <QObject>
#include <QMainWindow>
#include <QShortcut>
#include <QStringList>

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolume16Reader.h>
#include <vtkVolume.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkCamera.h>
#include <vtkVolumeRayCastMapper.h>


#include <QPlainTextEdit>
#include <QListWidgetItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <iostream>
#include <QtXml/QDomDocument>
#include <time.h>
#include <QGraphicsProxyWidget>
#include <qgraphicsproxywidget.h>
#include <QDebug>
#include <QPixmap>
#include <QCloseEvent>
#include <QProgressDialog>
#include <QErrorMessage>
#include <QtMath>
#include <QVector3D>
#include <QMatrix4x4>
#include <QGraphicsDropShadowEffect>
#include <QProgressBar>
#include <QDirIterator>

#include <QProgressDialog>
#include <QSize>
#include <QApplication>
#include <QString>
#include <QDir>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>
#include <QPixmap>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include "itkCommand.h"

#include <QProgressDialog>
#include <QProgressBar>

// MACROS NEEDED FOR SOME VTK INITIALIZATION ISSUE
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkInteractionStyle)

// First include the required header files for the VTK classes we are using.
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
#include "mywidget.h"
#include "customscene.h"

#define vDIM 512

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
    void display3D(float* volume,const int *dimension,double pixPitch);
    vtkSmartPointer<vtkDICOMReader> reader = NULL;
    vtkImageImport* volumeImport=NULL;
    vtkColorTransferFunction *colorFunc;
    vtkPiecewiseFunction   *alphaChannelFunc;
    vtkRenderer          *ren;

    unsigned char * getAxialSlice(float* vol,int value);
    unsigned char * getFrontalSlice(float* vol,int value);
    unsigned char * getSagitalSlice(float* vol,int value);


private slots:
    void on_Rendering_clicked();

    void on_Sagital_clicked();

    void on_Axial_clicked();

    void on_Frontal_clicked();


    void on_PB_Ellipse_clicked();

    void on_PB_Rectangle_clicked();

    void on_PB_Freehand_clicked();

    void on_PB_Circle_clicked();

    void on_PB_Rect_clicked();

    void on_PB_Clear_clicked();

    void on_PB_clear_clicked();

    void on_PB_Delete_clicked();

    void on_Lowerthresh_valueChanged(int value);

    void on_Upperthresh_valueChanged(int value);

private:
    Ui::MainWindow *ui;

//    QVTKWidget *vtkWidget;

    int volSize1,volSize2,volSize3;
    int scaleFactor;
    float *cbctvolume=NULL;
    short *v;
    unsigned char* cbctslice=NULL;
    QList<double> pixSpacingCBCT;

    vtkSmartPointer<vtkDICOMReader> dicomRead(QString path);
    void setVtkVolumeToC(float *vol);

    double widthAxial;
    double heightAxial;

    unsigned char* axialSliceCT;
    unsigned char* frontalSliceCT;
    unsigned char* sagitalSliceCT;

//    float lowerThreshold, upperThreshold;

    double widthSagital;
    double heightSagital;

    double widthFrontal;
    double heightFrontal;

    bool scale=false;
    QImage image;
    QGraphicsPixmapItem *pixMap;
    MyWidget *Scene;
    customscene *scene1;
    customscene *scene2;
    customscene *scene3;
};

#endif // MAINWINDOW_H
