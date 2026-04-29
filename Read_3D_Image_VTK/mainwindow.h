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
#include<vtkVolumeRayCastMapper.h>


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
#include <QImage>
#include <itkResampleImageFilter.h>
#include "customescene.h"


#define vDIM 512
#define vCTDIM 512
#define pDIM 3072

//extern  float* cbctvolume=NULL;
extern int ctDIM1,ctDIM2,ctDIM3;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void display3D(float* volume,const int *dimension,double pixPitch);
    void CopyImportVoidPointer(void *ptr, vtkIdType size);
    static vtkImageExport *New();

    // Now Axial, Sagital and Frontal Display function
    unsigned char * getAxialSlice(float* vol,int value,int type);
    unsigned char * getFrontalSlice(float* vol,int value,int type);
    unsigned char * getSagitalSlice(float* vol,int value,int type);

    unsigned char getAxialSlice();
    void getFrontalSlice();
    void getSagitalSlice();

    void AxialSlice();

    const int *dimension; // from main function to here because it's need to make public so that it would be call in any function

    vtkSmartPointer<vtkDICOMReader> reader = NULL; //


   // vtkSetMacro(DataScalarType,int); // commented
    //void SetDataScalarTypeToFloat(){this->SetDataScalarType(VTK_FLOAT);} // commented

   // vtkSetMacro(NumberOfScalarComponents,int); // commented
    //vtkGetMacro(NumberOfScalarComponents,int); // commented

    void SetDataExtentToWholeExtent();
   // {this->SetDataExtent(this->GetWholeExtent());} // commented

   // vtkSetVector3Macro(DataSpacing,double); // commented
   // vtkGetVector3Macro(DataSpacing,double); // commented

    //MyQvtkWidget *vtkWidget; // commented
    vtkColorTransferFunction *colorFunc;
    vtkPiecewiseFunction *alphaChannelFunc;
    vtkRenderer         *ren;

   void on_threeDslider_valueChanged(int value);  // see it use otherwise remove it

    void setLabel(QLabel *label);  // Add
    void setCancelButton(QPushButton *button); // Add
    void setBar(QProgressBar *bar); // Add

    void setpixelPitch(float realSize);

    QString rtStructFile;
    vtkStringArray *GetFileNamesForSeries(int i);
   // vtkIdType GetNumberOfValues() { return this->MaxId + 1;}

    vtkIdType Size;         // allocated size of data
    vtkIdType MaxId;        // maximum index inserted thus far
    int NumberOfComponents; // the number of components per tuple

   float* cbctvolume=NULL;

//    virtual void SetNumberOfTuples(vtkIdType number)
//    { this->SetNumberOfValues(this->NumberOfComponents* number); }
//    void SetNumberOfValues(vtkIdType number);
//    vtkIdType GetNumberOfValues() { return this->MaxId + 1; }

    ~MainWindow();

private slots:
    void on_pushButton_clicked(/*const QSize &iconSize*/);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


//    unsigned char * getAxialSlice(float* vol, int value, int type);   //

//    unsigned char * getFrontalSlice(float* vol, int value, int type);

//    unsigned char * getSagitalSlice(float* vol,int value,int type);


    void on_Draw_clicked();

private:
    Ui::MainWindow *ui;
    customescene *ascene;
    customescene *fscene;
    customescene *sscene;

   // float lowerThreshold, upperThreshold; // Lower and Upper Threshold Value
    QVTKWidget *vtkWidget;   // from display3D

    /* Axial, Sagital and Frontal Slices of Image */
    unsigned char* axialSliceCBCT=NULL;
    unsigned char* sagitalSliceCBCT=NULL;
    unsigned char* frontalSliceCBCT=NULL;


    int ctDIM;
    //vtkSmartPointer<vtkDICOMReader> CTReader; //fixed AP dicom image reader
    vtkSmartPointer<vtkDICOMReader> CBCTReader; //moving AP dicom image reader
    int volSize1,volSize2,volSize3; // Size of Image in X, Y and Z Direction

    short *v;

    float* ctvolume=NULL;
   // float* cbctvolume=NULL;
    vtkImageImport* volumeImport=NULL;

    float lowerThreshold, upperThreshold;
    unsigned char* ctslice=NULL;
    unsigned char* cbctslice=NULL;
    vtkSmartPointer<vtkDICOMReader> dicomRead(QString path);
    int GetNumberOfSeries();

    QList<double> pixSpacingCBCT;
    //QList<double> pixSpacingCT;

    void setVtkVolumeToC(float *vol); // Function to Export CBCT read to CBCT Volume


//    InitialScreen *initialScreen;

    int scaleFactor;

//    MyQvtkWidget(QWidget *w);
//    MyQvtkWidget *vtkWidget;
//    AP_LAT        *aplatScreen;

//    QWidget *CT_CBCT; // see it
//    CT_CBCT *ctCbctScreen;


//    CustomScene *axialScene;
//    CustomScene *sagitalScene;
//    CustomScene *frontalScene;

    //
    //
//    QAbstractSlider *QSlider;
//    QSlider *threeDslider;



};

#endif // MAINWINDOW_H
