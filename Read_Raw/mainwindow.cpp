#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GpuImageEnhancement.cuh"

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

void MainWindow::on_Load_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/RAwMLC/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short* Image=new unsigned short[w*h];
    fread(Image,1,w*h*sizeof(unsigned short),Img);

    unsigned short *Imageirayptr=new unsigned short[w*h];


    qDebug()<<"gpuStartImageEnhancement";
    gpuStartImageEnhancement(Image,Imageirayptr,w,h);
    for(int i=0;i<w*h;i++)
    {
        arr[i]=((Imageirayptr[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,1536,1536,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
    scene->addItem(item);
}
