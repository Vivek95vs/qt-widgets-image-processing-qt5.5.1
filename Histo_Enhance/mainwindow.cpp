#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QFileDialog"
#include "QFile"
#include "QDebug"
#include <thread>
#include <chrono>
#include "QTimer"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enhance=new Enhancement();
    enhanceMat=new EnhanceImage();


//    ui->minslider->setRange(0, 255);
//    ui->minslider->setValue(0);
//    ui->minslider->setToolTip("Minimum");

//    ui->Maxslider->setRange(0, 255);
//    ui->Maxslider->setValue(255);
//    ui->Maxslider->setToolTip("Maximum");

//    ui->brightness->setRange(-100, 100);
//    ui->brightness->setValue(0);
//    ui->brightness->setToolTip("Brightness");

//    ui->contrast->setRange(-100, 100);
//    ui->contrast->setValue(0);
//    ui->contrast->setToolTip("Contrast");

    ui->checkBox->setStyleSheet(R"(
        QCheckBox {
            spacing: 5px;
        }

        QCheckBox::indicator {
            width: 8px;
            height: 8px;
            border-radius: 6px;
            border: 2px solid #555;
            background-color: #fff;
        }

        QCheckBox::indicator:checked {
            background-color: #0ab6f2;
            border-color: #0ab6f2;
        }

        QCheckBox::indicator:hover {
            border-color: #888;
        }

        QCheckBox::indicator:checked:hover {
            border-color: #45a049;
        }

        QCheckBox::indicator:disabled {
            background-color: #ccc;
            border-color: #aaa;
        }
    )");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_LOAD_clicked()
{
//    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/couchtop/*.raw",QDir::currentPath());
//    if (filename.isEmpty())
//       {
//           qDebug()<<"Could not open file";
//       }
//    FILE * Img;
//    Img= fopen(filename.toStdString().c_str(),"rb");

//    unsigned short* Image=new unsigned short[w*h];
//    fread(Image,1,w*h*sizeof(unsigned short),Img);
////    unsigned char* arr=new unsigned char[w*h];

//    dispImg=new unsigned char[w*h];
//    for(int i=0;i<w*h;i++)
//    {
//        dispImg[i]=((Image[i]*255)/4000);
//    }

//    qDebug()<<arr[20];

    typedef unsigned short img;
    typedef itk::Image< img,2>Img;
    typedef itk::ImageFileReader<Img>Reader;
    Reader::Pointer reader=Reader::New();
    Img::Pointer image;
    QString fileName = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Test1/*.dcm",QDir::currentPath());
    reader->SetFileName(fileName.toStdString().c_str());

    typedef itk::GDCMImageIO ImageType;
    ImageType::Pointer gdcmImage=ImageType::New();
    reader->SetImageIO(gdcmImage);
    try
    {
        reader->Update();
    }
    catch (itk::ExceptionObject & e)
    {
        std::cerr << "exception in file reader " << std::endl;
        std::cerr << e << std::endl;
        return;
    }
    itk::MetaDataDictionary dict;
    dict = reader->GetMetaDataDictionary();

    std::string Rows1;
    itk::ExposeMetaData(dict,"0028|0010",Rows1);

    std::string Cols1;
    itk::ExposeMetaData(dict,"0028|0011",Cols1);

    gdcm::ImageReader gdcmReader2;
    gdcmReader2.SetFileName(fileName.toStdString().c_str());
    if( !gdcmReader2.Read() )
    {
        std::cerr << "gdcm read error " << std::endl;
        return ;
    }
    gdcm::File &gdcmFile = gdcmReader2.GetFile();
    gdcm::DataSet &gdcmDS = gdcmFile.GetDataSet();

    QString Rows=Rows1.c_str();
    QString Cols=Cols1.c_str();
    qDebug()<<Rows;
    qDebug()<<Cols;

    image = reader->GetOutput();

    pixelBuffer = image->GetBufferPointer();


    unsigned short minVal = 65535;  // Max for 16-bit
    unsigned short maxVal = 0;      // Min for 16-bit
    unsigned int minLoc = 0;
    unsigned int maxLoc = 0;

    // Iterate through the pixel buffer to find min and max
    for(int i = 0; i < w * h; ++i) {
        if (pixelBuffer[i] < minVal) {
            minVal = pixelBuffer[i];
            minLoc = i;
        }
        if (pixelBuffer[i] > maxVal) {
            maxVal = pixelBuffer[i];
            maxLoc = i;
        }
    }

    qDebug()<<"Value"<<minLoc<<maxLoc;

    dispImg= new unsigned char[w*h];

    qDebug()<<pixelBuffer[0];
    for(int i=0;i<w*h;++i)
    {
        dispImg[i] = pixelBuffer[i]*255/6000;
    }

//    for(int i = 0; i < w * h; ++i) {
//        // Scale the pixel value from 16-bit to 8-bit (assuming the original 16-bit image range is 0-65535)
//        dispImg[i] = static_cast<unsigned char>((static_cast<float>(pixelBuffer[i]) / 65535.0) * 255);
//    }

    myImage = QImage(dispImg,h,w,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    Scene = new QGraphicsScene();
    view = new QGraphicsView(Scene);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
    Scene->addItem(item);

    ui->minslider->setRange(0, 255);
    ui->minslider->setValue(0);
    ui->minslider->setToolTip("Minimum");

    ui->Maxslider->setRange(0, 255);
    ui->Maxslider->setValue(255);
    ui->Maxslider->setToolTip("Maximum");

    ui->brightness->setRange(-100, 100);
    ui->brightness->setValue(0);
    ui->brightness->setToolTip("Brightness");

    ui->contrast->setRange(-100, 100);
    ui->contrast->setValue(100);
    ui->contrast->setToolTip("Contrast");

    plothistogram(dispImg);


//    double minVal, maxVal;
//    cv::Point minLoc, maxLoc;
//    cv::minMaxLoc(originalImage, &minVal, &maxVal, &minLoc, &maxLoc);

//    // Show the results
//    QString result = QString("Max Pixel Value: %1 at (%2, %3)").arg(maxVal).arg(maxLoc.x).arg(maxLoc.y);
//    QLabel *label = new QLabel(result, this);
//    ui->pixel_val->setText(result);
//    qDebug()<<result;

}

void MainWindow::on_Maxslider_valueChanged(int value)
{
    updateFromMinMax();
}

void MainWindow::on_minslider_valueChanged(int value)
{
    updateFromMinMax();
}

void MainWindow::on_brightness_valueChanged(int value)
{
    updateFromBrightnessContrast();
}

void MainWindow::on_contrast_valueChanged(int value)
{
    updateFromBrightnessContrast();
}

//cv::Mat MainWindow::adjustImage(const cv::Mat &image, int min, int max, int brightness, int contrast) {
//    cv::Mat adjustedImage;

//    // Apply brightness and contrast adjustments
//    double alpha = 1.0 + contrast / 100.0;  // Contrast scaling factor
//    double beta = brightness;              // Brightness offset
//    image.convertTo(adjustedImage, CV_8U, alpha, beta);

//    // Apply minimum and maximum intensity thresholds
//    cv::threshold(adjustedImage, adjustedImage, max, 255, cv::THRESH_TRUNC); // Cap at max
//    cv::threshold(adjustedImage, adjustedImage, min, 255, cv::THRESH_TOZERO); // Set below min to 0

//    return adjustedImage;
//}

void MainWindow::updateFromMinMax() {
    int min = ui->minslider->value();
    int max = ui->Maxslider->value();

    // Calculate brightness and contrast based on min and max
    int brightness = (min + max) / 2 - 127; // Center of range mapped to midpoint
    int contrast = max - min;              // Dynamic range of intensity

    ui->brightness->blockSignals(true); // Prevent infinite recursion
    ui->contrast->blockSignals(true);
    ui->brightness->setValue(brightness);
    ui->contrast->setValue(contrast);
    ui->brightness->blockSignals(false);
    ui->contrast->blockSignals(false);

    updateImage();
}

void MainWindow::plothistogram(unsigned char *img)
{
//    qimagehist= e
    qimagehist=enhanceMat->histcal(qimagehist,img,h,w);

    qDebug()<<"QImage width"<<qimagehist.width()<<qimagehist.height();

    QImage scaledImage = qimagehist.scaled(ui->Hist_label->width(), ui->Hist_label->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPainter painter(&scaledImage);
    painter.setPen(QPen(Qt::red, 2));

            // Draw min/max lines based on slider values
    int minValue = ui->minslider->value();
    int maxValue = ui->Maxslider->value();

    int minX = (minValue * scaledImage.width()) / 255;
    int maxX = (maxValue * scaledImage.width()) / 255;

    // Draw min and max lines
    painter.drawLine(minX, 0, minX, scaledImage.height()); // Min line
    painter.drawLine(maxX, 0, maxX, scaledImage.height()); // Max line

    // Optional: Draw the brightness/contrast lines (for example)
    int brightness = ui->brightness->value();
    int contrast = ui->contrast->value();

    // Your logic for contrast/brightness can be reflected as lines
    // For now, we'll just draw two lines to represent them
    int brightnessLine = (brightness + 100) * scaledImage.width() / 200;
    int contrastLine = (contrast + 100) * scaledImage.width() / 200;

    painter.setPen(QPen(Qt::green, 2));
    painter.drawLine(brightnessLine, 0, brightnessLine, scaledImage.height()); // Brightness line

    painter.setPen(QPen(Qt::blue, 2));
    painter.drawLine(contrastLine, 0, contrastLine, scaledImage.height()); // Contrast line

    painter.end();

    qDebug()<<"scaled image"<<scaledImage.width()<<scaledImage.height();
    ui->Hist_label->setPixmap(QPixmap::fromImage(scaledImage));

}

template <typename T>
T clamp(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}


void MainWindow::updateFromBrightnessContrast() {
    int brightness = ui->brightness->value();
    int contrast = ui->contrast->value();

    // Calculate min and max based on brightness and contrast
    int min = 127 - contrast / 2 + brightness;
    int max = 127 + contrast / 2 + brightness;

    ui->minslider->blockSignals(true); // Prevent infinite recursion
    ui->Maxslider->blockSignals(true);
    ui->minslider->setValue(clamp(min, 0, 255));
    ui->Maxslider->setValue(clamp(max, 0, 255));
    ui->minslider->blockSignals(false);
    ui->Maxslider->blockSignals(false);

    updateImage();
}

void MainWindow::updateImage()
{
//    int min = ui->minslider->value();
//    int max = ui->Maxslider->value();
//    int brightness = ui->brightness->value();
//    int contrast = ui->contrast->value();

    ui->Max_label->setText(QString::number(ui->Maxslider->value()));
    ui->Min_label->setText(QString::number(ui->minslider->value()));
    ui->Bright_label->setText(QString::number(ui->brightness->value()));
    ui->contrast_label->setText(QString::number(ui->contrast->value()));


//    qDebug()<<"minimum and max val"<<min<<max<<brightness<<contrast;
//    cv::Mat newImage = adjustImage(originalImage, min, max, brightness, contrast);
// //    imageLabel->setPixmap(QPixmap::fromImage(matToQImage(newImage)));

//    cv::Mat img;
//    img= cv::Mat(height,width,CV_8UC1,dispImg);

    int min = ui->minslider->value();
    int max = ui->Maxslider->value();

    MatImg=new unsigned char[w*h];

    MatImg= enhanceMat->NormalizeMat(MatImg,dispImg,min,max,h,w);

//    cv::Mat adjustedImage;
//    cv::normalize(originalImage, adjustedImage, min, max, cv::NORM_MINMAX);

//    uchar* imgOut2=new uchar [h*w];
//    for(int i=0;i<w*h;i++)
//    {
//        imgOut2[i]=adjustedImage.data[i];
//    }
    QImage q_image3 = QImage(MatImg,w,h,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image3));
    Scene= new QGraphicsScene(this);
    Scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);

    plothistogram(dispImg);

}

void MainWindow::on_Auto_clicked()
{

    std::pair<double, double> result=enhanceMat->Autobrightvalue(dispImg,w,h);

    ui->minslider->setValue(static_cast<int>(result.first));
    ui->Maxslider->setValue(static_cast<int>(result.second));
}

void MainWindow::on_Reset_clicked()
{
    ui->minslider->setValue(0);
    ui->Maxslider->setValue(255);
    ui->brightness->setValue(0);
    ui->contrast->setValue(100);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        qDebug()<<"checked";
    }
    else
    {
        qDebug()<<"not checked";
    }
}

void MainWindow::on_SaveDB_clicked()
{
//    ui->SaveDB->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);");
     ui->SaveDB->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(0, 0, 0);");

     QTimer::singleShot(500, this, [this]() {
         ui->SaveDB->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);");
     });



//     _sleep(10000);
//     ui->SaveDB->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);");
}
