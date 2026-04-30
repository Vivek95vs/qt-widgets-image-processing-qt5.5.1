#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QFile>
#include <QDir>
#include <QWidget>
#include <QtWidgets>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int i;
    QImage q_image;
    int Rows;
    int Cols;
    unsigned char *dispImg;
    QString SiteNameLabel;
    ~MainWindow();
    std::string ReadOfflineDXPrivateTagDetails(gdcm::Tag tg, gdcm::DataSet ds);

private slots:
    void on_LOAD_clicked();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsItem *item;
};

#endif // MAINWINDOW_H
