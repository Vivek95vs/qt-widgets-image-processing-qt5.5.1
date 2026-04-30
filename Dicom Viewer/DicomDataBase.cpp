#include "DicomDataBase.h"
//dcmtk-64
#include <dcmdata/dcdicdir.h>
#include <dcmdata/dcdeftag.h>
#include "DicomDir.h"
#include <QFileSystemModel>
#include <QString>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include "vtkMyDICOMImageReader.h"


DicomDataBase * DicomDataBase::getInstance()
{
    /*if (NULL == m_pSingleton)
    {
        m_pSingleton = new DicomDataBase();
    }*/
    static DicomDataBase single;
    return &single;
    //return m_pSingleton;
}

 void DicomDataBase::Init(std::string dir)
 {

     QFile *dirfile = new QFile(QString::fromStdString(dir));
     auto dirfile_info = QFileInfo(*dirfile);
     QString FolderPrefix = dirfile_info.absolutePath();
     dirfile->close();

     DcmDicomDir dicomdir(dir.c_str());
#if _DEBUG
     std::filebuf fb;
     fb.open("DicomDir.log", std::ios::out);
     std::ostream out(&fb);
     dicomdir.print(out);
     fb.close();

     DcmFileFormat DCMFF = dicomdir.getDirFileFormat();
     std::filebuf lb;
     lb.open("DcmFileFormat.log", std::ios::out);
     std::ostream out2(&lb);
     DCMFF.print(out2);
     lb.close();
#endif

     DcmDirectoryRecord * DicomDirRootRecord = &(dicomdir.getRootRecord());

                                                                           //bool flag = DicomDirRootRecord->isEmpty();

     DcmDirectoryRecord *   PatientRecord = NULL;
     DcmDirectoryRecord *   StudyRecord = NULL;
     DcmDirectoryRecord *   SeriesRecord = NULL;
     DcmDirectoryRecord *   ImageRecord = NULL;
     OFString tmpString;

     this->PatientList.clear();
     int i = 0, j = 0, k = 0, l = 0;
     while (((PatientRecord = DicomDirRootRecord->getSub(i)) != NULL))
     {
         DicomPatient *m_patient = new DicomPatient();
         if (PatientRecord->findAndGetOFString(DCM_PatientID, tmpString).good())
         {
             m_patient->PatientID = tmpString.c_str();
         }
         if (PatientRecord->findAndGetOFString(DCM_PatientName, tmpString).good())
         {
             m_patient->PatientName = tmpString.c_str();
         }
         while (((StudyRecord = PatientRecord->getSub(j)) != NULL))
         {
             DicomStudy *m_study = new DicomStudy();
             if (StudyRecord->findAndGetOFString(DCM_PatientBirthDate, tmpString).good())
             {
                 m_study->PatientBirthDate = tmpString.c_str();
             }
             if (StudyRecord->findAndGetOFString(DCM_PatientSex, tmpString).good())
             {
                 m_study->PatientSex = tmpString.c_str();
             }
             if (StudyRecord->findAndGetOFString(DCM_PatientAge, tmpString).good())
             {
                 m_study->PatientAge = tmpString.c_str();
             }
             if (StudyRecord->findAndGetOFString(DCM_StudyID, tmpString).good())
             {
                 m_study->StudyId = tmpString.c_str();
             }
             if (StudyRecord->findAndGetOFString(DCM_StudyID, tmpString).good())
             {
                 m_study->StudyId = tmpString.c_str();
             }
             if (StudyRecord->findAndGetOFString(DCM_ModalityLUTType, tmpString).good())
             {
                 m_study->ModulationType = tmpString.c_str();
             }
             if (StudyRecord->findAndGetOFString(DCM_InstitutionName, tmpString).good())
             {
                 m_study->InstitutionName = tmpString.c_str();
             }
             while (((SeriesRecord = StudyRecord->getSub(k)) != NULL))
             {
                 DicomSeries *m_series = new DicomSeries();
                 if (SeriesRecord->findAndGetOFString(DCM_SeriesNumber, tmpString).good())
                 {
                     m_series->SeriseNumber = tmpString.c_str();
                 }
                 if (SeriesRecord->findAndGetOFString(DCM_StationName, tmpString).good())
                 {
                     m_series->StationName = tmpString.c_str();
                 }
                 if (SeriesRecord->findAndGetOFString(DCM_Manufacturer, tmpString).good())
                 {
                     m_series->Manufacturer = tmpString.c_str();
                 }
                 if (SeriesRecord->findAndGetOFString(DCM_NumberOfSeriesRelatedInstances, tmpString).good())
                 {
                     m_series->NumberOfSeriesRelatedInstances = tmpString.c_str();
                 }
                 while (((ImageRecord = SeriesRecord->getSub(l)) != NULL))
                 {
                     DicomImage * m_image = new DicomImage();
                     if (ImageRecord->findAndGetOFStringArray(DCM_ReferencedFileID, tmpString, true).good())
                     {
                         m_image->ReferencedFileID = tmpString.c_str();
                         QString temp = QString::fromStdString(FolderPrefix.toStdString() + "\\" + m_image->ReferencedFileID);
                         temp.replace(QChar('\\'), QChar('/'));
                         m_image->AbsFilePath = temp.toStdString();
                     }
                     if (ImageRecord->findAndGetOFString(DCM_InstanceCreationDate, tmpString).good())
                     {
                         m_image->InstanceCreationDate = tmpString.c_str();
                     }
                     if (ImageRecord->findAndGetOFString(DCM_KVP, tmpString).good())
                     {
                         m_image->kpv = tmpString.c_str();
                     }
                     if (ImageRecord->findAndGetOFString(DCM_SliceLocation, tmpString).good())
                     {
                         m_image->SliceLocation = tmpString.c_str();
                     }
                     if (ImageRecord->findAndGetOFString(DCM_Rows, tmpString).good())
                     {
                         m_image->row = atoi(tmpString.c_str());
                     }
                     if (ImageRecord->findAndGetOFString(DCM_Columns, tmpString).good())
                     {
                         m_image->col = atoi(tmpString.c_str());
                     }
                     if (ImageRecord->findAndGetOFString(DCM_InstanceNumber, tmpString).good())
                     {
                         m_image->InstanceNumber = tmpString.c_str();
                     }
                     l++;
                     m_series->ImageList.push_back(m_image);
                 }
                 l = 0;
                 k++;
                 m_study->SeriesList.push_back(m_series);
             }
             k = 0;
             j++;
             m_patient->StudyList.push_back(m_study);
         }
         j = 0;
         i++;
         this->PatientList.push_back(m_patient);
     }
 }

void DicomDataBase::InitFromSingleImage(std::string ImageFileName)
{
    //¹¹ÔìPatient/Study/Series,È»ºóÌí¼ÓÕâÕÅÍ¼
    /*
     * patientµÄIDºÍName
     * StudyµÄID
     * ËùÔÚµÄSeriesID
     */
     DcmFileFormat fileformat;
     OFCondition status = fileformat.loadFile(ImageFileName.c_str());
     if (status.bad())
     {
         return;
     }
     OFString temp_OFString;
     //image
     this->PatientList.clear();
     DicomImage * m_image = new DicomImage();
     if (fileformat.getDataset()->findAndGetOFStringArray(DCM_ReferencedFileID, temp_OFString, true).good())
     {
         m_image->ReferencedFileID = temp_OFString.c_str();
         m_image->AbsFilePath = ImageFileName;
     }
     else
     {
         m_image->AbsFilePath = ImageFileName;
         QFileInfo * fileinfo = new QFileInfo(QString::fromStdString(ImageFileName));
         if (fileinfo->exists())
         {
             m_image->ReferencedFileID = fileinfo->fileName().toStdString();
         }
     }
     //series
     DicomSeries *m_series = new DicomSeries();
     if (fileformat.getDataset()->findAndGetOFStringArray(DCM_SeriesNumber, temp_OFString, OFTrue).good())
     {
         m_series->SeriseNumber = temp_OFString.c_str();
     }
     m_series->ImageList.push_back(m_image);
     //study
     DicomStudy *m_study = new DicomStudy();
     if (fileformat.getDataset()->findAndGetOFStringArray(DCM_StudyID, temp_OFString, OFTrue).good())
     {
         m_study->StudyId = temp_OFString.c_str();
     }
     m_study->SeriesList.push_back(m_series);
     //patient
     DicomPatient *m_patient = new DicomPatient();
     if (fileformat.getDataset()->findAndGetOFStringArray(DCM_PatientName, temp_OFString, OFTrue).good())
     {
         m_patient->PatientName = temp_OFString.c_str();
     }
     if (fileformat.getDataset()->findAndGetOFStringArray(DCM_PatientID, temp_OFString, OFTrue).good())
     {
         m_patient->PatientID = temp_OFString.c_str();
     }
     m_patient->StudyList.push_back(m_study);
     this->PatientList.push_back(m_patient);
}

void DicomDataBase::InitFromSeriesFolder(std::string SeriesFolder)
{
    QDir * folder = new QDir(QString::fromStdString(SeriesFolder));
    QStringList files = folder->entryList(QDir::Files | QDir::Readable, QDir::Name);
    QString Prefix = folder->absolutePath();
    Prefix.append("\\");
    Prefix.replace(QChar('\\'), QChar('/'));

    std::map<int,std::string > * AllTheFiles = new std::map<int, std::string>();
    OFString temp_OFString;
    vtkSmartPointer<vtkMyDICOMImageReader> DICOMreader = vtkSmartPointer<vtkMyDICOMImageReader>::New();
    DICOMreader->SetGlobalWarningDisplay(false);
    for(int i=0;i<files.size();i++)
    {
        QString _currentfilename = Prefix;
        _currentfilename.append(files.at(i));

        DICOMreader->SetFileName(_currentfilename.toStdString().c_str());
        DICOMreader->Update();

        DcmFileFormat fileformat;
        OFCondition status = fileformat.loadFile(_currentfilename.toStdString().c_str());

        if (status.good()&& DICOMreader->getImageDateLength())
        {
            if (fileformat.getDataset()->findAndGetOFStringArray(DCM_InstanceNumber, temp_OFString, true).good())
            {
                AllTheFiles->insert(std::map<int, std::string>::value_type(std::atoi(temp_OFString.c_str()), files.at(i).toStdString()));
            }
        }
        else
        {
            continue;
        }
    }
    std::vector<std::string> * RfidInSeriesFolder=new std::vector<std::string>();
    std::map<int, std::string>::iterator iter;
    for(int i=1;i<AllTheFiles->size()+1;i++)
    {
        iter = AllTheFiles->find(i);
        if (iter != AllTheFiles->end())
        {
            RfidInSeriesFolder->push_back(iter->second);
        }
        else
        {
            continue;
        }
    }

    this->PatientList.clear();
    QString _currentfilename = Prefix;
    _currentfilename.append(QString::fromStdString(RfidInSeriesFolder->at(0)));
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(_currentfilename.toStdString().c_str());
    if (status.bad())
    {
    }
    //series
    DicomSeries *m_series = new DicomSeries();
    if (fileformat.getDataset()->findAndGetOFString(DCM_SeriesNumber, temp_OFString).good())
    {
        m_series->SeriseNumber = temp_OFString.c_str();
    }
    //image
    for (int i = 0; i < RfidInSeriesFolder->size(); i++)
    {
        DicomImage * m_image = new DicomImage();

        m_image->ReferencedFileID = RfidInSeriesFolder->at(i);
        QString temp = Prefix;
        temp.append(QString::fromStdString(m_image->ReferencedFileID));
        m_image->AbsFilePath = temp.toStdString();

        m_series->ImageList.push_back(m_image);
    }
    //study
    DicomStudy *m_study = new DicomStudy();
    if (fileformat.getDataset()->findAndGetOFStringArray(DCM_StudyID, temp_OFString, OFTrue).good())
    {
        m_study->StudyId = temp_OFString.c_str();
    }
    m_study->SeriesList.push_back(m_series);
    //patient
    DicomPatient *m_patient = new DicomPatient();
    if (fileformat.getDataset()->findAndGetOFStringArray(DCM_PatientName, temp_OFString, OFTrue).good())
    {
        m_patient->PatientName = temp_OFString.c_str();
    }
    if (fileformat.getDataset()->findAndGetOFStringArray(DCM_PatientID, temp_OFString, OFTrue).good())
    {
        m_patient->PatientID = temp_OFString.c_str();
    }
    m_patient->StudyList.push_back(m_study);
    this->PatientList.push_back(m_patient);
}

DicomDataBase::DicomDataBase()
{
}


DicomDataBase::~DicomDataBase()
{
}
DicomPatient * DicomDataBase::getPatientById(std::string &patientid)
{
    for (int i=0;i<PatientList.size();i++)
    {
        if (PatientList[i]->PatientID == patientid)
        {
            return PatientList[i];
        }
    }
    return nullptr;
}

 DicomPatient * DicomDataBase::get_previous_patient(DicomPatient * current_patient)
 {
    for(int i=0;i<PatientList.size();i++)
    {
        if (PatientList[i]->PatientID== current_patient->PatientID)
        {
            return (i - 1 < 0 ? PatientList[i] : PatientList[i- 1]);
        }
    }
     return current_patient;
 }

 DicomPatient * DicomDataBase::get_latter_patient(DicomPatient * current_patient)
 {
     for (int i = 0; i<PatientList.size(); i++)
     {
         if (PatientList[i]->PatientID == current_patient->PatientID)
         {
             return (i + 2 >PatientList.size() ? PatientList[i] : PatientList[i + 1]);
         }
     }
     return current_patient;
 }
