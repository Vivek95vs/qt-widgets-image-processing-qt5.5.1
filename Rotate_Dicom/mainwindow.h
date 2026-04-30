#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QImage q_image;
    int width;
    int height;
    unsigned char *dispImg;

    typedef unsigned short img;
    typedef unsigned short out_img;

    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;
    Reader::Pointer reader=Reader::New();
    typedef itk::GDCMImageIO ImageType;
    ImageType::Pointer gdcmImage=ImageType::New();
    Img::Pointer image;
    ~MainWindow();

private slots:
    void on_PB_LoadImage_clicked();

    void on_PB_Rotate_clicked();

    void on_PB_MeanFilter_clicked();

    void on_PB_Transform_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *item,*item1;
};

#endif // MAINWINDOW_H
