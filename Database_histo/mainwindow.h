#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QStringList"
#include "QList"
#include "QString"
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkResampleImageFilter.h>
#include <QFileDialog>
#include <QDebug>
#include <itkGDCMImageIO.h>
#include <itkMetaDataDictionary.h>
#include <itkMetaDataObject.h>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <itkEuler2DTransform.h>
//#include "enhancement.h"
#include "imageenhancementnew.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QImage q_image;
    int Rows;
    int Cols;
//    int width=3072;
//    int height=3072;
//    int width=512;
//    int height=512;
    unsigned char *dispImg;
    double alpha;
    double beta;
    float lowerThreshold, upperThreshold;
    ~MainWindow();
    unsigned short *radbuf;
//    int ImgWidth=3072;
//    int ImgHeight=3072;
//    int width=3072 ;
//    int height=3072;

    int ImgWidth=3072;
    int ImgHeight=3072;
    int width=3072;
    int height=3072;

private slots:
    void on_PB_LoadDicom_Image_clicked();

    void on_PB_MedianFilter_clicked();

    void on_PB_Invert_Filter_clicked();

    void on_PB_Reset_clicked();

    void on_Slider_Bright_valueChanged(int value);

    void on_Slider_Contrast_valueChanged(int value);

    void on_Slider_WC_valueChanged(int value);

    void on_Slider_WW_valueChanged(int value);

    void on_Load_Raw_clicked();

    void on_combo1_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
//    QString AlphaVal;
    QList<double> AlphaList;
    QStringList AlphaVal;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *item,*item1;
//    unsigned char *dispImg=NULL;
    unsigned short *usImage=NULL;
    unsigned short *img12=NULL;
//    Enhancement *enhance;
    ImageEnhancementNew *enhancer;
    QImage myImage;
    unsigned short *img=NULL;
//    QGraphicsItem *item;

//signals:
//    void databasesig(QString);

};

#endif // MAINWINDOW_H
