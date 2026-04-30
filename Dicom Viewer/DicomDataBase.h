#ifndef DICOMDATABASE_H
#define DICOMDATABASE_H

#include <string>
#include <vector>
#include "DicomPatient.h"


class DicomDataBase
{
public:
    static DicomDataBase* getInstance();
    void Init(std::string dir);
    void InitFromSingleImage(std::string ImageFileName);
    void InitFromSeriesFolder(std::string SeriesFolder);
private:

    DicomDataBase();
    ~DicomDataBase();
public:
    std::vector<DicomPatient*> PatientList;
    std::string DicomDirFilePath;
    std::string DicomForderPath;
    DicomPatient*getPatientById(std::string &patientid);
    DicomPatient*get_previous_patient(DicomPatient*current_patient);
    DicomPatient*get_latter_patient(DicomPatient*current_patient);
};

//DicomDataBase* DicomDataBase::m_pSingleton = new DicomDataBase();

#endif // DICOMDATABASE_H
