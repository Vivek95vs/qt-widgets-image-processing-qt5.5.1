#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s1 = new sceneclass();
    s1->setSceneRect(0,0,w,h);
    item = new QGraphicsPixmapItem();
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Icon_PB->hide();
    ui->progressBar->hide();
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(28);
    ui->progressBar->setValue(0);

    QObject::connect(s1,SIGNAL(rightbuttonclicked()),this,SLOT(getbrightness()));
    QObject::connect(s1,SIGNAL(rightbuttonclicked()),this,SLOT(getcontrast()));
}

void MainWindow::getbrightness()
{
    imgMat = Mat(w,h,CV_8UC1,opdata);
    cv::Mat outMat;
    imgMat.convertTo(outMat,-1,1,s1->brightness);
    QImage img = QImage(outMat.data,w,h,QImage::Format_Grayscale8);
    item->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::getcontrast()
{
    imgMat = Mat(w,h,CV_8UC1,opdata);
    cv::Mat outMat;
    imgMat.convertTo(outMat,-1,s1->contrast,s1->brightness);
    QImage img = QImage(outMat.data,w,h,QImage::Format_Grayscale8);
    item->setPixmap(QPixmap::fromImage(img));
//    cv::CLAHE::apply()

    t=(s1->contrast);
    ui->progressBar->setValue(t);
}


void MainWindow::on_Load_PB_clicked()
{
    ui->Icon_PB->show();
    ui->progressBar->show();
    unsigned short *ipdata = new unsigned short[w*h];
    opdata = new unsigned char[w*h];

    FILE *fo;
    QString browse = ("D:\\Test1\\Image_1.dcm");
    fo = fopen(browse.toStdString().c_str(),"rb");
    fread(ipdata,w*h*sizeof(unsigned short),1,fo);

    for (int i=0;i<(w*h);i++)
    {
        opdata[i]=(ipdata[i]*255)/65535;
    }

    QImage img = QImage(opdata,w,h,QImage::Format_Grayscale8);
    QPixmap p_img = QPixmap::fromImage(img);
    item->setPixmap(p_img);
    s1->addItem(item);

    ui->Icon_PB->setFixedSize(25,25);
    QPixmap pixmap("D:\\Ui_Icons\\Contrast\\contrast.png");
    QIcon icon(pixmap);
    ui->Icon_PB->setIcon(icon);
    ui->Icon_PB->setIconSize(QSize(22,22));

    ui->graphicsView->setScene(s1);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
}

MainWindow::~MainWindow()
{
    delete ui;
}


