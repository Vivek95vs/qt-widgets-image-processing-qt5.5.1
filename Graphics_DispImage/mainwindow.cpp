#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("Image Viewer");

    FILE * Img;
    Img= fopen("D:/Workflow/Test images/rawImage_23_09_2019_10_34_15.raw","r");
    int w=3072,h=3072;
    unsigned short* Image=new unsigned short[w*h];
    fread(Image,1,w*h*sizeof(unsigned short),Img);
    unsigned char* arr=new unsigned char[w*h];
    qDebug()<<Image[0];
    for(int i=0;i<w*h;i++)
    {
        arr[i]=((Image[i]*255)/65535);
    }
    qDebug()<<arr[0];
    QImage myImage(arr,3072,3072,QImage::Format_Grayscale8);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);

    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene->addItem(item);
//    for(int i=0;i<w*h;i++)
//    {
//        qDebug()<<arr[i];
//    }
//    unsigned char* Data = (unsigned char*)Image.data();
//    QImage myImage(Data,1200,700,QImage::Format_Grayscale8);
//    unsigned short bufferImage[1][49152];
//    fread(&bufferImage[0][0], 49152*sizeof(unsigned short),1, Img);
//    unsigned char* Data = (unsigned char*)bufferImage;
//    qDebug()<<array.length();
//    qDebug()<<sizeof(array);
//    qDebug()<<Data[1584*1828-1];
//    Img.close();

//    QImage myImage(Data, 1200, 700, QImage::Format_Grayscale8);
//    scene = new QGraphicsScene(this);
//    view = new QGraphicsView(scene);
//    ui->graphicsView->setScene(scene);

//    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
//            item = new QGraphicsPixmapItem(QPixmap(Img));
//    scene->addItem(item);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    QFile Img = QFileDialog::getOpenFileName(this,"Open Test Image",QDir::currentPath());
//    if (!Img.open(QFile::ReadOnly))
//       {
//           qDebug()<<"Could not open file";
//       }
//    unsigned char * bufferRow = new unsigned char[BUFFERSIZE];
//    int size=2048*1536;
//        unsigned char * Data=new unsigned char[size];
//        unsigned char * Redp = Data;

//        for(int rowNum=0;rowNum<1536;rowNum++){
//            // Read an entire row
//            fread(reinterpret_cast<char*>(bufferRow), BUFFERSIZE);
//            if(rowNum%2==0){
//                for(int i=0;i<BUFFERSIZE;i+=3){
//                    *Redp++=bufferRow[i];
//                }
//            }
//            QImage myImage(reinterpret_cast<char*>(Data), size,QImage::Format_Grayscale8);
//            scene = new QGraphicsScene(this);
//            view = new QGraphicsView(scene);
//            ui->graphicsView->setScene(scene);
//            item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));

//    int **matrix_image, test;
//    int i, j, rows=100, colums=100;

//        //i create dinamic rows
//        matrix_image = (int **) malloc (rows*sizeof(int*));

//        //i create dinamic colums
//        for(i=0;i<rows;i++)
//        {
//             matrix_image[i] = (int*) malloc (colums*sizeof(int));
//        }
//        //i copy values to matriz_image
//        for(i=0;i<rows;i++)
//        {
//            for(j=0;j<colums;j++)
//            {
//                //fscanf(Img,&test);
//                matrix_image[i][j]=test;
//                //qDebug()<< test;
//            }
//        }
//        //i print matriz
//        for(i=0;i<rows;i++)
//        {
//            for(j=0;j<colums;j++)
//            {
//                qDebug()<<matrix_image[i][j];
//            }
//            qDebug()<<endl;
//            QByteArray array =&test.readAll();
//            unsigned char* Data = (unsigned char*)&array.data()[0];
//            QImage myImage(Data,1200,700,QImage::Format_Grayscale8);
//            scene = new QGraphicsScene(this);
//            view = new QGraphicsView(scene);
//            ui->graphicsView->setScene(scene);

//            item = new QGraphicsPixmapItem(QPixmap::fromImage(matrix_image));
//            item = new QGraphicsPixmapItem(QPixmap(test));
//            scene->addItem(item);


//                QByteArray array =Img.readAll();
//                qDebug()<<array.length();
//                qDebug()<<sizeof(array);
//                qDebug()<<array[2];
//                unsigned char* Data = (unsigned char*)array.data();
//                Img.close();
//                qDebug()<<(unsigned short*)array.data()<<Data[1];
//                qDebug()<<Data[1584*1828-1];
//                QImage myImage(Data,3072,3072,QImage::Format_Grayscale8);
//                scene = new QGraphicsScene(this);
//                view = new QGraphicsView(scene);
//                ui->graphicsView->setScene(scene);

//                item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
//                item = new QGraphicsPixmapItem(QPixmap(Img));
//                scene->addItem(item);
    }
