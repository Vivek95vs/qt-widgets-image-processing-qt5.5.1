#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/opencv.hpp>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage Mat2QImage(const Mat &src) {
    if (src.empty())
        return QImage();

    if (src.type() == CV_8UC1) { // Grayscale image
        return QImage(src.data, src.cols, src.rows, src.step, QImage::Format_Grayscale8).copy();
    } else if (src.type() == CV_8UC3) { // RGB image
        Mat rgbImage;
        cvtColor(src, rgbImage, COLOR_BGR2RGB);
        return QImage(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step, QImage::Format_RGB888).copy();
    }

    return QImage();
}

void MainWindow::on_pushButton_clicked()
{

    Mat image = imread("D:\\Gantry\\FinalStiched before.jpg");
    if (image.empty()) {
        qDebug() << "Image not found or empty!";
    }

    // Convert BGR to RGB
    cvtColor(image, image, COLOR_BGR2RGB);

    // Threshold to detect red pixels
    Mat mask;
    inRange(image, Scalar(0, 0, 100), Scalar(100, 100, 255), mask);

    // Check if mask is empty
    if (mask.empty()) {
        qDebug() << "Mask is empty!";
    }

    qDebug() << "Mask is not empty!";

    // Find contours
    std::vector<std::vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Check if contours were found
    if (contours.empty()) {
        qDebug() << "No contours found!";
    }

    // Draw contours on the image
    Mat result = image.clone();
    drawContours(result, contours, -1, Scalar(0, 255, 0), 2);

    // Convert Mat to QImage
    QImage qImage = Mat2QImage(result);

    QString savePath = "D:\\Gantry\\output_image.jpg";
    if(qImage.save(savePath)) {
        qDebug() << "Image saved successfully to:" << savePath;
    } else {
        qDebug() << "Failed to save image!";

}

}
