#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QCursor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene();
    item = new QGraphicsPixmapItem();
    ui->graphicsView->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
            qDebug()<<"qDebug 1: AxialView";

            int x = QCursor::pos().x();
            int y = QCursor::pos().y();
            qDebug() << "I am here -> (" + QString::number(x) + "," + QString::number(y) + ")";
            //sceneSelected=1;  // 28/07/2021
            return true;
    }
}

void MainWindow::on_pushButton_clicked()
{
    unsigned short *ipdata = new unsigned short[w*h];
    opdata = new unsigned char[w*h];

    FILE *fo;
    QString browse = ("D:\\Test1\\Img1_1.dcm");
    fo = fopen(browse.toStdString().c_str(),"rb");
    fread(ipdata,w*h*sizeof(unsigned short),1,fo);

    for (int i=0;i<(w*h);i++)
    {
        opdata[i]=(ipdata[i]*255)/65535;
    }

    QImage img = QImage(opdata,w,h,QImage::Format_Grayscale8);
    QPixmap p_img = QPixmap::fromImage(img);
    item->setPixmap(p_img);
    scene->addItem(item);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
}
