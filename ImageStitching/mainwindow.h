#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qgraphicsscene.h"
#include <QGraphicsPixmapItem>

//#include <itkImageToVTKImageFilter.h>
//#include <itkVTKImageImport.h>
//#include <itkVTKImageExport.h>

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
#include <gdcmStringFilter.h>
#include <gdcmValue.h>
#include <gdcmGlobal.h>
#include <gdcmDicts.h>
#include <gdcmDictEntry.h>
#include <gdcmTag.h>
#include <gdcmVR.h>

#include <itkRGBPixel.h>
#include <itkPNGImageIO.h>
#include <itkNiftiImageIO.h>
#include <itkNiftiImageIOFactory.h>
#include <nifti1_io.h>
#include <itkAndImageFilter.h>
#include <itkTranslationTransform.h>

using namespace  gdcm;
//gdcm
#include "gdcmImage.h"
#include "gdcmReader.h"
#include "gdcmFile.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmWriter.h"
#include "gdcmItem.h"
#include "gdcmTag.h"
#include "gdcmImageWriter.h"
#include "gdcmAttribute.h"
#include "gdcmImageReader.h"
#include <gdcmSmartPointer.h>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int radSize=3072;
    QImage myImage;
    QGraphicsView *view;
    QGraphicsItem *item;

    QString Simulation_Quad_Raw_Path;

    void ImageStitching();
    void saveMultiscanImageDicom(unsigned short * image, QString path, int imSize, int croppedheight, int gantrypos);
    void downsampleImage(unsigned short *originalImage, std::vector<unsigned short> &downsampledImage, int Originalwidth, int Originalheight, int downsampledWidth, int downsampledHeight);

private slots:
    void on_ImageMerge_clicked();

    void on_single_crop_clicked();

    void on_Two_imagecrop_clicked();

    void on_three_imagecrop_clicked();

    void on_Original_image_clicked();

    void on_Four_Image_crop_clicked();

    void on_pushButton_2_clicked();

    void on_Two_Dicom_crop_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
