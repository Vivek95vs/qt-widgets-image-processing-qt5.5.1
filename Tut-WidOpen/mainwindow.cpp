#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Mat img=imread("D:/Workflow/Test images/test.jpg",IMREAD_UNCHANGED);
    if (img.empty()) {
            qDebug() << "Image File Not Found" << endl;
        }
    String windowName = "Image";
    namedWindow(windowName);
    imshow(windowName, img);
    waitKey(0);
}


MainWindow::~MainWindow()
{
    delete ui;
}
