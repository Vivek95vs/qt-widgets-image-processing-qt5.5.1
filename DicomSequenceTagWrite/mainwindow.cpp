#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <gdcmUIDGenerator.h>
#include <itkCommand.h>
#include "itkImageFileWriter.h"
#include <itkGDCMImageIO.h>
#include "itkMetaDataObject.h"
#include <itkMetaDataDictionary.h>
#include "itkImportImageFilter.h"
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

void MainWindow::on_pushButton_clicked()
{

    qDebug()<<"hi, SaveImageToDicom1";
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.raw",QDir::currentPath());
//    QString filename="D:\\DRR Raw 3072_2906\\Image_1.raw";
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short* image=new unsigned short[w*h];
    fread(image,1,w*h*sizeof(unsigned short),Img);
    unsigned short* buffer=new unsigned short[w*h];
    buffer=image;

    //    //Create new Dicom Image


    qDebug()<<"Data----1";
    gdcm::ImageWriter writer;
    gdcm::Image &image1 = writer.GetImage();
    image1.SetNumberOfDimensions(2);

    qDebug()<<"Data----2";

    //Create Sequence
    gdcm::File &file = writer.GetFile();
    gdcm::DataSet &ds = file.GetDataSet();

    //    //UID Sequence
    gdcm::UIDGenerator suid;
    //    StudyInstanceUUID1 =suid.Generate();

    gdcm::Attribute<0x0010,0x0010,VR::PN,VM::VM1> PatientName = {"PUSHPA P"};
    ds.Insert( PatientName.GetAsDataElement() );

    gdcm::Attribute<0x0010,0x0020,VR::LO,VM::VM1> PatientID = {"RT202310A01"};
    ds.Insert( PatientID.GetAsDataElement() );

        qDebug()<<"Data----3";

//    QString date_string_on_db = patientAge;
//    QStringList datelist2=date_string_on_db.split(" ");
//    QStringList datelist = datelist2[0].split("-");

//    if(da)
//    qDebug()<<"udgfiwegfge::CHECKKKK"<<datelist;
//    QString appendDate= datelist[2]+datelist[1]+datelist[0];

//    qDebug()<<"appendDate::CHECKKKK"<<appendDate;
//    QString DOB= appendDate.toStdString().c_str();
//    DOB.resize(10);

    gdcm::Attribute<0x0008,0x0064,VR::CS,VM::VM1> ConversionType = {""};
    ds.Insert( ConversionType.GetAsDataElement() );

//    QStringList strDOB = patientAge.split("-");
//    QString dob;
//    if(strDOB.length()>=2)
//       dob  = QString(strDOB[2]).mid(0,4)+strDOB[1]+strDOB[0];
//    else
//       dob = "";


    gdcm::Attribute<0x0010,0x0030,VR::DA,VM::VM1> PatBirthDate = {"19950921"};
    ds.Insert( PatBirthDate.GetAsDataElement() );

        qDebug()<<"Data----4";
//    qDebug()<<"PatientGenderyes"<<patientGender;

//    patientGender="FEMALE";

//    if(patientGender.trimmed()=="MALE" || patientGender.trimmed()=="Male")
//        patientGender="M";
//    else if(patientGender.trimmed()=="FEMALE" || patientGender.trimmed()=="Female")
//        patientGender="F";
//    else
//        patientGender="O";


    gdcm::Attribute<0x0010,0x0040,VR::CS,VM::VM1> PatientSex = {"F"};
    ds.Insert( PatientSex.GetAsDataElement() );

    gdcm::Attribute<0x0010,0x1010,VR::AS,VM::VM1> PatientAge = {"45"};
    ds.Insert( PatientAge.GetAsDataElement() );

    gdcm::Attribute<0x0010,0x1020,VR::DS,VM::VM1> PatientSize = {};
    ds.Insert( PatientSize.GetAsDataElement() );

        qDebug()<<"Data----5";

////    //    gdcm::Attribute<0x0010,0x2297,VR::PN,VM::VM1> ResponsiblePerson = {""};
////    //   ds.Insert( ResponsiblePerson.GetAsDataElement() );

////    //    gdcm::Attribute<0x0010,0x2299,VR::LO,VM::VM1> ResponsibleOrganization = {""};
////    //    ds.Insert( ResponsibleOrganization.GetAsDataElement() );

    gdcm::Attribute<0x0020,0x000D,VR::UI,VM::VM1> StudyUID = {"1C"};
    ds.Insert( StudyUID.GetAsDataElement() );

    QString date = QString(QDate::currentDate().toString("yyyyMMdd"));
    QString time = QString(QTime::currentTime().toString("hhmmss.zzzzzz"));

    gdcm::Attribute<0x0008,0x0020,VR::DA,VM::VM1> StudyDate = {date.toStdString().c_str()};
    ds.Insert( StudyDate.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0030,VR::TM,VM::VM1> StudyTime = {time.toStdString().c_str()};
    ds.Insert( StudyTime.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0090,VR::PN,VM::VM1> PhysicianName = {"DR. VENKAT"};
    ds.Insert( PhysicianName.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0022,VR::DA,VM::VM1> AcquisitionDate = {date.toStdString().c_str()};
    ds.Insert( AcquisitionDate.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0032,VR::TM,VM::VM1> AcquisitionTime = {time.toStdString().c_str()};
    ds.Insert( AcquisitionTime.GetAsDataElement() );

////    if(date.length()>=8)
////        AcqDate = date.mid(6,2)+"-"+date.mid(4,2)+"-"+date.mid(0,4);
////    else
////        AcqDate="";

////    if(time.length()>=8)
////        AcqTime = time.mid(0,2)+":"+time.mid(2,2)+":"+time.mid(4,2);
////    else
////        AcqTime="";
///

//    QString fracno;

//    if(FractionNumber.toInt()<10)
//        fracno = "0"+FractionNumber;

//    QString beamNumberStr = "0";

//    if(BeamNumber<10)
//        beamNumberStr = beamNumberStr+QString::number(BeamNumber);

//    QString studyiD = StudyID+QString::number(fGroup)+fracno+beamNumberStr;

    gdcm::Attribute<0x0020,0x0010,VR::SH,VM::VM1> studyID = {"2708"};
    ds.Insert( studyID.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x1030,VR::LO,VM::VM1> StudyDescriptionN = {"IMG"};
    ds.Insert(StudyDescriptionN.GetAsDataElement());

    gdcm::Attribute<0x0008,0x103e,VR::LO,VM::VM1> SeriesDescriptionN = {"3"};
    ds.Insert(SeriesDescriptionN.GetAsDataElement());

    gdcm::Attribute<0x0008,0x0050,VR::SH,VM::VM1> AccessionNum = {"1"};
    ds.Insert( AccessionNum.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0060,VR::CS,VM::VM1> Modality = {"RTIMAGE"};
    ds.Insert( Modality.GetAsDataElement() );

    gdcm::Attribute<0x0018,0x1000,VR::LO,VM::VM1> SerialNumber = {"985518756"}; //"987654321"
    ds.Insert( SerialNumber.GetAsDataElement() );

        qDebug()<<"Data----6";

//    if(radProjCount==1 || (stereoProjCount1==1 && stereoProjCount2==0)|| (stereoProjCount2==1 && stereoProjCount1==0))
        QString commonSeriesUID = suid.Generate();

    gdcm::Attribute<0x0020,0x000E,VR::UI,VM::VM1> SeriesUID = {commonSeriesUID.toStdString().c_str()/*suid.Generate()*/};  //SeriesInstanceUID.toStdString().c_str()
    ds.Insert( SeriesUID.GetAsDataElement() );
    gdcm::Attribute<0x0020,0x0011,VR::IS,VM::VM1> SeriesNum = {/*1*/};
    ds.Insert( SeriesNum.GetAsDataElement() );

        qDebug()<<"Data----7";

    gdcm::Attribute<0x0008,0x1070,VR::PN,VM::VM1> OperatorName = {"user"};
    ds.Insert( OperatorName.GetAsDataElement() );

    gdcm::Attribute<0x0020,0x0052,VR::UI,VM::VM1> FrameOfReferenceUID = {suid.Generate()};
    ds.Insert( FrameOfReferenceUID.GetAsDataElement() );

            qDebug()<<"Data----8";

    gdcm::Attribute<0x0020,0x1040,VR::LO,VM::VM1> PositionReferenceIndicator = {""};
    ds.Insert( PositionReferenceIndicator.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0070,VR::LO,VM::VM1> Manufacturers = {"PANACEA MEDICALS"};
    ds.Insert( Manufacturers.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0080,VR::LO,VM::VM1> InstitutionName = {"Hospital Name"};
    ds.Insert( InstitutionName.GetAsDataElement() );

                qDebug()<<"Data----9";
    gdcm::Attribute<0x0008,0x1090,VR::LO,VM::VM1> ManufacturerModelNames = {"Panacea"};
    ds.Insert( ManufacturerModelNames.GetAsDataElement() );

    gdcm::Attribute<0x0018,0x1020,VR::LO,VM::VM1> SoftwareVersions = {"1.01"};
    ds.Insert( SoftwareVersions.GetAsDataElement() );

////    //    gdcm::Attribute<0x0028,0x0120,VR::US,VM::VM1> PixelPadding = {0};
////    //    ds.Insert( PixelPadding.GetAsDataElement() );

    gdcm::Attribute<0x0020,0x0013,VR::IS,VM::VM1> InstanceNumber = {/*1*/};
    ds.Insert( InstanceNumber.GetAsDataElement() );

                qDebug()<<"Data----10";
    gdcm::Attribute<0x0020,0x0020,VR::CS,VM::VM2> PatOrientation = {""};
    ds.Insert( PatOrientation.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0023,VR::DA,VM::VM1> ContentDate = {date.toStdString().c_str()};
    ds.Insert( ContentDate.GetAsDataElement() );

    gdcm::Attribute<0x0008,0x0033,VR::TM,VM::VM1> ContentTime = {time.toStStdString().c_str()};
    ds.Insert( ContentTime.GetAsDataElement() );

                qDebug()<<"Data----11";

////    gdcm::Attribute<0x0008,0x0008,VR::CS,VM::VM4> ImageType = {"ORIGININAL","PRIMARY","SIMULATOR","SMX_FIELD"};
        gdcm::Attribute<0x0008,0x0008,VR::CS,VM::VM3> ImageType = {"ORIGININAL","PRIMARY","RADIOGRAPH"};
        ds.Insert( ImageType.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x0002,VR::US,VM::VM1> SamplesPerPixel = {1};
    ds.Insert( SamplesPerPixel.GetAsDataElement() );

        gdcm::Attribute<0x0028,0x0004,VR::CS,VM::VM1> PhotometricInterpretation = {"MONOCHROME2"};
        ds.Insert( PhotometricInterpretation.GetAsDataElement() );

          size_t  radSize[2];

          radSize[0]=3072;
          radSize[1]=3072;

        int imSize1 = radSize[0];
////    qDebug()<<"imSize"<<imSize;
    gdcm::Attribute<0x0028,0x0010,VR::US,VM::VM1> Rows = {imSize1};
    ds.Insert( Rows.GetAsDataElement() );

    gdcm::Attribute<0x0028,0x0011,VR::US,VM::VM1> Coloums = {imSize1};
    ds.Insert( Coloums.GetAsDataElement() );

                qDebug()<<"Data----12";

    gdcm::Attribute<0x0028,0x0030,VR::DS,VM::VM2> ImgerPixelSpacing = {0.139,0.139};
    //    gdcm::Attribute<0x0028,0x0030,VR::DS,VM::VM2> ImgerPixelSpacing = {imaginPixelSpacing,imaginPixelSpacing};
    ds.Insert(ImgerPixelSpacing.GetAsDataElement());

        gdcm::Attribute<0x0028,0x0100,VR::US,VM::VM1> BitsAllocated = {16};
        ds.Insert( BitsAllocated.GetAsDataElement() );

        gdcm::Attribute<0x0028,0x0101,VR::US,VM::VM1> BitsStored = {16};
        ds.Insert( BitsStored.GetAsDataElement() );

        gdcm::Attribute<0x0028,0x0102,VR::US,VM::VM1> HighBit = {15};
        ds.Insert( HighBit.GetAsDataElement() );

        gdcm::Attribute<0x0028,0x0103,VR::US,VM::VM1> PixelRepresentation = {0000};
        ds.Insert( PixelRepresentation.GetAsDataElement());

        gdcm::Attribute<0x0028,0x0006,VR::US,VM::VM1> PlanarConfiguration = {};
        ds.Insert( PlanarConfiguration.GetAsDataElement());

        gdcm::Attribute<0x0028,0x0034,VR::IS,VM::VM2> PixelAspectRatio = {1,1};
        ds.Insert( PixelAspectRatio.GetAsDataElement() );

        gdcm::Attribute<0x0028,0x1040,VR::CS,VM::VM1> PixelIntensityRelationship = {"LIN"};
         ds.Insert( PixelIntensityRelationship.GetAsDataElement() );

        gdcm::Attribute<0x0028,0x1041,VR::SS,VM::VM1> PixelIntensityRelationshipSign = {1};
        ds.Insert( PixelIntensityRelationshipSign.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x0002,VR::SH,VM::VM1> RTImageLabel = {"Beam"};
    ds.Insert( RTImageLabel.GetAsDataElement() );

                qDebug()<<"Data----13";

////    gdcm::Attribute<0x3002,0x0004,VR::ST,VM::VM1> RTImageDescription = {"IMG"};
////    ds.Insert( RTImageDescription.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x000A,VR::CS,VM::VM1> ReportedValuesOrigin = {"OPERATOR"};
    ds.Insert( ReportedValuesOrigin.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x000C,VR::CS,VM::VM1> RTImagePlane = {"NORMAL"};
    ds.Insert( RTImagePlane.GetAsDataElement() );

                qDebug()<<"Data----14";

//    if(curDMode==1 || (curDMode==3 && stereoProjCount1==1))
//    {
    gdcm::Attribute<0x3002,0x000D,VR::DS,VM::VM3> XRayImageReceptorTranslation = {0.1,0,-350};
    //    gdcm::Attribute<0x3002,0x000D,VR::DS,VM::VM3> XRayImageReceptorTranslation = {detectorxShift+imagerXCurrentPosition,detectoryShift+imagerYCurrentPosition};
    ds.Insert( XRayImageReceptorTranslation.GetAsDataElement() );
//    }

                qDebug()<<"Data----15";
//    else if (curDMode==2 || (curDMode==3 && stereoProjCount2==1))
//    {
//        gdcm::Attribute<0x3002,0x000D,VR::DS,VM::VM3> XRayImageReceptorTranslation = {detector2xShift+kV2xShift,detector2yShift+kV2yShift,-350};
        //    gdcm::Attribute<0x3002,0x000D,VR::DS,VM::VM3> XRayImageReceptorTranslation = {detectorxShift+imagerXCurrentPosition,detectoryShift+imagerYCurrentPosition};
//        ds.Insert( XRayImageReceptorTranslation.GetAsDataElement() );
//    }

    gdcm::Attribute<0x3002,0x000E,VR::DS,VM::VM1> XRayImageReceptorAngle = {0};
    ds.Insert( XRayImageReceptorAngle.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x0010,VR::DS,VM::VM6> RTImageOrientation = {};
    ds.Insert( RTImageOrientation.GetAsDataElement() );

                qDebug()<<"Data----16";

////    int bining = 1;
////    if(imSize==3072)
////        bining = 1;
////    else if(imSize==1536)
////        bining = 2;
////    float pixspacing = imaginPixelSpacing;

//    detectorPixelPitch[0]*FAD/FID


    float pixSpacing[2];


    double FAD,FID,detectorPixelPitch[2];
    FAD=921;
    FID=1696;
    detectorPixelPitch[0]=0.139;
    detectorPixelPitch[1]=0.139;
    pixSpacing[0]= detectorPixelPitch[0]*FAD/FID;
    pixSpacing[1]= detectorPixelPitch[1]*FAD/FID;

    float isocentre[2];

    isocentre[0] = radSize[0]/2*pixSpacing[0];
    isocentre[1] = radSize[1]/2*pixSpacing[1];

     qDebug()<<"Data----17"<<pixSpacing[0]<<pixSpacing[1]<<isocentre[0]<<isocentre[1];


////    //   gdcm::Attribute<0x3002,0x0011,VR::DS,VM::VM2> ImagePlanePixelSpacing = {float(0.1),float(0.1)};
////    //ds.Insert( ImagePlanePixelSpacing.GetAsDataElement() );

////    qDebug()<<"radSizeeesssss  "<<radSize<<pixspacing<<isoCentreY;

    float RTimagePosX,RTimagePosY;

    RTimagePosX = -isocentre[0];
    RTimagePosY = (radSize[1]*pixSpacing[1]) - isocentre[1];

                    qDebug()<<"Data----18";

    gdcm::Attribute<0x3002,0x0012,VR::DS,VM::VM2> RTImagePosition = {RTimagePosX,RTimagePosY};
    ds.Insert( RTImagePosition.GetAsDataElement() );
    gdcm::Attribute<0x3002,0x0020,VR::SH,VM::VM1> RadiationMachineName = {"LINAC"};
    ds.Insert( RadiationMachineName.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x0022,VR::DS,VM::VM1> RadiationMachineSAD = {FAD};
    ds.Insert( RadiationMachineSAD.GetAsDataElement() );

////    //    gdcm::Attribute<0x3002,0x0024,VR::DS,VM::VM1> RadiationMachineSSD = {};
////    //    ds.Insert( RadiationMachineSSD.GetAsDataElement() );

    gdcm::Attribute<0x3002,0x0026,VR::DS,VM::VM1> RTImageSID = {FID};
    ds.Insert( RTImageSID.GetAsDataElement() );


                    qDebug()<<"Data----19";
////    //    gdcm::Attribute<0x3002,0x0028,VR::DS,VM::VM1> SourceToReferenceObjectDistance = {};
////    //    ds.Insert( SourceToReferenceObjectDistance.GetAsDataElement() );

    gdcm::MediaStorage msUID = gdcm::MediaStorage::RTImageStorage;
    std::string h1=msUID.GetString();
    gdcm::Attribute<0x0008,0x0016,VR::UI,VM::VM1> SOPClassUID = {h1};
    ds.Insert( SOPClassUID.GetAsDataElement() );

    gdcm::UIDGenerator gen;
    gdcm::Attribute<0x0008,0x0018,VR::UI,VM::VM1> sOPInstanceUID = {gen.Generate()};
    ds.Insert( sOPInstanceUID.GetAsDataElement() );

                    qDebug()<<"Data----20";

////    /*********SEQUENCE-START*********/
    gdcm::SmartPointer<gdcm::SequenceOfItems> ReferencedRTPlanSequence = new gdcm::SequenceOfItems();
    ReferencedRTPlanSequence->SetLengthToUndefined();

    gdcm::MediaStorage ms1 = gdcm::MediaStorage::RTImageStorage;
    std::string k=ms1.GetString();
    gdcm::Attribute<0x0008,0x1150,VR::UI,VM::VM1> ReferencedSOPClassUID = {k};
    gdcm::DataElement rfID = ReferencedSOPClassUID.GetAsDataElement();

    gdcm::Attribute<0x0008,0x1155,VR::UI,VM::VM1> ReferencedSOPInstanceUID = {suid.Generate()};
    gdcm::DataElement refSOPID = ReferencedSOPInstanceUID.GetAsDataElement();

    gdcm::Item ReferencedRTPlanItem;
    gdcm::DataSet &dsReferencedRTPlan = ReferencedRTPlanItem.GetNestedDataSet();
    dsReferencedRTPlan.Insert( rfID );
    dsReferencedRTPlan.Insert(refSOPID);

    ReferencedRTPlanSequence->AddItem(ReferencedRTPlanItem);

    gdcm::DataElement desReferencedRTPlan( gdcm::Tag(0x300C,0x0002) );
    desReferencedRTPlan.SetVR(gdcm::VR::SQ);
    desReferencedRTPlan.SetValue(*ReferencedRTPlanSequence);
    desReferencedRTPlan.SetVLToUndefined();
    ds.Insert(desReferencedRTPlan);

                    qDebug()<<"Data----21";
////    /*********SEQUENCE-END*********/

    gdcm::Attribute<0x0018,0x0060,VR::DS,VM::VM1> KVP = {80};
    ds.Insert( KVP.GetAsDataElement() );

    gdcm::Attribute<0x0018,0x1151,VR::IS,VM::VM1> XRayTubeCurrent = {12};
    ds.Insert( XRayTubeCurrent.GetAsDataElement() );

    gdcm::Attribute<0x0018,0x1150,VR::IS,VM::VM1> ExposureTime = {60};
    ds.Insert( ExposureTime.GetAsDataElement() );

                    qDebug()<<"Data----22";
////    /*********SEQUENCE-START*********/

//    gdcm::SmartPointer<gdcm::SequenceOfItems> ExposureSequence = new gdcm::SequenceOfItems();
//    ExposureSequence->SetLengthToUndefined();

//    gdcm::Attribute<0x0008,0x1160,VR::IS,VM::VM1> ReferencedFrameNum = {1};
//    gdcm::DataElement ReferencedFrame = ReferencedFrameNum.GetAsDataElement();

//    gdcm::Attribute<0x3002,0x0032,VR::DS,VM::VM1> MeterSetExpo = {1};
//    gdcm::DataElement ExpoMeterset = MeterSetExpo.GetAsDataElement();

//    gdcm::Attribute<0x300A,0x00F0,VR::IS,VM::VM1> NumOfBlocks = {0};
//    gdcm::DataElement NBlocks = NumOfBlocks.GetAsDataElement();

//    gdcm::Attribute<0x300A,0x011E,VR::DS,VM::VM1> GantryAngle1 = {gantryAngle};
//    gdcm::DataElement GAngle = GantryAngle1.GetAsDataElement();

//    gdcm::Attribute<0x300A,0x0120,VR::DS,VM::VM1> BeamLimitingDeviceAngle1 = {(360.0-colliThetaCurrentPosition)};
//    gdcm::DataElement BLDAngle = BeamLimitingDeviceAngle1.GetAsDataElement();

//    gdcm::Attribute<0x300A,0x0122,VR::DS,VM::VM1> PatientSupportAngle1 = {(couchTheta)};
//    gdcm::DataElement PSAngle = PatientSupportAngle1.GetAsDataElement();

//    gdcm::SmartPointer<gdcm::SequenceOfItems> BeamLimitingDeviceSequence = new gdcm::SequenceOfItems();
//    BeamLimitingDeviceSequence->SetLengthToUndefined();

//    for(int i=0; i<2;i++){
//        if(i==0){
//            //    gdcm::SmartPointer<gdcm::SequenceOfItems> BeamLimitingDeviceSequence = new gdcm::SequenceOfItems();
//            //    BeamLimitingDeviceSequence->SetLengthToUndefined();

//            gdcm::Attribute<0x300A,0x00B8,VR::CS,VM::VM1> RTBeamLimitingDeviceType = {"ASYMX"};
//            gdcm::DataElement RtDeviceType = RTBeamLimitingDeviceType.GetAsDataElement();

//            gdcm::Attribute<0x300A,0x00BC,VR::IS,VM::VM1> NumberOfLeafJawPairs = {3};
//            gdcm::DataElement JawPairs= NumberOfLeafJawPairs.GetAsDataElement();

//            gdcm::Attribute<0x300A,0x011C,VR::DS,VM::VM6> LeafJawPositions = {jawX1CurrentPosition,jawX2CurrentPosition,wireX1CurrentPosition,wireX2CurrentPosition,detectorxShift,imagerXCurrentPosition};
//            gdcm::DataElement JawPosition= LeafJawPositions.GetAsDataElement();

//            gdcm::Item beamLimitingItem;
//            gdcm::DataSet &dsbeamLimiting = beamLimitingItem.GetNestedDataSet();
//            dsbeamLimiting.Insert( RtDeviceType );
//            //    dsbeamLimiting.Insert(SDD);
//            dsbeamLimiting.Insert(JawPairs);
//            //    dsbeamLimiting.Insert(LeafBound);
//            dsbeamLimiting.Insert(JawPosition);

//            BeamLimitingDeviceSequence->AddItem(beamLimitingItem);
//        }

//        if(i==1){
//            //    gdcm::SmartPointer<gdcm::SequenceOfItems> BeamLimitingDeviceSequence = new gdcm::SequenceOfItems();
//            //    BeamLimitingDeviceSequence->SetLengthToUndefined();

//            gdcm::Attribute<0x300A,0x00B8,VR::CS,VM::VM1> RTBeamLimitingDeviceType = {"ASYMY"};
//            gdcm::DataElement RtDeviceType = RTBeamLimitingDeviceType.GetAsDataElement();

//            gdcm::Attribute<0x300A,0x00BC,VR::IS,VM::VM1> NumberOfLeafJawPairs = {3};
//            gdcm::DataElement JawPairs= NumberOfLeafJawPairs.GetAsDataElement();

//            gdcm::Attribute<0x300A,0x011C,VR::DS,VM::VM6> LeafJawPositions = {jawY1CurrentPosition,jawY2CurrentPosition,wireY1CurrentPosition,wireY2CurrentPosition,detectoryShift,imagerYCurrentPosition};
//            gdcm::DataElement JawPosition= LeafJawPositions.GetAsDataElement();

//            gdcm::Item beamLimitingItem;
//            gdcm::DataSet &dsbeamLimiting = beamLimitingItem.GetNestedDataSet();
//            dsbeamLimiting.Insert( RtDeviceType );
//            //    dsbeamLimiting.Insert(SDD);
//            dsbeamLimiting.Insert(JawPairs);
//            //    dsbeamLimiting.Insert(LeafBound);
//            dsbeamLimiting.Insert(JawPosition);

//            BeamLimitingDeviceSequence->AddItem(beamLimitingItem);
//        }
//    }

////        //        if(i==2){
////        //            //    gdcm::SmartPointer<gdcm::SequenceOfItems> BeamLimitingDeviceSequence = new gdcm::SequenceOfItems();
////        //            //    BeamLimitingDeviceSequence->SetLengthToUndefined();

////        //            gdcm::Attribute<0x300A,0x00B8,VR::CS,VM::VM1> RTBeamLimitingDeviceType = {"X"};
////        //            gdcm::DataElement RtDeviceType = RTBeamLimitingDeviceType.GetAsDataElement();

////        //            gdcm::Attribute<0x300A,0x00BC,VR::IS,VM::VM1> NumberOfLeafJawPairs = {1};
////        //            gdcm::DataElement JawPairs= NumberOfLeafJawPairs.GetAsDataElement();

////        //            gdcm::Attribute<0x300A,0x011C,VR::DS,VM::VM2> LeafJawPositions = {wireX1CurrentPosition,wireX2CurrentPosition};
////        //            gdcm::DataElement JawPosition= LeafJawPositions.GetAsDataElement();

////        //            gdcm::Item beamLimitingItem;
////        //            gdcm::DataSet &dsbeamLimiting = beamLimitingItem.GetNestedDataSet();
////        //            dsbeamLimiting.Insert( RtDeviceType );
////        //            //    dsbeamLimiting.Insert(SDD);
////        //            dsbeamLimiting.Insert(JawPairs);
////        //            //    dsbeamLimiting.Insert(LeafBound);
////        //            dsbeamLimiting.Insert(JawPosition);

////        //            BeamLimitingDeviceSequence->AddItem(beamLimitingItem);
////        //        }

////        //        if(i==3){
////        //            //    gdcm::SmartPointer<gdcm::SequenceOfItems> BeamLimitingDeviceSequence = new gdcm::SequenceOfItems();
////        //            //    BeamLimitingDeviceSequence->SetLengthToUndefined();

////        //            gdcm::Attribute<0x300A,0x00B8,VR::CS,VM::VM1> RTBeamLimitingDeviceType = {"Y"};
////        //            gdcm::DataElement RtDeviceType = RTBeamLimitingDeviceType.GetAsDataElement();

////        //            gdcm::Attribute<0x300A,0x00BC,VR::IS,VM::VM1> NumberOfLeafJawPairs = {1};
////        //            gdcm::DataElement JawPairs= NumberOfLeafJawPairs.GetAsDataElement();

////        //            gdcm::Attribute<0x300A,0x011C,VR::DS,VM::VM2> LeafJawPositions = {wireY1CurrentPosition,wireY2CurrentPosition};
////        //            gdcm::DataElement JawPosition= LeafJawPositions.GetAsDataElement();

////        //            gdcm::Item beamLimitingItem;
////        //            gdcm::DataSet &dsbeamLimiting = beamLimitingItem.GetNestedDataSet();
////        //            dsbeamLimiting.Insert( RtDeviceType );
////        //            //    dsbeamLimiting.Insert(SDD);
////        //            dsbeamLimiting.Insert(JawPairs);
////        //            //    dsbeamLimiting.Insert(LeafBound);
////        //            dsbeamLimiting.Insert(JawPosition);

////        //            BeamLimitingDeviceSequence->AddItem(beamLimitingItem);
////        //        }

////    }
////    gdcm::DataElement desbeamLimitingItem( gdcm::Tag(0x300A,0x00B6) );
////    desbeamLimitingItem.SetVR(gdcm::VR::SQ);
////    desbeamLimitingItem.SetValue(*BeamLimitingDeviceSequence);
////    desbeamLimitingItem.SetVLToUndefined();

////    gdcm::Item ExposureItem;
////    gdcm::DataSet &dsExposure = ExposureItem.GetNestedDataSet();
////    dsExposure.Insert( ReferencedFrame );
////    dsExposure.Insert(ExpoMeterset);
////    dsExposure.Insert(NBlocks);
////    dsExposure.Insert(GAngle);
////    dsExposure.Insert(BLDAngle);
////    dsExposure.Insert(PSAngle);
////    dsExposure.Insert(desbeamLimitingItem);

////    ExposureSequence->AddItem(ExposureItem);

////    gdcm::DataElement desExposureSequenceItem( gdcm::Tag(0x3002,0x0030) );
////    desExposureSequenceItem.SetVR(gdcm::VR::SQ);
////    desExposureSequenceItem.SetValue(*ExposureSequence);
////    desExposureSequenceItem.SetVLToUndefined();
////    ds.Insert(desExposureSequenceItem);


////    /*********SEQUENCE-END*********/

    gdcm::Attribute<0x300A,0x011E,VR::DS,VM::VM1> GantryAngle = {0};
    ds.Insert(GantryAngle.GetAsDataElement());

////    //    gdcm::Attribute<0x300A,0x014A,VR::FL,VM::VM1> GantryPitchAngle = {};
////    //    ds.Insert(GantryPitchAngle.GetAsDataElement());

////    gdcm::Attribute<0x300A,0x0120,VR::DS,VM::VM1> BeamLimitingDeviceAngle = {(360.0-colliThetaCurrentPosition)};
////    ds.Insert(BeamLimitingDeviceAngle.GetAsDataElement());

    gdcm::Attribute<0x300A,0x0122,VR::DS,VM::VM1> PatientSupportAngle = {0};
    ds.Insert(PatientSupportAngle.GetAsDataElement());

    gdcm::Attribute<0x300A,0x00B3,VR::CS,VM::VM1> PrimaryDosimeterUnit = {"MU"};
    ds.Insert(PrimaryDosimeterUnit.GetAsDataElement());

                    qDebug()<<"Data----23";

//    if(treatmentMachineName == "Bhabhatron"){
//        gdcm::Attribute<0x300A,0x00B3,VR::CS,VM::VM1> PrimaryDosimeterUnit = {"MINUTE"};
//        ds.Insert( PrimaryDosimeterUnit.GetAsDataElement() );
//    }
//    else{
//        gdcm::Attribute<0x300A,0x00B3,VR::CS,VM::VM1> PrimaryDosimeterUnit = {"MU"};
//        ds.Insert( PrimaryDosimeterUnit.GetAsDataElement() );
//    }

    gdcm::Attribute<0x300A,0x0128,VR::DS,VM::VM1> TableTopVerticalPosition = {0};
    ds.Insert(TableTopVerticalPosition.GetAsDataElement());

    gdcm::Attribute<0x300A,0x0129,VR::DS,VM::VM1> TableTopLongitudinalPosition = {0};
    ds.Insert(TableTopLongitudinalPosition.GetAsDataElement());

    gdcm::Attribute<0x300A,0x012A,VR::DS,VM::VM1> TableTopLateralPosition = {0};
    ds.Insert(TableTopLateralPosition.GetAsDataElement());

    gdcm::Attribute<0x300A,0x012C,VR::DS,VM::VM3> IsocenterPosition = {isocentre[0],isocentre[1],0};
    ds.Insert( IsocenterPosition.GetAsDataElement() );

    gdcm::Attribute<0x300A,0x00F0,VR::IS,VM::VM1> NumberOfBlocks = {0};
    ds.Insert(NumberOfBlocks.GetAsDataElement());

////    gdcm::Attribute<0x0018,0x5100,VR::CS,VM::VM1> PatientPosition = {QString(patDetails.at(7)).toStdString().c_str()};
////    ds.Insert(PatientPosition.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1052,VR::DS,VM::VM1> RescaleIntercept = {0.0};
    ds.Insert(RescaleIntercept.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1053,VR::DS,VM::VM1> RescaleSlope = {1.0};
    ds.Insert(RescaleSlope.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1054,VR::LO,VM::VM1> RescaleType = {"US"};
    ds.Insert(RescaleType.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1050,VR::DS,VM::VM1> WindowCenter = {32768};
    ds.Insert(WindowCenter.GetAsDataElement());

    gdcm::Attribute<0x0028,0x1051,VR::DS,VM::VM1> WindowWidth = {65535};
    ds.Insert(WindowWidth.GetAsDataElement());

    gdcm::Attribute<0x300C,0x0006,VR::IS,VM::VM1> ReferencedBeamNumber = {1};
    ds.Insert(ReferencedBeamNumber.GetAsDataElement());

    gdcm::Attribute<0x300E,0x0002,VR::CS,VM::VM1> ApprovalStatus = {"UNAPPROVED"};
    ds.Insert(ApprovalStatus.GetAsDataElement());

    qDebug()<<"Data----24";

//        gdcm::Attribute<0x0008,0x0016,VR::UI,VM::VM1> SOPClassUID = {};
//        ds.Insert( SOPClassUID.GetAsDataElement());

//        gdcm::Attribute<0x0008,0x0018,VR::UI,VM::VM1> SOPInstanceUID = {};
//        ds.Insert( SOPInstanceUID.GetAsDataElement());

    gdcm::Attribute<0x0008,0x0005,VR::CS,VM::VM1> SpecificCharacterSet = {"ISO_IR_100"};
    ds.Insert(SpecificCharacterSet.GetAsDataElement());

    unsigned int dims[2] = {};
    dims[0] = imSize1;
    dims[1] = imSize1;
    image1.SetDimensions( dims );

    image1.SetOrigin(0,0);
    image1.SetOrigin(1,1);

     qDebug()<<"Data----25";

////    // qDebug()<<"PixelSpacing"<<double(int(imaginPixelSpacing*100.0))/100.0<<double(int(imaginPixelSpacing*100.0))/100.0;


    double *spacing1 = new double[2];
////    //    spacing1[0]=double(int(imaginPixelSpacing*100.0))/100.0;
////    //    spacing1[1]=double(int(imaginPixelSpacing*100.0))/100.0;
    spacing1[0]=pixSpacing[0];
    spacing1[1]=pixSpacing[1];

    image1.SetSpacing(spacing1);
    gdcm::PixelFormat pf = gdcm::PixelFormat::UINT16;
    pf.SetSamplesPerPixel( 1 );
    image1.SetPixelFormat(pf);
    qDebug()<<"hi";

    gdcm::PhotometricInterpretation pi =
            gdcm::PhotometricInterpretation::MONOCHROME2;
    image1.SetPhotometricInterpretation( pi );

    image1.SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian );

    gdcm::DataElement pixeldata(gdcm::Tag(0x7fe0,0x0010));
    pixeldata.SetByteValue( (char*)buffer, 3072*3072*sizeof(unsigned short));
    image1.SetDataElement( pixeldata );

    QString path = ("D:\\Resample converted");
    qDebug()<<"path"<<path;
    writer.SetFileName((path+"\\Images_"+ QString::number(2)+".dcm").toStdString().c_str());
    writer.SetFile(file);
    if( !writer.Write())
    {
        qDebug("Dicom Image Write Error!");
    }
    qDebug()<<"done";
}
