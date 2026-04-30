#include "rtstruct.h"
#include "QDebug"
#include "qapplication.h"
#include "QStringList"
#include "itkMetaDataObject.h"
#include "QApplication"
#include "dcmtk/dcmrt/drtplan.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dcdeftag.h"
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dcmetinf.h"

#include "dcmtk/dcmdata/dcrlerp.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmdata/dcuid.h"           /* for UID_ defines */
#include "dcmtk/dcmjpeg/djencode.h"
#include "dcmtk/dcmdata/dcmetinf.h"
#include "dcmtk/dcmdata/dcvrda.h"
#include "dcmtk/dcmdata/dcvrtm.h"
#include "QString"

#include "QMessageBox"

#include <gdcmUIDGenerator.h>
#include <itkGDCMImageIO.h>
int counter=0;


using namespace gdcm;

RTStruct::RTStruct()
{
    //    on_readtag_clicked();
}

void RTStruct::ReadImageToDicom(const Img *image1, const size_t imSize, int j, std::string fileName)
{
    itk::MetaDataDictionary dict2;
    dict2 = image1->GetMetaDataDictionary();

    std::string Rows1;
    itk::ExposeMetaData(dict2,"0028|0010",Rows1);
    Rows2 =  std::stoi(Rows1);

    std::string Cols1;
    itk::ExposeMetaData(dict2,"0028|0011",Cols1);
    Cols2 = std::stoi(Cols1);

    itk::ExposeMetaData(dict2,"0028|0030",pixs);

    itk::ExposeMetaData(dict2,"0008|0070",manufacture);

    itk::ExposeMetaData(dict2,"0008|1030",StudyD);

    itk::ExposeMetaData(dict2,"0008|103e",Seri);

    itk::ExposeMetaData(dict2,"0008|1090",model);

    itk::ExposeMetaData(dict2,"0010|0010",PatientName);

    itk::ExposeMetaData(dict2,"0010|0020",PatientID);

    itk::ExposeMetaData(dict2,"0010|1010",age);

    itk::ExposeMetaData(dict2,"0010|0030",DOB);

    itk::ExposeMetaData(dict2,"0008|103e",Seri);

    itk::ExposeMetaData(dict2,"0008|0018",SOPINSTANCEUID);
    SOPINSTANCEUIDList.append(SOPINSTANCEUID.c_str());

    if(j==0)
    {
        itk::ExposeMetaData(dict2,"0020|000d",StudyINSTANCEUID);
        StudyINSTANCEUIDList.append(StudyINSTANCEUID.c_str());

        itk::ExposeMetaData(dict2,"0020|000e",SeriesINSTANCEUID);
        SeriesINSTANCEUIDList.append(SeriesINSTANCEUID.c_str());

        itk::ExposeMetaData(dict2,"0020|0052",FrameReferenceUID);
        FrameReferenceUIDList.append(FrameReferenceUID.c_str());
    }
    itk::ExposeMetaData(dict2,"0010|0030",DOB);

    itk::ExposeMetaData(dict2,"0010|0040",gen);

    //qDebug()<<"Exit"<<j;
}

void RTStruct::on_readtag_clicked(QString path, QString contours12,QString sliceNo)
{

    //    QString path ="D:\\writeStruct\\CT";
    if(path == 0||path == "")
    {
        //        QMessageBox::critical(this,"Error","No path found !!");
    }

    QDir dir(path);
    QStringList filters;
    QStringList dcmList;

    if(!dir.exists())
    {
        //qDebug()<<"Directory doesnot exit---7";
        //        QMessageBox::critical(this,"Error","Directory does not exists !!");
    }

    filters << "*.dcm" ;
    dir.setNameFilters(filters);
    dcmList = dir.entryList(filters);


    qDebug()<<"No. of dicom files : "<<dcmList.length();

    qDebug()<<"path"<<path;

    // contoursPoints=contours12;

    QStringList slist;
    slist = contours12.split(",");


    sliceNOcbct= sliceNo.split(",");

    qDebug()<<"sliceNOcbct length"<<sliceNOcbct<<sliceNOcbct.length();

    for(int i=0;i<slist.length();i++)
    {
        QString val1=slist.at(i);
        cpList.append(val1.toDouble());
    }

    //qDebug()<<"cplist"<<cpList;


    Dicompath = path;

    if(dcmList.length()==0){
        //        QMessageBox::warning(this,"Error","No images found..");
        return;
    }

    qDebug()<<"Enter val";
    buffer = new unsigned short[dimsize*dimsize*dcmList.length()];

    std::string fileNameCPP;

    for(int i=0;i<dcmList.length();i++)
    {
       fileNameCPP = path.toStdString() + "\\Slice" + std::to_string(i+1) + ".dcm";
        //QString filena=dcmList[i];
        //qDebug()<<"File name"<<filena;
        //fileNameCPP=filena.toStdString();
        //qDebug()<<"After File name"<<fileNameCPP;
        ReaderType1::Pointer reader1;        
        reader1 = ReaderType1::New();        
        reader1->SetFileName(fileNameCPP);        
        typedef itk::GDCMImageIO  ImageType;
        ImageType::Pointer gdcmImage = ImageType::New();        
        reader1->SetImageIO( gdcmImage);
        reader1->SetFileName(fileNameCPP);
        //std::cout<<"fileNameCPP..."<<fileNameCPP<<std::endl;

        //        reader->SetDataScalarTypeToShort();
        //        reader->SetMemoryRowOrderToFileNative();

        try
        {
            reader1->Update();
            std::cout<<"fileNameCPP..."<<fileNameCPP<<std::endl;
        }
        catch(...)
        {
            qDebug()<<"Exception  reading dicom files";
            //            QMessageBox::warning(this,"Error","Problems in reading Dicom images");
            return;

        }

        const Img * image= reader1->GetOutput();

        const unsigned short *pixelBuffer = image->GetBufferPointer();

        this->ReadImageToDicom(image,dimsize,i,fileNameCPP);

        for(int j=0;j<dimsize*dimsize;++j)
        {
            buffer[i*dimsize*dimsize+j]=pixelBuffer[j];

        }

    }

    on_RT_struct_generate_clicked();
}

void RTStruct::on_RT_struct_generate_clicked()
{
    //qDebug()<<"Dicompath"<<Dicompath;
    QString patientname=PatientName.c_str();
    QString Patientid=PatientID.c_str();
    //    QString Dicompath = "D:\\Test";
    QString gender= gen.c_str();
    QString dOb=DOB.c_str();
    QString Age=age.c_str();
    QString StudyDes=StudyD.c_str();
    QString SeriDes=Seri.c_str();
    QString Manufacture=manufacture.c_str();
    QString Model=model.c_str();
    QString version="1.3.7";
    //    QString contoursPoints= "1,2.3";

    QString StudyINSTANCEuid = StudyINSTANCEUIDList[0];
    QString SeriesINSTANCEuid= SeriesINSTANCEUIDList[0];
    QString FrameReferenceuid= FrameReferenceUIDList[0];

    //    std::cout<<"uids"<<StudyINSTANCEuid<<SeriesINSTANCEuid<<FrameReferenceuid;

    char uid[100];

    DcmFileFormat fileformat;
    DcmRepresentationParameter *params;
    DcmDataset *dataset = fileformat.getDataset();

    //    QString contours="2,3,4,5";
    typedef itk::Point< double, 2 > PointType;

    QString dicomDate = QString(QDate::currentDate().toString("yyyyMMdd"));
    QString dicomTime = QString(QTime::currentTime().toString("hhmmss.zzzzzz"));

    QString t1 = "RS.";
    QString t2 = ".dcm";
    QString dicomfile2 = t1+dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT)+t2;

    QString dir = Dicompath;

    QString Roicolor1="255\\128\\128";
    QString Roicolor2="255\\255\\128";
    QString Roicolor3="255\\0\\0";

    QStringList Roicolor;

    Roicolor.append(Roicolor1);
    Roicolor.append(Roicolor2);
    Roicolor.append(Roicolor3);
    QString fileName1= dir+"//"+dicomfile2;

    //qDebug()<<"contour"<<contours;

    QList<QList<double>> ContourFinalList;
    //    QList<double> cpList1;
    //    QList<double> cpList2;

    // QStringList ContourList= contours.split(",");
    //qDebug()<<"ContourList"<<ContourList;

    //    cpList.append(124.674);
    //    cpList.append(132.593);
    //    cpList.append(1.58101e-322);
    //    cpList.append(172.003);
    //    cpList.append(132.593);
    //    cpList.append(1.58101e-322);
    //    cpList.append(172.003);
    //    cpList.append(157.454);
    //    cpList.append(1.58101e-322);
    //    cpList.append(124.674);
    //    cpList.append(157.454);
    //    cpList.append(1.58101e-322);
    //    cpList.append(124.674);
    //    cpList.append(132.593);
    //    cpList.append(1.58101e-322);

    //    cpList1.append(127.805);
    //    cpList1.append(125.595);
    //    cpList1.append(1.58101e-322);
    //    cpList1.append(155.889);
    //    cpList1.append(125.595);
    //    cpList1.append(1.58101e-322);
    //    cpList1.append(155.889);
    //    cpList1.append(160.032);
    //    cpList1.append(1.58101e-322);
    //    cpList1.append(127.805);
    //    cpList1.append(160.032);
    //    cpList1.append(1.58101e-322);
    //    cpList1.append(127.805);
    //    cpList1.append(125.595);
    //    cpList1.append(1.58101e-322);

    //    cpList2.append(145.484);
    //    cpList2.append(124.03);
    //    cpList2.append(1.58101e-322);
    //    cpList2.append(167.951);
    //    cpList2.append(124.03);
    //    cpList2.append(1.58101e-322);
    //    cpList2.append(167.951);
    //    cpList2.append(137.289);
    //    cpList2.append(1.58101e-322);
    //    cpList2.append(145.484);
    //    cpList2.append(137.289);
    //    cpList2.append(1.58101e-322);
    //    cpList2.append(145.484);
    //    cpList2.append(124.03);
    //    cpList2.append(1.58101e-322);

    ContourFinalList.append(cpList);
    //    ContourFinalList.append(cpList1);
    //    ContourFinalList.append(cpList2);

    QString studyID=StudyINSTANCEuid;
    QString seriesID=SeriesINSTANCEuid;

    //qDebug()<<"finalcontour"<<ContourFinalList<<ContourFinalList.length();

    dataset->putAndInsertString(DCM_SOPClassUID, UID_RTStructureSetStorage);
    StructuresetSop = dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT);
    StructuresetSeries = dcmGenerateUniqueIdentifier(uid, SITE_SERIES_UID_ROOT);
    dataset->putAndInsertString(DCM_SOPInstanceUID, StructuresetSop.c_str());
    dataset->putAndInsertString(DCM_StudyInstanceUID, studyID.toStdString().c_str());
    dataset->putAndInsertString(DCM_SeriesInstanceUID, StructuresetSeries.c_str());
    //    dataset->putAndInsertString(DCM_FrameOfReferenceUID,dcmGenerateUniqueIdentifier(uid,SITE_UID_ROOT));
    dataset->putAndInsertString(DCM_Modality,"RTSTRUCT");

    dataset->putAndInsertString(DCM_StudyDescription,StudyDes.toStdString().c_str());

    dataset->putAndInsertString(DCM_PatientName,patientname.toStdString().c_str());

    dataset->putAndInsertString(DCM_PatientID,Patientid.toStdString().c_str());

    //    QString gender;
    //    gen="Female";

    //    if(gen.c_str()=="Female")
    //        gender="F";
    //    else
    //        gender="M";
    QString slicestr=sliceNOcbct[0];
    int slicenum=slicestr.toInt()-1;
    qDebug()<<"slice number"<<slicenum;
    dataset->putAndInsertString(DCM_PatientSex, gender.toStdString().c_str());

    //    DOB="10-08-1996";

    dataset->putAndInsertString(DCM_PatientBirthDate,dOb.toStdString().c_str());

    //    age="24";

    dataset->putAndInsertString(DCM_PatientAge,Age.toStdString().c_str());
    dataset->putAndInsertString(DCM_SpecificCharacterSet,"ISO_IR 100");
    dataset->putAndInsertString(DCM_SamplesPerPixel,"1");
    dataset->putAndInsertString(DCM_PhotometricInterpretation,"MONOCHROME2");
    dataset->putAndInsertString(DCM_Rows,"512");
    dataset->putAndInsertString(DCM_Columns,"512");
    dataset->putAndInsertString(DCM_BitsAllocated,"16");
    dataset->putAndInsertString(DCM_BitsStored,"16");
    dataset->putAndInsertString(DCM_HighBit,"15");
    dataset->putAndInsertString(DCM_PixelRepresentation,"0");
    dataset->putAndInsertString(DCM_SmallestImagePixelValue,"0");
    dataset->putAndInsertString(DCM_LargestImagePixelValue,"256");

    dataset->putAndInsertString(DCM_ManufacturerModelName,Model.toStdString().c_str());
    dataset->putAndInsertString(DCM_Manufacturer,Manufacture.toStdString().c_str());

    dataset->putAndInsertString(DCM_StudyDescription,StudyDes.toStdString().c_str());
    dataset->putAndInsertString(DCM_SoftwareVersions,version.toStdString().c_str());
    dataset->putAndInsertString(DCM_InstanceCreationDate,dicomDate.toStdString().c_str());
    dataset->putAndInsertString(DCM_InstanceCreationTime,dicomTime.toStdString().c_str());
    dataset->putAndInsertString(DCM_SeriesDescription,SeriDes.toStdString().c_str());

    dataset->putAndInsertString(DCM_StructureSetLabel,"123");
    dataset->putAndInsertString(DCM_StructureSetDate,dicomDate.toStdString().c_str());
    dataset->putAndInsertString(DCM_StructureSetTime,dicomTime.toStdString().c_str());

    DcmItem *RFR,*StusyIn,*SeriesIns,*Cts,*SSRS,*RROS,*BS=NULL;
    //    qDebug()<<"SOPINSTANCEUIDList"<<SOPInstanceUIDList;
    if(dataset->findOrCreateSequenceItem(DCM_ReferencedFrameOfReferenceSequence,RFR).good())
    {
        framereferenceID = FrameReferenceuid;
        RFR->putAndInsertString(DCM_FrameOfReferenceUID,framereferenceID.toStdString().c_str());
        if(RFR->findOrCreateSequenceItem(DCM_RTReferencedStudySequence,StusyIn).good())
        {
            StusyIn->putAndInsertString(DCM_ReferencedSOPClassUID, UID_RETIRED_DetachedStudyManagementSOPClass);
            QString SOPINS = StudyINSTANCEuid;
            StusyIn->putAndInsertString(DCM_ReferencedSOPInstanceUID,SOPINS.toStdString().c_str());

            if(StusyIn->findOrCreateSequenceItem(DCM_RTReferencedSeriesSequence,SeriesIns).good())
            {
                QString SeriesINS = SeriesINSTANCEuid;
                SeriesIns->putAndInsertString(DCM_SeriesInstanceUID,SeriesINS.toStdString().c_str());

                int p=-1;
                for(int R=0;R<SOPINSTANCEUIDList.length();R++)
                {
                    p++;
                    if(SeriesIns->findOrCreateSequenceItem(DCM_ContourImageSequence,Cts,p).good())
                    {
                        QString CTINS = SOPINSTANCEUIDList[R];
                        Cts->putAndInsertString(DCM_ReferencedSOPClassUID,UID_CTImageStorage);
                        Cts->putAndInsertString(DCM_ReferencedSOPInstanceUID,CTINS.toStdString().c_str());
                    }
                }
            }
        }
    }

    //qDebug()<<"List" <<ContourFinalList.length();
    for(int i=0;i<ContourFinalList.length();i++){
        //qDebug()<<"CPFinalList1"<<i;
        // //  qDebug()<<"SSequence"<<p<<i;
        if(dataset->findOrCreateSequenceItem(DCM_StructureSetROISequence,SSRS,i).good()){
            //            qDebug()<<"good";
            SSRS->putAndInsertString(DCM_ROINumber,QString::number(i+1).toStdString().c_str());
            SSRS->putAndInsertString(DCM_ReferencedFrameOfReferenceUID,framereferenceID.toStdString().c_str());
            //            SSRS->putAndInsertString(DCM_ReferencedFrameOfReferenceUID,dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));
            QString ROIName ="Anatomy";
            ROIName = ROIName+QString::number(i+1).toStdString().c_str();
            SSRS->putAndInsertString(DCM_ROIName,ROIName.toStdString().c_str());
        }
    }

    for(int j=0;j<ContourFinalList.length();j++){
        //        qDebug()<<"good11";
        //qDebug()<<"CPFinalList2"<<j;
        if(dataset->findOrCreateSequenceItem(DCM_RTROIObservationsSequence,RROS,j).good()){
            RROS->putAndInsertString(DCM_ObservationNumber,QString::number(j+1).toStdString().c_str());
            RROS->putAndInsertString(DCM_ReferencedROINumber,QString::number(j+1).toStdString().c_str());
            RROS->putAndInsertString(DCM_RTROIInterpretedType,"ORGAN");
        }
    }

    for(int C1=0;C1<ContourFinalList.length();C1++){
        if(dataset->findOrCreateSequenceItem(DCM_ROIContourSequence,BS,C1).good()){
            //               qDebug()<<"good11  bbb"<<ContourFinalList.length();
            QString Roicolorlist=Roicolor[C1];
            BS->putAndInsertString(DCM_ROIDisplayColor,Roicolorlist.toStdString().c_str());
            BS->putAndInsertString(DCM_ReferencedROINumber,QString::number(C1+1).toStdString().c_str());
            DcmItem *CS;
            for(int c=0;c<sliceNOcbct.length();c++){
                if(BS->findOrCreateSequenceItem(DCM_ContourSequence,CS,c).good()){
                    CS->putAndInsertString(DCM_ContourGeometricType,"CLOSED_PLANAR");
                    CS->putAndInsertString(DCM_ContourOffsetVector,"0.0\\0.0\\0.0");
                    int ConPts = ContourFinalList[C1].length()/3;
                    //                    int ConPts = ContourFinalList.length();
                    CS->putAndInsertString(DCM_NumberOfContourPoints,QString::number(ConPts).toStdString().c_str());
                    QString str;
                    for(int i3=0; i3<ContourFinalList[C1].size();i3++){
                        if(i3==ContourFinalList[C1].size()-1){
                            str+=QString::number(ContourFinalList.at(C1).at(i3));}
                        else{
                            str+=QString::number(ContourFinalList.at(C1).at(i3))+"\\";
                        }
                    }
                    CS->putAndInsertString(DCM_ContourData,str.toStdString().c_str());
                    DcmItem *CIS;
                    for(int c1=0;c1<1;c1++){
                        if(CS->findOrCreateSequenceItem(DCM_ContourImageSequence,CIS,c1).good()){
                            CIS->putAndInsertString(DCM_ReferencedSOPClassUID,UID_CTImageStorage);
                            QString SOPINS = SOPINSTANCEUIDList[slicenum+counter];
                            CIS->putAndInsertString(DCM_ReferencedSOPInstanceUID,SOPINS.toStdString().c_str());
                        }
                        counter++;
                    }
                }
            }
        }
    }

    dataset->putAndInsertString(DCM_PixelData,"0");

    OFCondition status;
    status = dataset->chooseRepresentation(EXS_LittleEndianExplicit, params);
    QString pathfile="D:\\writeStruct\\10-01-2023";
    QString dicomfile =pathfile+"//"+dicomfile2;
    //QString dicomfile =fileName1;


    qDebug()<<"Status good"<<status.good();

    if(status.good()){
        fileformat.saveFile(dicomfile.toStdString().c_str(), EXS_LittleEndianExplicit);
        qDebug()<<"File saved";

        qApp->processEvents();

    }
    else
    {
        fileformat.saveFile("test.dcm", EXS_LittleEndianExplicit);
        qDebug()<<"File not saved";
        qApp->processEvents();
    }
}

