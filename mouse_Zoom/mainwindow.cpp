#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QDir>
#include <QStandardItemModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
//    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
//    ui->graphicsView->setMouseTracking(true);
    bar=new QScrollBar();
    bar->setMaximum(100);
    bar->setMinimum(0);
//    ui->graphicsView->addScrollBarWidget(bar,Qt::AlignRight);
//         ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//         ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//         ui->graphicsView->horizontalScrollBar()->setMaximum(100);
//         ui->graphicsView->verticalScrollBar()->setMaximum(100);
    ui->graphicsView->horizontalScrollBar()->setDisabled(false);
    ui->graphicsView->verticalScrollBar()->setDisabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::wheelEvent(QWheelEvent *event)
{
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor=1.15;
qDebug()<<event->delta();
    if(event->delta()>0)
    {
//        ui->graphicsView->horizontalScrollBar()->setRange(0,0);
//        ui->graphicsView->verticalScrollBar()->setRange(0,0);
        ui->graphicsView->scale(scaleFactor,scaleFactor);
    }
    else
    {
//        ui->graphicsView->horizontalScrollBar()->setRange(100,100);
//        ui->graphicsView->verticalScrollBar()->setRange(100,100);
//       ui->graphicsView->verticalScrollBar()->setValue(bar->setMaximum());

            ui->graphicsView->scale(1/scaleFactor,1/scaleFactor);

    }


//     ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//     ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    view->setInteractive(true);
//    view->setDragMode(QGraphicsView::ScrollHandDrag);


//    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    static const double scaleFactor = 1.15;
//    static double currentScale = 1.0;  // stores the current scale value.
//    static const double scaleMin = .1; // defines the min scale limit.
//    if(event->delta() > 0)
//    {
//        ui->graphicsView->scale(scaleFactor, scaleFactor);
//        currentScale *= scaleFactor;
//    }
//    else if (currentScale > scaleMin)
//    {
//       ui->graphicsView->scale(1 / scaleFactor, 1 / scaleFactor);
//        currentScale /= scaleFactor;
//        ui->graphicsView->horizontalScrollBar()->blockSignals(true);



//    qreal delta = 1 + (event->delta() > 0 ? 0.1 : -0.1);
//    ui->graphicsView->scale(delta, delta);
//    event->accept();



//    QPoint pos=event->pos();
//    QPointF posf= ui->graphicsView->mapToScene(pos);

//    double by;
//    double angle = event->angleDelta().y();

//    if      (angle > 0) { by = 1 + ( angle / 360 * 0.1); }
//    else if (angle < 0) { by = 1 - (-angle / 360 * 0.1); }
//    else                { by = 1; }

//    ui->graphicsView->scale(by,by);

//    double w = ui->graphicsView->viewport()->width();
//    double h= ui->graphicsView->viewport()->height();

//    double wf=ui->graphicsView->mapToScene(QPoint(w-1,0)).x()-ui->graphicsView->mapToScene(QPoint(0,0)).x();
//    double hf=ui->graphicsView->mapToScene(QPoint(0,h-1)).y()-ui->graphicsView->mapToScene(QPoint(0,0)).y();

//    double lf=posf.x()-pos.x() * wf/w;
//    double tf=posf.y()-pos.y() * hf/h;

//    ui->graphicsView->ensureVisible(lf,tf,wf,hf,0,0);
//    QPointF newPos= ui->graphicsView->mapToScene(pos);
//    ui->graphicsView->ensureVisible(QRectF(QPointF(lf,tf)-newPos+posf,QSizeF(wf,hf)),0,0);
//    event->accept();

//    double numDegrees = -event->delta() / 8.0;
//    double numSteps = numDegrees / 15.0;
//    double factor = std::pow(1.125, numSteps);
//    ui->graphicsView->scale(factor, factor);


//    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

//    double scale_m = 1;
//    if((event->delta() > 0)&&(scale_m >= 50))//Up to 50 times the original image
//            {
//                return;
//            }
//            else if((event->delta() < 0)&&(scale_m <= 0.01))//After the image is reduced to the adaptive size, it will not continue to shrink
//            {
//                return;//Reset the picture size and position to make it adaptive to the control window size
//            }
//            else
//            {
//                // current zoom multiple;
//                qreal scaleFactor = ui->graphicsView->matrix().m11();
//                scale_m = scaleFactor;

//                int wheelDeltaValue = event->delta();
//                // Scroll up and zoom in;
//                if (wheelDeltaValue > 0)
//                {
//                    ui->graphicsView->scale(1.2, 1.2);

//                       update();
//                }
//                else
//                {// Scroll down to zoom out;
//                   ui->graphicsView->scale(1.0 / 1.2, 1.0 / 1.2);

//                       update();
//                }

//            }

//        double angle = event->angleDelta().y();
//        double factor = qPow(1.0015, angle);

//        auto targetViewportPos = event->pos();
//        auto targetScenePos = view->mapToScene(event->pos());

//        ui->graphicsView->scale(factor, factor);
//        view->centerOn(targetScenePos);
//        QPointF deltaViewportPos = targetViewportPos - QPointF(view->viewport()->width() / 2.0, view->viewport()->height() / 2.0);
//        QPointF viewportCenter = view->mapFromScene(targetScenePos) - deltaViewportPos;
    //        view->centerOn(view->mapToScene(viewportCenter.toPoint()));


//    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    if(event->delta()>0)
//    {
//        QPointF posIn=ui->graphicsView->mapToScene(event->pos());
//        double Fact1= 1.2;
//        QTransform xform=ui->graphicsView->transform();
//        xform.translate(posIn.x(),posIn.y());   // origin to spot
//        xform.scale(Fact1,Fact1);
//        xform.translate(-posIn.x(),-posIn.y()); // spot to origin
//        ui->graphicsView->setTransform(xform);
//        ui->graphicsView->update();
//        event->accept();
//    }
//    else
//    {

//        QPointF posOut=ui->graphicsView->mapToScene(event->pos());
//        double Fact2= 1/1.2;
//        QTransform yform=ui->graphicsView->transform();
//        yform.translate(posOut.x(),posOut.y());
//        yform.scale(Fact2,Fact2);
//        yform.translate(-posOut.x(),-posOut.y());
//        ui->graphicsView->setTransform(yform);
//        ui->graphicsView->update();
//        ui->graphicsView->viewport()->installEventFilter(bar);
//        event->accept();
//    }

//    if(event->delta()>0)
//    {
//        if(item->w)
//    }
}

void MainWindow::on_pushButton_clicked()
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
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
    scene->addItem(item);
}
