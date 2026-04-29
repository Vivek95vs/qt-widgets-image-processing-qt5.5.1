#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_PB_Load1_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");

    unsigned short* Image=new unsigned short[w*h];
    fread(Image,1,w*h*sizeof(unsigned short),Img);
//    unsigned char* arr=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
        arr[i]=((Image[i]*255)/65535);
    }
//    qDebug()<<arr[20];
    myImage = QImage(arr,3072,3072,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new customscene();
    view = new QGraphicsView(scene);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    scene->addItem(item);
}

void MainWindow::on_PB_load2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img1;
    Img1= fopen(filename.toStdString().c_str(),"rb");
    unsigned short* Image1=new unsigned short[w*h];
    fread(Image1,1,w*h*sizeof(unsigned short),Img1);
//    unsigned char* arr1=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
        arr1[i]=((Image1[i]*255)/65535);
    }
    myImage1=QImage(arr1,3072,3072,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage1));
    scene = new customscene();

    view = new QGraphicsView();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    scene->addItem(item);
}

void MainWindow::on_PB_overlay_clicked()
{
    //Overlay
    arr2=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
            arr2[i]=((arr[i])+(arr1[i]));
    }
    QImage myImage2(arr2,3072,3072,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage2));
    scene = new customscene();
    view = new QGraphicsView();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    scene->addItem(item);

    //Overlay
//      QPixmap px1=QPixmap::fromImage(myImage);
//      QPixmap px2=QPixmap::fromImage(myImage1);

//      QPixmap px(px1.width(),px1.height());
//      px.fill(Qt::transparent);
//      QPainter painter(&px);
//      painter.drawPixmap(0,0,px1);
//      painter.drawPixmap(w,h,px2);

//        QPixmap px1=QPixmap::fromImage(myImage);
//        QPixmap px2=QPixmap::fromImage(myImage1);


//      scene=new QGraphicsScene();
//      item3=scene->addPixmap(0,0,px1);
//      item3->setPos(w,h);
//      view3=new QGraphicsView(scene);
//      ui->graphicsView3->setScene(scene);
//      ui->graphicsView3->fitInView(item3,Qt::KeepAspectRatio);
//      scene->addItem(item3);
}

void MainWindow::on_PB_Quadrant_clicked()
{
    //    Quadrant

    QPixmap px1=QPixmap::fromImage(myImage.scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    QPixmap px2=QPixmap::fromImage(myImage1.scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    scene = new customscene();
    item=scene->addPixmap(px1.copy(0,0,w/2,h/2));
    item->setPos(0,0);
    item=scene->addPixmap(px1.copy(w/2,h/2,w/2,h/2));
    item->setPos(w/2,h/2);
    item=scene->addPixmap(px2.copy(w/2,0,w/2,h/2));
    item->setPos(w/2,0);
    item=scene->addPixmap(px2.copy(0,h/2,w/2,h/2));
    item->setPos(0,h/2);
    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,w,h);
//        scene->addItem(item3);
}

void MainWindow::on_PB_checker_clicked()
{
    //Checker board

    myImage=myImage.convertToFormat(QImage::Format_ARGB32);
    int n=10;
    int s=myImage.width();
    int sc=ceil((s/n));
    int s1=myImage.height();
    int sc1=ceil((s1/n));

    for (int i = 0;i<n;++i)
    {
       for(int j = 0;j<n;++j)
       {
           if ((i+j)%2==0)
             {
               for (int k = (j)*sc1;k<(j+1)*sc1;k++)
               {
                  for (int l = (i)*sc;l<(i+1)*sc;l++)
                  {
                            myImage.setPixel(l,k,qRgba(0,0,0,0));

                  }
               }
           }
       }
    }

    QPixmap px3=QPixmap::fromImage(myImage,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPixmap px4=QPixmap::fromImage(myImage1,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    scene = new customscene();
    p1=scene->addPixmap(px4.copy(0,0,w,h));
    p2=scene->addPixmap(px3.copy(0,0,w,h));
    view=new QGraphicsView();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(p1);
}

void MainWindow::on_PB_toggle_clicked()
{
    QPixmap px1=QPixmap::fromImage(myImage,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPixmap px2=QPixmap::fromImage(myImage1,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    scene = new customscene();
    p1=scene->addPixmap(px1.copy(0,0,w,h));
    p2=scene->addPixmap(px2.copy(0,0,w,h));
    p2->setFlag(QGraphicsItem::ItemIsMovable);

    if(ui->PB_toggle->isChecked())
    {

        view=new QGraphicsView(scene);
        ui->graphicsView->setScene(scene);
        scene->setSceneRect(0,0,w,h);
        p2->setOpacity(1);
        ui->graphicsView->fitInView(p1);
    }
    else
    {
        view=new QGraphicsView(scene);
        ui->graphicsView->setScene(scene);
        scene->setSceneRect(0,0,w,h);
        p1->setOpacity(0);
        ui->graphicsView->fitInView(p2);

    }
}

void MainWindow::on_PB_Rectangle_clicked()
{
    scene->selectedTool=2;
}

void MainWindow::on_PB_clearall_clicked()
{
    scene->clear();
}

void MainWindow::on_PB_Rect_clicked()
{
    scene->selectedTool=1;
}
