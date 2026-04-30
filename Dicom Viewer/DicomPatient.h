#ifndef DICOMPATIENT_H
#define DICOMPATIENT_H

#include <string>
#include <vector>
#include "DicomStudy.h"

class DicomPatient
{
public:
    DicomPatient();
    DicomPatient(DicomPatient*old);
    ~DicomPatient();
public:
    std::string PatientName;
    std::string PatientID;
    std::vector<DicomStudy*> StudyList;
    int indexOfCurrentStudy;
    int indexOfCurrentSeries;
    int indexOfCurrentImage;

    void reset();

    DicomStudy*getCurrentDicomStudy();
    void setCurrentDicomStudyById(std::string &studyid);

    DicomSeries* getCurrentDicomSeries();
    void setCurrentDicomSeriesById(std::string &seriesnum);

    DicomImage* getCurrentDicomImage();
    DicomImage* getNextDicomImage();
    DicomImage* getDicomImageByRfid(std::string &rfid);
    DicomImage* getDicomImageByIndex(int index);
};

#endif // DICOMPATIENT_H
