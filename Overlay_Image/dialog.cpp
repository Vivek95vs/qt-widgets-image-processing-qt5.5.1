#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//    opt=new Operation();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_PB_LoadImage1_clicked()
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
    item1 = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene = new QGraphicsScene();
    view1 = new QGraphicsView(scene);

    ui->graphicsView1->setScene(scene);
    ui->graphicsView1->fitInView(item1,Qt::KeepAspectRatio);
    scene->addItem(item1);
}

void Dialog::on_PB_LoadImage2_clicked()
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
    item2 = new QGraphicsPixmapItem(QPixmap::fromImage(myImage1));
    scene = new QGraphicsScene();

    view2 = new QGraphicsView(scene);
    ui->graphicsView2->setScene(scene);
    ui->graphicsView2->fitInView(item2,Qt::KeepAspectRatio);
    scene->addItem(item2);
}

void Dialog::on_PB_Overlay_clicked()
{
    //Overlay
    arr2=new unsigned char[w*h];
    for(int i=0;i<w*h;i++)
    {
            arr2[i]=((arr[i])+(arr1[i]));
    }
    QImage myImage2(arr2,3072,3072,QImage::Format_Grayscale8);
    item3 = new QGraphicsPixmapItem(QPixmap::fromImage(myImage2));
    scene = new QGraphicsScene(this);
    view2 = new QGraphicsView(scene);
    ui->graphicsView3->setScene(scene);
    ui->graphicsView3->fitInView(item3,Qt::KeepAspectRatio);
    scene->addItem(item3);

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

void Dialog::on_PB_Quad_clicked()
{
    //    Quadrant

        QPixmap px1=QPixmap::fromImage(myImage.scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        QPixmap px2=QPixmap::fromImage(myImage1.scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        scene = new QGraphicsScene();
        item3=scene->addPixmap(px1.copy(0,0,w/2,h/2));
        item3->setPos(0,0);
        item3=scene->addPixmap(px1.copy(w/2,h/2,w/2,h/2));
        item3->setPos(w/2,h/2);
        item3=scene->addPixmap(px2.copy(w/2,0,w/2,h/2));
        item3->setPos(w/2,0);
        item3=scene->addPixmap(px2.copy(0,h/2,w/2,h/2));
        item3->setPos(0,h/2);
        view3 = new QGraphicsView(scene);
        ui->graphicsView3->setScene(scene);
        ui->graphicsView3->fitInView(item3,Qt::KeepAspectRatio);
//        scene->addItem(item3);
}

void Dialog::on_PB_CheckerBoard_clicked()
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
    scene=new QGraphicsScene();
    p1=scene->addPixmap(px4.copy(0,0,w,h));
    p2=scene->addPixmap(px3.copy(0,0,w,h));
    view3=new QGraphicsView(scene);
    ui->graphicsView3->setScene(scene);
    ui->graphicsView3->fitInView(p1,Qt::KeepAspectRatio);
}

void Dialog::on_PB_Toggle_clicked()
{

//    scene->clear();
//    double o1,o2;
    QPixmap px1=QPixmap::fromImage(myImage,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPixmap px2=QPixmap::fromImage(myImage1,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    scene=new QGraphicsScene();
    p1=scene->addPixmap(px1.copy(0,0,w,h));
//    p1->setOpacity(0);

    p2=scene->addPixmap(px2.copy(0,0,w,h));
//    p2->setOpacity(0);

    view3=new QGraphicsView(scene);
    ui->graphicsView3->setScene(scene);
//    ui->graphicsView3->fitInView(p1,Qt::KeepAspectRatio);

//    if(pressed==0)
//    {
//        p2->setOpacity(0);
//        p2->setFlag(QGraphicsItem::ItemIsMovable);
//    }
//    else
//    {
//        p1->setOpacity(1);
//        p1->setFlag(QGraphicsItem::ItemIsMovable);
//    }

}


void Dialog::on_pushButton_toggled(bool checked)
{
    QPixmap px1=QPixmap::fromImage(myImage,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPixmap px2=QPixmap::fromImage(myImage1,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    scene=new QGraphicsScene();
    p1=scene->addPixmap(px1.copy(0,0,w,h));
//    p1->setOpacity(0);

    p2=scene->addPixmap(px2.copy(0,0,w,h));
    p2->setOpacity(0);

//    view3=new QGraphicsView(scene);
//    ui->graphicsView3->setScene(scene);
//    ui->graphicsView3->fitInView(p1,Qt::KeepAspectRatio);

    checked=true;
    if(checked==1)
    {
        ui->graphicsView3->fitInView(p1,Qt::KeepAspectRatio);
        p1->setOpacity(1);
        p1->setFlag(QGraphicsItem::ItemIsMovable);
    }
    else
    {
        ui->graphicsView3->fitInView(p2,Qt::KeepAspectRatio);
        p2->setOpacity(1);

        p2->setFlag(QGraphicsItem::ItemIsMovable,false);
    }

}

void Dialog::on_PB_Togglecheck_clicked()
{
    QPixmap px1=QPixmap::fromImage(myImage,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPixmap px2=QPixmap::fromImage(myImage1,Qt::ColorOnly).scaled(QSize(w,h),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    scene=new QGraphicsScene();
    p1=scene->addPixmap(px1.copy(0,0,w,h));
    p2=scene->addPixmap(px2.copy(0,0,w,h));
    if(ui->PB_Togglecheck->isChecked())
    {

        view3=new QGraphicsView(scene);
        ui->graphicsView3->setScene(scene);
        p2->setOpacity(0);
        ui->graphicsView3->fitInView(p1,Qt::KeepAspectRatio);
        p1->setFlag(QGraphicsItem::ItemIsMovable);
    }
    else
    {
        view3=new QGraphicsView(scene);
        ui->graphicsView3->setScene(scene);
        p1->setOpacity(0);
        ui->graphicsView3->fitInView(p2,Qt::KeepAspectRatio);
        p2->setFlag(QGraphicsItem::ItemIsMovable);
    }
}
