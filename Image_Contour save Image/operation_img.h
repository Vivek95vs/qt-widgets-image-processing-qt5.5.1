#ifndef OPERATION_IMG_H
#define OPERATION_IMG_H
#include "disp_evt.h"
#include "ruler_item.h"

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>

#include <itkImageToVTKImageFilter.h>
#include "itkVTKImageImport.h"
#include "itkVTKImageExport.h"

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
#include "itkRGBPixel.h"
#include "itkPNGImageIO.h"
#include "itkNiftiImageIO.h"
#include "itkNiftiImageIOFactory.h"
#include <nifti1_io.h>
#include <itkAndImageFilter.h>
#include <gdcmUIDGenerator.h>

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

namespace Ui {
class operation_Img;
}

class operation_Img : public QDialog
{
    Q_OBJECT

public:
    explicit operation_Img(QWidget *parent = 0);
    QImage myImage;
    QImage myImage1;
    const int w=3072,h=3072;
     QString treatmentMachineName;

//    Operation *opt;
    unsigned char* arr=new unsigned char[w*h];
    unsigned char* arr1=new unsigned char[w*h];
    unsigned char* arr2=new unsigned char[w*h];
    unsigned char* arr3=new unsigned char[w*h];
    bool Pressed;

        QList<QGraphicsItem*>measureListAP;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsItem *item;
    QGraphicsPixmapItem *p1=NULL;
    QGraphicsPixmapItem *p2=NULL;
    int ToggleScale;
    int ValueDiameter;
    Ruler_Item *itemRuler;
    ~operation_Img();

private slots:


    void on_PB_LoadImage1_clicked();

    void on_PB_LoadImage2_clicked();

    void on_PB_Overlay_clicked();

    void on_PB_Quadrant_clicked();

    void on_PB_CheckerBoard_clicked();

    void on_PB_Toggle_clicked();

    void on_PB_Rectangle_clicked();

    void on_PB_Ellipse_clicked();

    void on_PB_FreeHand_clicked();

    void on_PB_Delete_clicked();

    void on_PB_Clearall_clicked();

    void on_PB_RectChange_clicked();



    void on_saveRectitem_clicked();

    void on_pushButton_clicked();

private:
    Ui::operation_Img *ui;
    Disp_Evt *Evt;
    int dMode=0;

public slots:

    void changedLeftPos();
    void changedRightPos();
    void changedUpPos();
    void changedDownPos();
    void receivetohide();
    void saverectitem(QGraphicsItem* drawrect);

    void on_PB_HorizRuler_clicked();
    void on_PB_VertiRuler_clicked();
    void on_PB_Image_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
};

#endif // OPERATION_IMG_H
