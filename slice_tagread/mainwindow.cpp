#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "itkGDCMImageIO.h"
#include "itkMetaDataObject.h"
#include "QDebug"
#include "QApplication"
#include "QProcess"


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

void MainWindow::ReadImageToDicom(const MainWindow::Img *image1, const size_t imSize, int j, std::string fileName)
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
//    SOPINSTANCEUIDList.removeAt(j);
//    SOPINSTANCEUIDList.insert(j,SOPINSTANCEUID.c_str());

    SOPINSTANCEUIDList.append(SOPINSTANCEUID.c_str());

    itk::ExposeMetaData(dict2,"0020|000d",StudyINSTANCEUID);
//    StudyINSTANCEUIDList.removeAt(j);
//    StudyINSTANCEUIDList.(j,StudyINSTANCEUID.c_str());
    StudyINSTANCEUIDList.append(StudyINSTANCEUID.c_str());

    itk::ExposeMetaData(dict2,"0020|000e",SeriesINSTANCEUID);
//    SeriesINSTANCEUIDList.removeAt(j);
//    SeriesINSTANCEUIDList.insert(j,SeriesINSTANCEUID.c_str());
    SeriesINSTANCEUIDList.append(SeriesINSTANCEUID.c_str());

    itk::ExposeMetaData(dict2,"0020|0052",FrameReferenceUID);
//    FrameReferenceUIDList.removeAt(j);
//    FrameReferenceUIDList.insert(j,FrameReferenceUID.c_str());
    FrameReferenceUIDList.append(SeriesINSTANCEUID.c_str());


    itk::ExposeMetaData(dict2,"0010|0030",DOB);

    itk::ExposeMetaData(dict2,"0010|0040",gen);



    qDebug()<<"Exit"<<j;


}

void MainWindow::on_Readtag_clicked()
{
//    QString path = QFileDialog::getExistingDirectory(this, tr("Image folder"));
    QString path ="D:\\writeStruct\\CT";
    if(path == 0||path == "")
    {
        QMessageBox::critical(this,"Error","No path found !!");
    }

    QDir dir(path);
    QStringList filters;
    QStringList dcmList;

    if(!dir.exists())
    {
        qDebug()<<"Directory doesnot exit---7";
        QMessageBox::critical(this,"Error","Directory does not exists !!");
    }

    filters << "*.dcm" ;
    dir.setNameFilters(filters);
    dcmList = dir.entryList(filters);


    qDebug()<<"No. of dicom files : "<<dcmList.length();

    qDebug()<<"path"<<path;

    if(dcmList.length()==0){
        QMessageBox::warning(this,"Error","No images found..");
        return;
    }


    buffer = new unsigned short[dimsize*dimsize*dcmList.length()];

    std::string fileNameCPP;

    for(int i=0;i<dcmList.length();i++)
    {
        fileNameCPP = path.toStdString() + "\\Slice" + std::to_string(i+1) + ".dcm";

        ReaderType1::Pointer reader1;
        reader1 = ReaderType1::New();

        reader1->SetFileName(fileNameCPP);

        typedef itk::GDCMImageIO  ImageType;
        ImageType::Pointer gdcmImage = ImageType::New();

        reader1->SetImageIO( gdcmImage);

//        reader->SetDataScalarTypeToShort();
//        reader->SetMemoryRowOrderToFileNative();

        try
        {
        reader1->Update();
        }
        catch(...)
        {
            qDebug()<<"Exception  reading dicom files";
            QMessageBox::warning(this,"Error","Problems in reading Dicom images");
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

//    for(int i=0;i<85;i++)
//    {
//       SOPINSTANCEUIDList1.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value1"<<SOPINSTANCEUIDList1<<SOPINSTANCEUIDList1.length();

//    for(int i=85;i<170;i++)
//    {
//       SOPINSTANCEUIDList2.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value2"<<SOPINSTANCEUIDList2<<SOPINSTANCEUIDList2.length();
//    for(int i=170;i<255;i++)
//    {
//       SOPINSTANCEUIDList3.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value3"<<SOPINSTANCEUIDList3<<SOPINSTANCEUIDList3.length();

//    for(int i=255;i<340;i++)
//    {
//       SOPINSTANCEUIDList4.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value4"<<SOPINSTANCEUIDList4<<SOPINSTANCEUIDList4.length();

//    for(int i=340;i<426;i++)
//    {
//       SOPINSTANCEUIDList5.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value5"<<SOPINSTANCEUIDList5<<SOPINSTANCEUIDList5.length();

//    for(int i=426;i<512;i++)
//    {
//        SOPINSTANCEUIDList6.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value6"<<SOPINSTANCEUIDList6<<SOPINSTANCEUIDList6.length();

//    for(int i=0;i<102;i++)
//    {
//       SOPINSTANCEUIDList1.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value1"<<SOPINSTANCEUIDList1<<SOPINSTANCEUIDList1.length();

//    for(int i=102;i<204;i++)
//    {
//       SOPINSTANCEUIDList2.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value2"<<SOPINSTANCEUIDList2<<SOPINSTANCEUIDList2.length();
//    for(int i=204;i<306;i++)
//    {
//       SOPINSTANCEUIDList3.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value3"<<SOPINSTANCEUIDList3<<SOPINSTANCEUIDList3.length();

//    for(int i=306;i<409;i++)
//    {
//       SOPINSTANCEUIDList4.append(SOPINSTANCEUIDList[i]);

//    }
//    qDebug()<<"SOP----Value4"<<SOPINSTANCEUIDList4<<SOPINSTANCEUIDList4.length();

//    for(int i=409;i<512;i++)
//    {
//       SOPINSTANCEUIDList5.append(SOPINSTANCEUIDList[i]);

//    }

//    qDebug()<<"SOP----Value5"<<SOPINSTANCEUIDList5<<SOPINSTANCEUIDList5.length();



//    qDebug()<<"SOPIDList"<<SOPINSTANCEUIDList[0]<<SOPINSTANCEUIDList[1];
//    qDebug()<<"studyIDList"<<StudyINSTANCEUIDList[0];
//    qDebug()<<"SeriesIDList"<<SeriesINSTANCEUIDList[0];
//    qDebug()<<"frameIDList"<<FrameReferenceUIDList[0];

}

void MainWindow::on_RTstruct_generate_clicked()
{
//    QString program = qApp->applicationDirPath()+"/WriteRTStruct"+"/WriteRTStruct.exe";

//    qDebug()<<"program"<<program;
    std::string reqDetails;
//    QString reqUIDs;

//    QStringList arguments2;

    QString patientname=PatientName.c_str();
    QString Patientid=PatientID.c_str();
    QString Dicompath = "D:\\Test";
    QString gender= gen.c_str();
    QString dOb=DOB.c_str();
    QString Age=age.c_str();
    QString StudyDes=StudyD.c_str();
    QString SeriDes=Seri.c_str();
    QString Manufacture=manufacture.c_str();
    QString Model=model.c_str();
    QString version="1.3.7";
//    std::string version="1.3.7";
    QString Contourpoints= "10,12,13,12,12,15";
//    std::string Contourpoints= "10,12,13,12,12,15";


//    std::string SOPINSTANCEuid1= SOPINSTANCEUIDList1.join(",").toStdString();
//    std::string SOPINSTANCEuid2= SOPINSTANCEUIDList2.join(",").toStdString();
//    std::string SOPINSTANCEuid3= SOPINSTANCEUIDList3.join(",").toStdString();
//    std::string SOPINSTANCEuid4= SOPINSTANCEUIDList4.join(",").toStdString();
//    std::string SOPINSTANCEuid5= SOPINSTANCEUIDList5.join(",").toStdString();
//    std::string SOPINSTANCEuid6= SOPINSTANCEUIDList6.join(",").toStdString();

    QString StudyINSTANCEuid = StudyINSTANCEUIDList[0];
    QString SeriesINSTANCEuid= SeriesINSTANCEUIDList[0];
    QString FrameReferenceuid= FrameReferenceUIDList[0];

    std::cout<<"uids"<<StudyINSTANCEuid<<SeriesINSTANCEuid<<FrameReferenceuid;
    reqDetails=Dicompath+","+patientname+","+Patientid+","+gender+","+dOb+","+Age+","+StudyDes+","+SeriDes+","+Manufacture+","+Model+","+StudyINSTANCEuid+","+SeriesINSTANCEuid+","+FrameReferenceuid+","+version;
//    arguments2<<Contourpoints<<SOPINSTANCEuid1<<SOPINSTANCEuid2<<SOPINSTANCEuid3<<SOPINSTANCEuid4<<SOPINSTANCEuid5<<SOPINSTANCEuid6<<reqDetails;
//    rtstruct=new WriteRTStruct();
//    rtstruct->RTStruct(Contourpoints,SOPINSTANCEuid1,SOPINSTANCEuid2,SOPINSTANCEuid3,SOPINSTANCEuid4,SOPINSTANCEuid5,SOPINSTANCEuid6,reqDetails);
//    qDebug()<<"argument"<<arguments2;
//    QProcess *myProcess =new QProcess();
//    myProcess->start(program, arguments2);

//    while(myProcess->state()== myProcess->Running)
//    {
//        qDebug()<<"state"<<myProcess->state();
//        qApp->processEvents();
//    }

    qDebug()<<"Finished";
}
