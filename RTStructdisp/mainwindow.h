#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "graphicsscene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <itkImageSeriesReader.h>
#include <itkGDCMImageIO.h>
#include <itkExtractImageFilter.h>
#include <gdcmReader.h>
#include <gdcmTag.h>
#include <gdcmAttribute.h>
#include <gdcmSequenceOfItems.h>
#include "itkPolygonSpatialObject.h"
#include "itkSpatialObjectToImageFilter.h"
#include "itkNiftiImageIO.h"
#include "itkGroupSpatialObject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void displayImagesWithContours();
    void loadRTStructure(const QString &fileName);
    void loadCTImages(const QStringList &fileNames);

    typedef itk::Image< uint8_t, 3 >   ImageType;
    typedef itk::GroupSpatialObject<2> GroupType;
    typedef itk::PolygonSpatialObject<2> PolygonType;
    typedef itk::SpatialObjectPoint<2> PolygonPointType;
    PolygonPointType p;

    GraphicsScene* scene;


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
