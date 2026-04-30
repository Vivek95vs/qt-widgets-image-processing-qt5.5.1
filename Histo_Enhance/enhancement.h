#pragma once
#include <iostream>
#include <cmath>
using std::string;  /* Most recommended */
class Enhancement
{
public:
    int i, j;

public:
    Enhancement();
    ~Enhancement();

    unsigned short** Normalization_Function(unsigned short** InputImage, int rowSize, int colSize, int minValue, int maxValue, float Angle);
    unsigned short*  ImageEnhancement(unsigned short* inputImage, int rowSize, int colSize, int IAngle);
    void Convertion2D1(unsigned short** Normalization, unsigned short *image, int  rowSize, int colSize);
    void gaussFilt(unsigned short *image, int sigma, unsigned short*outputImage, int rowSize, int colSize);
    unsigned short** Histogram_calculation(unsigned short** ComplementImage, int rowSize, int colSize, float Angle);
    unsigned short** Complement_Function(unsigned short** InputImage, int rowSize, int colSize);
    unsigned short** Conversion(unsigned short* image, int rowS, int colS);

};

