#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QDir>
#include <vtkDICOMImageReader.h>
#include <vtkImageReslice.h>
#include <QGraphicsColorizeEffect>
#include <vtkDICOMGenerator.h>
#include <vtkDICOMUIDGenerator.h>
#include <vtkStringArray.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkDICOMReader.h>
#include <vtkDICOMTag.h>
#include <vtkDICOMWriter.h>
#include <vtkDICOMMRGenerator.h>
#include <vtkDICOMMetaData.h>
#include <vtkImageImport.h>
#include <vtkDICOMCTGenerator.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include<vtkDirectory.h>
#include<vtkMatrix4x4.h>
#include<vtkDICOMSorter.h>
#include<vtkDICOMDirectory.h>
#include<vtkImageExport.h>
#include<vtkIntArray.h>
#include<vtkMedicalImageProperties.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int* dim;
    unsigned char *dispImg;
    unsigned short *v1;
    int w=3072,h=3072;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsItem *item;
};
#endif // MAINWINDOW_H
