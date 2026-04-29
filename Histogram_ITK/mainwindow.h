#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <itkGDCMImageIO.h>
#include <QDebug>
#include <itkImage.h>
#include <QImage>
#include <itkPoint.h>
#include <itkFixedArray.h>

#include <itkGDCMImageIO.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageToHistogramFilter.h>
#include <itkImageRandomIteratorWithIndex.h>
#include <itkHistogram.h>
#include <itkHistogramAlgorithmBase.h>
#include <itkHistogramThresholdCalculator.h>
#include <itkHistogramToImageFilter.h>
#include <itkSize.h>
#include <itkMeasurementVectorTraits.h>
#include <itkImageToHistogramFilter.h>
#include <itkMeasurementVectorTraits.h>
#include <itkImageToHistogramFilter.h>

#include <QObject>

#include <QtCore>

#include "qcustomplot.h"

typedef unsigned short InputPixelType;
typedef itk::Image<InputPixelType, 2> MovingImageType; // make movingImageType smart pointer as global (because i need to make pointer type function)





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);



    //void ReadFixedImage();
   // void ReadFixedImage(); // return image of unsigned short type (16 bits)
    unsigned short *ReadFixedImage(); // return image of unsigned short type (16 bits)
    unsigned short *ptr = NULL;
    unsigned short *ImageF=NULL;
    unsigned short *ImagePix=NULL;
    MovingImageType::Pointer ReadMovingImage();

    MovingImageType::Pointer MovingImage;

    QVector<double> HistogramFixed();
    QVector<double> HistogramMove();

    void plotGraphF();
    void plotGraphM();

//    QCustomPlot *fcustomPlotClass;
//    QCustomPlot *mcustomPlotClass;


//    QCustomPlot *FixedI;
//    QCustomPlot *MoveI;


    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector <int> NewVector; // integer type vector in private

};

#endif // MAINWINDOW_H
