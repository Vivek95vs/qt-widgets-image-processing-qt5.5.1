#ifndef DICOMSERIES_H
#define DICOMSERIES_H

#include <string>
#include "DicomImage.h"
#include <vector>

class DicomSeries
{
public:
    DicomSeries();
    ~DicomSeries();
public:
    std::string Manufacturer;
    std::string StationName;
    std::string SeriseNumber;
    std::string NumberOfSeriesRelatedInstances;
    std::vector<DicomImage*> ImageList;
};

#endif // DICOMSERIES_H
