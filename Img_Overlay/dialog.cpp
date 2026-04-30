#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    const int w=3072,h=3072;
    unsigned short* Image=new unsigned short[w*h];
    fread(Image,1,w*h*sizeof(unsigned short),Img);
    unsigned char* arr=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
        arr[i]=((Image[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,3072,3072,QImage::Format_Grayscale8);
    item1 = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item1,Qt::KeepAspectRatio);
    scene->addItem(item1);
}

void Dialog::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img1;
    Img1= fopen(filename.toStdString().c_str(),"rb");

    const int w=3072,h=3072;
    unsigned short* Image1=new unsigned short[w*h];
    fread(Image1,1,w*h*sizeof(unsigned short),Img1);
    unsigned char* arr1=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
        arr1[i]=((Image1[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage1=QImage(arr1,3072,3072,QImage::Format_Grayscale8);
    item2 = new QGraphicsPixmapItem(QPixmap::fromImage(myImage1));
    scene1 = new QGraphicsScene();

    view1 = new QGraphicsView(scene1);
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(item2,Qt::KeepAspectRatio);
    scene1->addItem(item2);
}

void Dialog::on_pushButton_3_clicked()
{
//    QImage myImage2;
//    for(int i=0;i<w;i++)
//    {
//        for(int j=0;j<h;j++)
//        {
//            myImage2(i,j)=(myImage(i,j)+myImage1(i,j))/2;
//    }
//    }
//    QImage myImage3(myImage2,3072,3072,QImage::Format_Grayscale8);
//    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage2));
//    scene = new QGraphicsScene(this);
//    view1 = new QGraphicsView(scene);
//    ui->graphicsView3->setScene(scene);
//    ui->graphicsView3->fitInView(item,Qt::KeepAspectRatio);
//    scene->addItem(item);

        arr2=new unsigned char[w*h];
        for(int i=0;i<w*h;i++)
        {
                arr2[i]=((arr[i])+(arr1[i]))/2.0;
        }
        QImage myImage2(arr2,3072,3072,QImage::Format_Grayscale8);
        item3 = new QGraphicsPixmapItem(QPixmap::fromImage(myImage2));
        scene2 = new QGraphicsScene(this);
        view2 = new QGraphicsView(scene2);
        ui->graphicsView3->setScene(scene2);
        ui->graphicsView3->fitInView(item3,Qt::KeepAspectRatio);
        scene->addItem(item3);

//    double gViewFoffset[2];
//    double gViewMoffset[2];

//    QPixmap px1=QPixmap::fromImage(myImage);
//    QPixmap px2=QPixmap::fromImage(myImage1);

//    p1=scene2->addPixmap(px1.copy(gViewFoffset[0]/2,gViewFoffset[1]/2,w,h));
//    p1->setOpacity(1);

//    p2=scene2->addPixmap(px2.copy(gViewMoffset[0]/2,gViewMoffset[1]/2,w,h));
//    p2->setOpacity(1);

//        p2->setFlag(QGraphicsItem::ItemIsMovable);

//        item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage2));
//        scene2 = new QGraphicsScene(this);
//        view2 = new QGraphicsView(scene);
//        ui->graphicsView3->setScene(scene2);
//        ui->graphicsView3->fitInView(p2,Qt::KeepAspectRatio);
//        scene->addItem(p2);

}
