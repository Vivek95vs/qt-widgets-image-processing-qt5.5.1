#ifndef DICOMIMAGE_H
#define DICOMIMAGE_H

#include <string>


class DicomImage
{
public:
    DicomImage();
    ~DicomImage();
public:
    std::string ReferencedFileID;
    std::string InstanceCreationDate;
    std::string kpv;
    std::string SliceLocation;
    std::string InstanceNumber;
    std::string AbsFilePath;
    int row;
    int col;
    std::string PixelSpacing;
public:
    std::string getReferencedFileID();
    void setReferencedFileID(std::string value);

    std::string getInstanceCreationDate();
    void setInstanceCreationDate(std::string value);

    std::string getkpv();
    void setkpv(std::string value);

    std::string getSliceLocation();
    void setSliceLocation(std::string value);

    std::string getPixelSpacing();
    void setPixelSpacing(std::string value);

    int getRow();
    void setRow(int value);

    int getCol();
    void setCol(int value);
};

#endif // DICOMIMAGE_H
