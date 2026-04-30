#ifndef ENHANCEIMAGE_H
#define ENHANCEIMAGE_H

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "QImage"

class EnhanceImage
{
public:
    EnhanceImage();
    cv::Mat originalImage;
    unsigned char *NormalizeMat(unsigned char *img, unsigned char *img1, int min, int max, int size1, int size2);
    std::pair<double, double> Autobrightvalue(unsigned char *img, int size1, int size2);
    QImage histcal(QImage qImage, unsigned char *img, int size1, int size2);
};

#endif // ENHANCEIMAGE_H
