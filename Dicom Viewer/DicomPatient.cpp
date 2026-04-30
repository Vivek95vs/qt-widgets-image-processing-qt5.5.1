#include "DicomPatient.h"

DicomPatient::DicomPatient()
{
    indexOfCurrentStudy = 0;
    indexOfCurrentSeries = 0;
    indexOfCurrentImage = 0;
}

DicomPatient::DicomPatient(DicomPatient * old)
{
    this->PatientName = old->PatientName;
    this->PatientID =old->PatientID;
    this->indexOfCurrentStudy = old->indexOfCurrentStudy;
    this->indexOfCurrentSeries = old->indexOfCurrentSeries;
    this->indexOfCurrentImage = old->indexOfCurrentImage;

    for(int i=0;i<old->StudyList.size();i++)
    {
        this->StudyList.push_back(old->StudyList[i]);
    }
}

DicomPatient::~DicomPatient()
{
}

void DicomPatient::reset()
{
    indexOfCurrentStudy = 0;
    indexOfCurrentSeries = 0;
    indexOfCurrentImage = 0;
}

DicomStudy * DicomPatient::getCurrentDicomStudy()
{
    return this->StudyList[indexOfCurrentStudy];
}

void DicomPatient::setCurrentDicomStudyById(std::string &studyid)
{
    int index = 0;
    for(index=0;index<this->StudyList.size(); index++)
    {
        if (StudyList[index]->StudyId == studyid)
        {
            indexOfCurrentStudy = index;
            return;
        }
    }
    indexOfCurrentStudy = 0;
}

DicomSeries * DicomPatient::getCurrentDicomSeries()
{
    return this->StudyList[indexOfCurrentStudy]->SeriesList[indexOfCurrentSeries];
}

void DicomPatient::setCurrentDicomSeriesById(std::string & seriesnum)
{

    for(int i=0;i<this->StudyList.size();i++)
    {
        for(int j=0;j<this->StudyList[i]->SeriesList.size();j++)
        {
            if(this->StudyList[i]->SeriesList[j]->SeriseNumber==seriesnum)
            {
                indexOfCurrentSeries = j;
                indexOfCurrentStudy = i;
                indexOfCurrentImage = 0;
                return;
            }
        }
    }
}

DicomImage * DicomPatient::getCurrentDicomImage()
{
    return this->StudyList[indexOfCurrentStudy]->SeriesList[indexOfCurrentSeries]->ImageList[indexOfCurrentImage];
}

DicomImage * DicomPatient::getNextDicomImage()
{
    indexOfCurrentImage =
        (indexOfCurrentImage == StudyList[indexOfCurrentStudy]->
                                SeriesList[indexOfCurrentSeries]->
                                ImageList.size() - 1 ?
                                0 : indexOfCurrentImage + 1);
    return getCurrentDicomImage();
}

DicomImage * DicomPatient::getDicomImageByRfid(std::string & rfid)
{

    for(int i=0;i<this->StudyList.size();i++)
    {
        for(int j=0;j<this->StudyList[i]->SeriesList.size();j++)
        {
            for(int k=0;k<this->StudyList[i]->SeriesList[j]->ImageList.size();k++)
            {
                if(this->StudyList[i]->SeriesList[j]->ImageList[k]->ReferencedFileID== rfid)
                {
                    indexOfCurrentStudy = i;
                    indexOfCurrentSeries = j;
                    indexOfCurrentImage = k;
                    return  getCurrentDicomImage();
                }
            }
        }
    }
}

 DicomImage * DicomPatient::getDicomImageByIndex(int index)
 {
     if (index>this->StudyList[indexOfCurrentStudy]->SeriesList[indexOfCurrentSeries]->ImageList.size())
     {
         return getCurrentDicomImage();
     }else
     {
         indexOfCurrentImage = index;
         return this->StudyList[indexOfCurrentStudy]->SeriesList[indexOfCurrentSeries]->ImageList[indexOfCurrentImage];
     }
 }
