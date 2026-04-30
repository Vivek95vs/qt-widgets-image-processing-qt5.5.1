#ifndef DICOMSTUDY_H
#define DICOMSTUDY_H

#include <string>
#include <vector>
#include "DicomSeries.h"

class DicomStudy
{
public:
    DicomStudy();
    ~DicomStudy();
public:
    std::string ModulationType;
    std::string InstitutionName;
    std::string PatientBirthDate;
    std::string PatientSex;
    std::string PatientAge;
    std::string StudyId;
    std::vector<DicomSeries*> SeriesList;
};



#endif // DICOMSTUDY_H
