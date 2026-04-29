#include "enhanceimage.h"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QImage>



using namespace cv;

EnhanceImage::EnhanceImage()
{

}

/*!
 * \brief MainWindow::on_Brightness_SB_valueChanged
 * function to adjust  brightness
 */
uchar* EnhanceImage::enhanceBrightness(unsigned char* dispImg, int height, int width,double alpha, double beta)
{

    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg);

    imgbuf.convertTo(img,-1,static_cast<double>(alpha)/100*3.0+1,beta);
    //imgbuf.convertTo(img,-1,(alpha+1),beta);

    //imgbuf.convertTo(img,-1,alpha,beta);

    uchar* imgOut=new uchar [height*width];
    for(int i=0;i<height*width;i++)
        imgOut[i]=img.data[i];

    return imgOut;

}

uchar* EnhanceImage::enhanceContrast(unsigned char* dispImg, int height, int width, double alpha, double beta)
{

    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg);
    imgbuf.convertTo(img,-1,static_cast<double>(alpha)/100*3.0+1,beta);

    //imgbuf.convertTo(img,-1,(alpha+1),beta);

    uchar* imgOut=new uchar [height*width];
    for(int i=0;i<height*width;i++)
        imgOut[i]=img.data[i];

    return imgOut;

}




uchar* EnhanceImage::medianFilter(unsigned char* dispImg,int height,int width)
{

    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg);

    cv::medianBlur(imgbuf,img,5);

    uchar* imgOut=new uchar [height*width];
    for(int i=0;i<height*width;i++)
        imgOut[i]=img.data[i];

    return imgOut;

}
uchar* EnhanceImage::invertFilter(unsigned char* dispImg,int height,int width)
{
    unsigned char* dispImg2=new unsigned char[height*width];
    for(int i=0;i<width*height;++i)
    {
        dispImg2[i] = 255-dispImg[i];
    }
    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg2);
    imgbuf.convertTo(img,-1,1,0);

    uchar* imgOut=new uchar [height*width];
    for(int i=0;i<height*width;i++)
        imgOut[i]=img.data[i];


    delete[] dispImg2;

    return imgOut;

}

void EnhanceImage::NormalizeProjectionImage(unsigned short *inpimg,int size)
{
    cv::Mat rotImg;
    cv::Mat imgbuf = cv::Mat(size,size,CV_16UC1,inpimg);
    for(int i=0;i<10; i++){
        for(int j=0; j<size; j++){
            imgbuf.at<unsigned short>(i,j)=imgbuf.at<unsigned short>(i+10,j);

        }
    }

    for(int j=0; j<size; j++){
        imgbuf.at<unsigned short>(size-3,j)=imgbuf.at<unsigned short>(size-5,j);
        imgbuf.at<unsigned short>(size-2,j)=imgbuf.at<unsigned short>(size-4,j);
        imgbuf.at<unsigned short>(size-1,j)=imgbuf.at<unsigned short>(size-3,j);
    }

    for(int j=0; j<size; j++){
        imgbuf.at<unsigned short>(j,size-3)=imgbuf.at<unsigned short>(j,size-5);
        imgbuf.at<unsigned short>(j,size-2)=imgbuf.at<unsigned short>(j,size-4);
        imgbuf.at<unsigned short>(j,size-1)=imgbuf.at<unsigned short>(j,size-3);
    }


    cv::Mat imgbuf1 = cv::Mat(size,size,CV_16UC1,(ushort*)imgbuf.data);
    // get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((imgbuf1.cols)/2.0, (imgbuf1.rows)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, 90, 1.0);
    cv::warpAffine(imgbuf1, imgbuf1, rot, Size(imgbuf.cols, imgbuf.rows));
    imgbuf1.convertTo(rotImg,-1,1,0);


    //cv::Mat cvImage = cv::Mat (size, size, CV_16UC1,inpimg);
    medianBlur(rotImg, rotImg,3);
    GaussianBlur(rotImg,rotImg,Size(5, 5),0);
    for(int i=0;i<10; i++){
        for(int j=0; j<size; j++){
            rotImg.at<unsigned short>(i,j)=rotImg.at<unsigned short>(i+10,j);
        }
    }

    normalize(rotImg,rotImg,940,25500, NORM_MINMAX, CV_16UC1);
    medianBlur(rotImg, rotImg,3);
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            inpimg[i*size+j]=rotImg.at<unsigned short>(i,j);
        }
    }
}

QImage EnhanceImage::translateQImage(QImage img, double shiftX, double shiftY)
{

     cv::Mat trans = (cv::Mat_<double>(2,3) << 1, 0, shiftX, 0, 1, shiftY);
   //  cv::Mat trans = cv::Mat(2,3,CV_8UC1,[1, 0, shiftX, 0, 1, shiftY]);
  //   cv::Mat trans = [1 0 shiftX]
     cv::Mat imgbuf =  cv::Mat(img.width(),img.height(),CV_8UC1,(uchar*)img.constBits(), img.bytesPerLine());
     cv::warpAffine(imgbuf, imgbuf, trans, Size(imgbuf.cols, imgbuf.rows));

     QImage image( imgbuf.data,imgbuf.cols, imgbuf.rows,static_cast<int>(imgbuf.step),QImage::Format_Grayscale8 );
//    //return
      return image;
}

unsigned char* EnhanceImage::translatecharImage(unsigned char *img, int size1, int size2,double shiftX, double shiftY)
{

     cv::Mat trans = (cv::Mat_<double>(2,3) << 1, 0, shiftX, 0, 1, shiftY);
   //  cv::Mat trans = cv::Mat(2,3,CV_8UC1,[1, 0, shiftX, 0, 1, shiftY]);
  //   cv::Mat trans = [1 0 shiftX]
     cv::Mat imgbuf =  cv::Mat(size1,size2,CV_8UC1,img);
     cv::warpAffine(imgbuf, imgbuf, trans, Size(imgbuf.cols, imgbuf.rows));

     for(int i=0;i<size1;i++){
         for(int j=0;j<size2;j++){
             img[i*size1+j]=imgbuf.at<unsigned char>(i,j);
         }
     }
//    //return
      return img;
}








///*!
// * \brief MainWindow::on_actionHistogram_Equalization_triggered
// * function for histogram equalization
// */
//void EnhanceImage::on_actionHistogram_Equalization_triggered(bool checked)
//{
//    if(count<1 && OfflineMode==1)
//        return;

//    if(twoview==1)
//        return;
//    streamOff <<"Histogram equalization triggered"<<endl;
//    hideOverlay();
//    if(ui->FOV_PB->isChecked())
//        ui->FOV_PB->setChecked(false);
//    qApp->processEvents();
//    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg);
//    cv::equalizeHist(imgbuf,img);
//    q_image = QImage(img.data,width,height,QImage::Format_Grayscale8);
//    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));
//    curScene->addItem(item);
//    ui->graphicsView->setScene(curScene);
//    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);

//    showOverlay();
//    ui->FOV_PB->setChecked(true);
//    streamOff <<"Histogram equalization done"<<endl;
//}

