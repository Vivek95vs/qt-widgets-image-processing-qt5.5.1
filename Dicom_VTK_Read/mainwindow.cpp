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

void MainWindow::on_PB_Load_clicked()
{
    vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    QString fileName = QFileDialog::getOpenFileName(this,"Open Test Image","D:/Workflow/Test images/*.dcm",QDir::currentPath());
    reader->SetFileName(fileName.toStdString().c_str());
    reader->Update();


    vtkSmartPointer<vtkImageReslice>flip=vtkSmartPointer<vtkImageReslice>::New();
    flip->SetInputConnection(reader->GetOutputPort());
    flip->SetResliceAxesDirectionCosines(1,0,0,0,-1,0,0,0,-1);
    flip->Update();

    vtkSmartPointer<vtkImageExport>exporter=vtkSmartPointer<vtkImageExport>::New();
    exporter->SetInputData(flip->GetOutput());
    exporter->Update();

    v1=(unsigned short*)exporter->GetPointerToData();
    dispImg=new unsigned char[w*h];
//    int saturatedValue;
//    double N1_min=580,N1_max=6000;
    unsigned short *Imageirayptr=new unsigned short[w*h];


    qDebug()<<"gpuStartImageEnhancement";
    gpuStartImageEnhancement(v1,Imageirayptr,w,h);
    for(int i=0;i<w*h;++i)
    {
        dispImg[i] = Imageirayptr[i]*255/65535.0;
    }

    qDebug()<<"gpuStartImageEnhancement";


//    for(int j=0;j<w*h;j++)
//    {

//        saturatedValue = Imageirayptr[j] - N1_min;

//        if (saturatedValue > 0)
//            Imageirayptr[j] = 65535.0-(saturatedValue/(N1_max - N1_min))*20000;

//         dispImg[j] = Imageirayptr[j]*255.0/65535.0;



//        //FluoroDispBuf[imsize*imsize*saveCountImg+j]= (dispImg[j])/**(2000*255.0)/65535.0)*/;
//    }
    QImage q_image = QImage(dispImg,w,h,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);

}
