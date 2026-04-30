#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    char uid[100];

//    write();
    read();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::write()
{
    DcmFileFormat fileformat;

    QString filename = ("D:/Workflow/Test images/rawImage_2.dcm");
    fileformat.loadFile(filename.toStdString().c_str());

    DcmDataset *dataset = fileformat.getDataset();

    qDebug()<<"image loaded for Read";

    dataset->putAndInsertString(DCM_PatientName,"Aarav");
    dataset->putAndInsertString(DCM_PatientID,"569");
    dataset->putAndInsertString(DCM_PatientSex,"M");
    dataset->putAndInsertString(DCM_PatientAge,"50");

    for(int i=0;i<1;i++)
    {
        DcmItem *item=NULL;
        if(dataset->findOrCreateSequenceItem(DCM_DoseReferenceSequence,item,i).good())
        {
            item->putAndInsertString(DCM_DoseReferenceNumber,"1");
            item->putAndInsertString(DCM_DoseReferenceUID,"1.2345.22");
            item->putAndInsertString(DCM_DoseReferenceType,"Cancer Tissue");
            item->putAndInsertString(DCM_DoseReferenceDescription,"goog");
            item->putAndInsertString(DCM_DeliveryMaximumDose,"20 KV");
            item->putAndInsertString(DCM_TargetPrescriptionDose,"10 KV");
            item->putAndInsertString(DCM_TargetMaximumDose,"40 KV");
        }
    }

    for(int k=0;k<1;k++)
    {
        DcmItem *itemF,*itemRB=NULL;
        if(dataset->findOrCreateSequenceItem(DCM_FractionGroupSequence,itemF,k).good())
        {
            strlist=QString::number(k+1);
            itemF->putAndInsertString(DCM_FractionGroupNumber,strlist.toStdString().c_str());
            itemF->putAndInsertString(DCM_NumberOfFractionsPlanned,strlist.toStdString().c_str());
            itemF->putAndInsertString(DCM_NumberOfBeams,strlist.toStdString().c_str());

            for(int m=0;m<1;m++)
            {
                if(itemF->findOrCreateSequenceItem(DCM_ReferencedBeamSequence,itemRB,m).good())
                {
                    strlist=QString::number(m+1);
                    itemRB->putAndInsertString(DCM_ReferencedBeamNumber,strlist.toStdString().c_str());
                    itemRB->putAndInsertString(DCM_BeamDose,strlist.toStdString().c_str());
                    itemRB->putAndInsertString(DCM_BeamMeterset,strlist.toStdString().c_str());
                }
            }
        }
    }

    QString filename1("D:/Workflow/Test images/Pro3.dcm");

    fileformat.saveFile(filename1.toStdString().c_str(),EXS_LittleEndianExplicit);
}

void MainWindow::read()
{
    DcmFileFormat fileformat;
    QString filename = ("D:/Workflow/Test images/rawImage_2.dcm");
    fileformat.loadFile(filename.toStdString().c_str());
    DcmDataset *dataset = fileformat.getDataset();

    OFString patientname,patientID,patientsex,patientage,manufacture;

    dataset->findAndGetOFString(DCM_PatientName,patientname);
    dataset->findAndGetOFString(DCM_PatientID,patientID);
    dataset->findAndGetOFString(DCM_PatientSex,patientsex);
    dataset->findAndGetOFString(DCM_PatientAge,patientage);
    dataset->findAndGetOFString(DCM_Manufacturer,manufacture);

    std::cout<<"Patient Name:"<<patientname<<std::endl;
    std::cout<<"Patient ID:"<<patientID<<std::endl;
    std::cout<<"Patient Sex:"<<patientsex<<std::endl;
    std::cout<<"Patient Age:"<<patientage<<std::endl;
    std::cout<<"Manufacture Name:"<<manufacture<<std::endl;
}
