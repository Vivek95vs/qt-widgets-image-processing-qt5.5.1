#include "enhanceimage.h"


using namespace cv;

EnhanceImage::EnhanceImage()
{

}

unsigned char* EnhanceImage::NormalizeMat(unsigned char *img,unsigned char *img1,int min, int max, int size1, int size2)
{
    cv::Mat adjustedImage;
    originalImage=cv::Mat(size1,size2,CV_8UC1,img1);
    cv::normalize(originalImage, adjustedImage, min, max, cv::NORM_MINMAX);

    for(int i=0;i<size1;i++){
        for(int j=0;j<size2;j++){
            img[i*size1+j]=adjustedImage.at<unsigned char>(i,j);
        }
    }
//    //return
     return img;

}

std::pair<double, double> EnhanceImage::Autobrightvalue(unsigned char *img,int size1,int size2) {


    double minVal, maxVal;

    cv::Mat adjustedImage=cv::Mat(size1,size2,CV_8UC1,img);
    cv::minMaxLoc(adjustedImage, &minVal, &maxVal);

    // Optionally ignore outliers for better results
    cv::Mat sorted;
    cv::sort(adjustedImage.reshape(1, 1), sorted, cv::SORT_ASCENDING);

    int ignorePixels = static_cast<int>(0.01 * adjustedImage.total()); // 1% exclusion
    minVal = sorted.at<uchar>(ignorePixels);                            // Exclude low outliers
    maxVal = sorted.at<uchar>(sorted.total() - ignorePixels - 1);      // Exclude high outliers

    return {minVal,maxVal};
}

QImage EnhanceImage::histcal(QImage qImage,unsigned char *img, int size1,int size2)
{
    cv::Mat adjustedImage=cv::Mat(size1,size2,CV_8UC1,img);
    int histSize = 256; // Number of bins
    float range[] = {0, 256}; // Pixel intensity range
    const float *histRange = {range};
    cv::Mat hist;
    cv::calcHist(&adjustedImage, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    // Normalize the histogram to fit within the display area
    int histWidth = 512, histHeight = 400;
    int binWidth = cvRound((double) histWidth / histSize);
    cv::normalize(hist, hist, 0, histHeight, cv::NORM_MINMAX);

    // Create an image to draw the histogram
    cv::Mat histImage(histHeight, histWidth, CV_8UC1, cv::Scalar(255)); // White background
    for (int i = 1; i < histSize; i++) {
        cv::line(
            histImage,
            cv::Point(binWidth * (i - 1), histHeight - cvRound(hist.at<float>(i - 1))),
            cv::Point(binWidth * i, histHeight - cvRound(hist.at<float>(i))),
            cv::Scalar(0), // Black line
            2,
            8,
            0
        );
    }

    // Convert to QImage for display
    qImage=QImage(histImage.data, histImage.cols, histImage.rows, histImage.step, QImage::Format_Grayscale8);
//    histogramLabel->setPixmap(QPixmap::fromImage(qImage));
    QString filePath ="D:\\10\\hist.png";
    cv::imwrite(filePath.toStdString(), histImage);

    return qImage;

}
