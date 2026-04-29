#ifndef ENHANCEIMAGE_H
#define ENHANCEIMAGE_H


#include <QApplication>

extern int FrameRateMode;
class EnhanceImage
{
public:
    EnhanceImage();
    uchar * enhanceBrightness(unsigned char *dispImg, int height, int width, double alpha, double beta);


    uchar *enhanceContrast(unsigned char *dispImg, int height, int width, double alpha, double beta);
    uchar *medianFilter(unsigned char *dispImg, int height, int width);
    uchar *invertFilter(unsigned char *dispImg, int height, int width);
    void NormalizeProjectionImage(unsigned short *inpimg, int size);    
    QImage translateQImage(QImage img, double shiftX, double shiftY);   
    unsigned char *translatecharImage(unsigned char *img, int size1, int size2, double shiftX, double shiftY);

private:

};

#endif // ENHANCEIMAGE_H
