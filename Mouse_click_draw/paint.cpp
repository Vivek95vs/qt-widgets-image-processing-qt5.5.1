#include "paint.h"
#include "ui_paint.h"

#include<QDialog>
#include<QFile>
#include<QDir>
#include<QFileDialog>
#include<QGraphicsPixmapItem>

paint::paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paint)
{
    ui->setupUi(this);
    ui->label->setText("QGraphicsScene To Display Items");
    scene = new paintScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);

}

paint::~paint()
{
    delete ui;
}



void paint::on_pushButton_clicked()
{
    scene->selectedTool=1;
}


void paint::on_pushButton_2_clicked()
{
    scene->selectedTool=2;
}

void paint::on_pushButton_4_clicked()
{
    scene->clear();
}

void paint::on_pushButton_5_clicked()
{
    scene->selectedTool=3;
}

void paint::on_pushButton_6_clicked()
{
    QList<QGraphicsItem *>Items=scene->selectedItems();
    foreach(QGraphicsItem *item, Items)
    {
               scene->removeItem(item);
               delete(item);

    }
}

void paint::on_pushButton_3_clicked()
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
        QImage myImage(arr,3072,3072,QImage::Format_Grayscale8);
        item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
        scene = new paintScene(this);
        view = new QGraphicsView(scene);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->fitInView(item);
        scene->addItem(item);
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        delete[] Image;
        delete[] arr;
}

void paint::on_pushButton_7_clicked()
{
    scene->selectedTool=4;
}
