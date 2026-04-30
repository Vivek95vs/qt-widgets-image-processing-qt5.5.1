#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <QDebug>

using namespace cv;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Mat img = Mat(1792,1344, CV_8UC3);
    img = imread("D:/Workflow/Test images/Proj_265.raw", IMREAD_UNCHANGED);
    if(img.empty()){
    qDebug()<<"unable to read image";
    }
    String windowName = "Image";
    namedWindow(windowName);
    imshow(windowName, img);

    return a.exec();
}

