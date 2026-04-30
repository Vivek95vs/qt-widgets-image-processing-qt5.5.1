#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vtkDICOMImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>
#include <vtkImageData.h>
#include <vtkDICOMMetaData.h>
#include <vtkDICOMReader.h>
#include "vtkDICOMDirectory.h"
#include <vtkDICOMTagPath.h>
#include <vtkDICOMWriter.h>
#include <vtk
#include "QDebug"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Tagwrite_clicked()
{

    vtkSmartPointer<vtkDICOMReader> reader = vtkSmartPointer<vtkDICOMReader>::New();

    // Get the DICOM metadata

    QString dicomFolder="D:\\SliceWrite\\Dicomtag";
    vtkSmartPointer <vtkDICOMDirectory> dicomdir = vtkSmartPointer <vtkDICOMDirectory>:: New ();
    dicomdir -> SetDirectoryName (dicomFolder.toStdString().c_str());


    try
    {
     dicomdir ->Update ();
    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files";
        //return;
    }

//    dicomdir ->Update ();


    vtkSmartPointer<vtkDICOMReader> reader1 = vtkSmartPointer<vtkDICOMReader>::New();

    /*int */ numSeries=dicomdir->GetNumberOfSeries();

    vtkStringArray *sortedFiles;

    qDebug()<<"Number of Series found :"<<numSeries;

    if(numSeries>1 || numSeries == 0)
        return;//QMessage Box to be added
//    while(numSeries>0){
    //if(numSeries==1){

        sortedFiles = dicomdir -> GetFileNamesForSeries (numSeries-1);

        for(int i=0;i<sortedFiles->GetNumberOfValues();i++){

            if(reader1->CanReadFile(sortedFiles->GetValue(i))){

                reader1->SetFileName(sortedFiles->GetValue(i));
                reader1->SetGlobalWarningDisplay(false);

                try
                {
                 reader1->Update();
                }
                catch(...)
                {
                    qDebug()<<"Exception  reading dicom files";
                    return;
                }

                if(QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(
                                                              vtkDICOMTag(0x0008,0x0060)).AsString()).compare("RTIMAGE")==0)
                {
                    return;
                }
//
                //vtkObject::GlobalWarningDisplayOff();

                /* Search for RT Structure file and get filename*/
                if(QString::fromStdString(reader1->GetMetaData()->GetAttributeValue(
                                              vtkDICOMTag(0x0008,0x0060)).AsString()).compare("RTSTRUCT")==0){
                     rtStructFile = sortedFiles->GetValue(i);

                     //qDebug()<<"RTSTRUCT available"<<rtStructFile;

                }

//                }

            }
        }



    reader1=NULL;
    reader =NULL;

    reader =vtkSmartPointer<vtkDICOMReader>::New();
    reader->SetFileNames(sortedFiles);
    reader->SetMemoryRowOrderToFileNative();

//    re

    try
    {
        reader->Update();

    }
    catch(...)
    {
        qDebug()<<"Exception  reading dicom files";
//        return 0;

    }

    vtkSmartPointer<vtkDICOMMetaData> metaData = reader->GetMetaData();

//    vtkDICOMTagPath tagPath(DC::PatientName);
//    std::string originalValue = metaData->GetAttributeValue(tagPath).GetString();

    vtkDICOMTag patientOrientationTag(0x0018, 0x1111);
    if (metaData->HasAttribute(patientOrientationTag))
    {
        // Tag 0018,1111 exists in the metadata
        // You can now retrieve its value or perform any other operations as needed
        std::cout << "Tag 0018,1111 exists in the metadata." << std::endl;
        std::string patientOrientationValue = metaData->GetAttributeValue(patientOrientationTag).AsString();
        std::cout << "Patient Orientation: " << patientOrientationValue << std::endl;
    }
    else
    {
        // Tag 0018,1111 does not exist in the metadata
        std::cout << "Tag 0018,1111 does not exist in the metadata." << std::endl;
        vtkDICOMTag anotherCustomTag(0x0018, 0x1111);  // Example tag (Patient's ID)
        QString value = "12345";
        vtkDICOMValue anotherCustomValue(value.toStdString().c_str());      // Example value

        metaData->SetAttributeValue(anotherCustomTag, anotherCustomValue);
//        metaData->SetAttributeValue(DC::DistanceSourceToPatient,"570.00");
    }

    vtkSmartPointer<vtkDICOMWriter> writer = vtkSmartPointer<vtkDICOMWriter>::New();
    writer->SetMemoryRowOrderToFileNative();
    writer->SetMetaData(metaData);  // Set the modified metadata
    writer->SetInputData(reader->GetOutput());  // Set your image data
    writer -> SetFilePattern ("%s/slice%04.4d.dcm");//pattern is fixed.
    writer->SetFilePrefix("D:\\SliceWrite\\Outputpath");  // Set the output directory
    writer->Update();
}
