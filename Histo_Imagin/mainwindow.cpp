#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QFileDialog"
#include "QFile"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enhance = new ImageEnhancementNew();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_Load_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/couchtop/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");


    width=3072;
    height=3072;

     qDebug()<<"Image----";


//    width = ImgWidth;
//    height = ImgHeight;

    dispImg= new unsigned char[width*height];
    radbuf = new unsigned short[3072*3072];

    fread(radbuf,sizeof(unsigned short),3072*3072,Img);

    qDebug()<<"Image----";


    img = new unsigned short[3072*3072];
    enhance->StartImageEnhancement(radbuf,img,height,width);

    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = img/*image->GetBufferPointer()*/[i]*255.0/65535.0;
    }
    qDebug()<<"Image----"<<img[100];

    myImage = QImage(dispImg,3072,3072,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    Scene = new QGraphicsScene();
    view = new QGraphicsView(Scene);
    ui->graphicsView->setScene(Scene);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
    Scene->addItem(item);
}
