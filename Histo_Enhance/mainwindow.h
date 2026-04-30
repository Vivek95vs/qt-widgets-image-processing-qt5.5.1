#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "enhancement.h"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QGraphicsItem"

#include "gdcmDataSet.h"
#include <gdcmUIDGenerator.h>
#include <gdcmTypes.h>
#include <gdcmReader.h>
#include <gdcmSmartPointer.h>
#include <gdcmImageReader.h>
#include <gdcmAttribute.h>
#include <gdcmSequenceOfItems.h>
#include <gdcmFileMetaInformation.h>
#include "itkImageFileWriter.h"
#include "itkImageFileReader.h"
#include <itkGDCMImageIO.h>
#include <itkMetaDataDictionary.h>
#include <itkMetaDataObject.h>
#include <itkImportImageFilter.h>
#include "enhanceimage.h"

//using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    unsigned short *radbuf;
    unsigned short *pixelBuffer;
//    cv::Mat originalImage;
    int ImgWidth=3072;
    int ImgHeight=3072;
    int w=400 ;
    int h=400;
    QImage qimagehist;

private slots:
    void on_PB_LOAD_clicked();

    void on_Maxslider_valueChanged(int value);

    void on_minslider_valueChanged(int value);

    void on_brightness_valueChanged(int value);

    void on_contrast_valueChanged(int value);
    void updateImage();


    void on_Auto_clicked();

    void on_Reset_clicked();

    void on_checkBox_clicked(bool checked);


    void on_SaveDB_clicked();

private:
    Ui::MainWindow *ui;
    unsigned char *dispImg=NULL;
    unsigned char *MatImg=NULL;
    unsigned short *usImage=NULL;
    Enhancement *enhance;
    EnhanceImage *enhanceMat;
//    cv::Mat img1;
    QImage myImage;
    QGraphicsScene *Scene;
    QGraphicsItem *item;
    QGraphicsView *view;
//    cv::Mat adjustImage(const cv::Mat &image, int min, int max, int brightness, int contrast);
    void updateFromBrightnessContrast();
    void updateFromMinMax();
    void plothistogram(unsigned char *img);
};

#endif // MAINWINDOW_H
