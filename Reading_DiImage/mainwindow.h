#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    int Rows;
    int Cols;
    unsigned char *dispImg;
    ~MainWindow();

private slots:
    void on_PB_Load_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *item;
};

#endif // MAINWINDOW_H
