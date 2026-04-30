#ifndef RTSTRUCT_H
#define RTSTRUCT_H

#include "itkImage.h"
#include "itkImageFileReader.h"

#include "gdcmImage.h"
#include "gdcmReader.h"
#include "gdcmFile.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmWriter.h"
#include "gdcmItem.h"
#include "gdcmTag.h"
#include "gdcmImageWriter.h"
#include "gdcmAttribute.h"
#include "gdcmImageReader.h"
#include <QDateTime>
#include <gdcmSmartPointer.h>
#include "QFileDialog"
#include "QFile"
#include "QMessageBox"
#include "QDir"

class RTStruct
{
public:
    RTStruct();

    unsigned short * buffer = NULL;
    int dimsize=512;
    int Rows2,Cols2;
    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader< Img >ReaderType1;

    QStringList SOPINSTANCEUIDList,StudyINSTANCEUIDList,SeriesINSTANCEUIDList,FrameReferenceUIDList;
    QStringList SOPINSTANCEUIDList1,SOPINSTANCEUIDList2,SOPINSTANCEUIDList3,SOPINSTANCEUIDList4,SOPINSTANCEUIDList5,SOPINSTANCEUIDList6;
    void ReadImageToDicom(const Img *image1, const size_t imSize, int j, std::string fileName);
    std::string age,PatientName,PatientID,gen,manufacture,model,DOB,StudyD,pixs,Seri,SOPINSTANCEUID,StudyINSTANCEUID,SeriesINSTANCEUID,FrameReferenceUID;
    typedef itk::Point< double, 2 > PointType;
    typedef itk::Image< unsigned short , 2>    ImageType;
    std::string StructuresetSop;
    QString strlist;
    QString framereferenceID;
    void on_readtag_clicked(QString path, QString contours12);
    QStringList SOPInstanceUIDList;
    QString contoursPoints;
    QString Dicompath;
    void inputparameters(QString contours, QString SOPInstanceUID1, QString SOPInstanceUID2, QString SOPInstanceUID3, QString SOPInstanceUID4, QString SOPInstanceUID5, QString SOPInstanceUID6, QString Requiredetails);

private slots:
    void on_RT_struct_generate_clicked();
};

#endif // RTSTRUCT_H
