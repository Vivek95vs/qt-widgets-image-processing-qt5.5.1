#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QFile"
#include "QMessageBox"
#include "QDir"
#include "WriteRTStruct.h"

#include "itkImageFileReader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    unsigned short * buffer = NULL;
    int dimsize=512;
    int Rows2,Cols2;

    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader< Img >ReaderType1;
    QStringList SOPINSTANCEUIDList,StudyINSTANCEUIDList,SeriesINSTANCEUIDList,FrameReferenceUIDList;
//    QStringList SOPINSTANCEUIDList1,SOPINSTANCEUIDList2,SOPINSTANCEUIDList3,SOPINSTANCEUIDList4,SOPINSTANCEUIDList5,SOPINSTANCEUIDList6;
    void ReadImageToDicom(const Img *image1, const size_t imSize, int j, std::string fileName);
    std::string age,PatientName,PatientID,gen,manufacture,model,DOB,StudyD,pixs,Seri,SOPINSTANCEUID,StudyINSTANCEUID,SeriesINSTANCEUID,FrameReferenceUID;

    WriteRTStruct *rtstruct;
public slots:


private slots:
    void on_Readtag_clicked();

    void on_RTstruct_generate_clicked();

    void on_List_data_clicked();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
