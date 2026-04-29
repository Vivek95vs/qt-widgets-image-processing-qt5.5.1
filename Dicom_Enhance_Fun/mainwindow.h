#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QString>
#include <QtCore>
#include <QtGui>

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
#include "imageenhacement.h"

using namespace gdcm;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString strlist;
    QList<QList<QStringList>> tags;
    double PixelX=300,PixelY=300;
    QPointF PixelPitch1;
    QPointF PointCen;
    QVector<QPointF>Size,Cancer_center;
    QList<QStringList>Contentlist2;
    QStringList TagList1;
    int i;
    QList<QPointF> IsoCentres;
    int w=3072 ;
    int h=3072;
    int Rows3;
    int Cols;
    unsigned short *dispImg;
    unsigned char *disp;
    unsigned char *slice;
    QImage q_image;
    QString editBeamName;
    QString treatmentMachineName;
    int count;

private slots:
    void on_PB_load_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item;
    QGraphicsView *view;
    ImageEnhacement *enhancer;

};

#endif // MAINWINDOW_H
