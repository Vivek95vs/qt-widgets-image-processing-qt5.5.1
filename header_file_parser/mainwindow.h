#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include <rtkConstantImageSource.h>
//#include <rtkThreeDCircularProjectionGeometryXMLFileWriter.h>
//#include <rtkRayEllipsoidIntersectionImageFilter.h>
//#include <rtkCudaFDKConeBeamReconstructionFilter.h>
//#include <rtkFieldOfViewImageFilter.h>
//#include <itkImageFileWriter.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
//    void processFiles(const QString& folderPath);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
