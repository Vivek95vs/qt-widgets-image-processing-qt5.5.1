#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <QDebug>

using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{

 QCoreApplication a(argc, argv);
//char * imgpath = "D:/Workflow/Test images/rawImage_23_09_2019_10_34_15.raw";
//FILE * f = fopen(imgpath, "rb");
//if ( ! f )
//{
//    qDebug()<<"bad path :";
//    return -1;
//}
//char pixels[256*256];
//fread(pixels,256*256,1,f);
//fclose(f);

//cv::Mat img(256,256,CV_8UC1,pixels);
//cv::imshow("Proj_265.raw",img);

 const std::string file_path = "D:/Workflow/Test images/rawImage_23_09_2019_10_34_15.raw";
     std::ifstream fin;
     // Note that binary read mode must be specified here
     fin.open(file_path,  std::ios::binary);
     if (!fin) {
         std::cerr << "open failed: " << file_path << std::endl;
     }
     // The seek function will move the marker to the end of the input stream
     fin.seekg(0, fin.end);
     // tell will tell the number of bytes in the entire input stream (from the beginning to the mark)
     int length = fin.tellg();
     // Move the marker to the beginning of the stream
     fin.seekg(0, fin.beg);
     std::cout << "file length: " << length << std::endl;

     // load buffer
     char* buffer = new char [length];
     // The read function reads (copy) each byte of length in the stream to buffer
     fin.read(buffer, length);

     // construct opencv mat and show image
     cv::Mat image(cv::Size(1280, 800), CV_8UC1, buffer);
     cv::imshow("test", image);
     cv::waitKey();
    return a.exec();
}
