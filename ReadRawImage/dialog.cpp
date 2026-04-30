 #include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    mouseOperations = new MouseOperations();
    ui->graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_displayImage_clicked()
{
    mouseOperations->setMode(MouseOperations::itemsEnum::otherOperations);
    QString imageFile = "D:/Ashutosh/QT Projects/ReadRawImage/Test.raw";
    unsigned short *storeImg = new unsigned short[3072*3072];
    unsigned char *charImg = new unsigned char[3072*3072];
    FILE *file = fopen(imageFile.toStdString().c_str(),"rb+");//Open the file with read mode ("rb+")
    fread(storeImg, 1, 3072*3072*sizeof(unsigned short), file);
    fclose(file);
    for (int i=0;i<3072*3072;i++){
        charImg[i] = (storeImg[i]*255.0)/65535.0;
    }
    QImage qImage = QImage(charImg,3072,3072, QImage::Format_Grayscale8);
    QGraphicsPixmapItem *image = new QGraphicsPixmapItem(QPixmap::fromImage(qImage));
   // scene = new QGraphicsScene();
    mouseOperations->addItem(image);
    ui->graphicsView->setScene(mouseOperations);
    ui->graphicsView->fitInView(10,10,3072,3072);

}

void Dialog::on_deleteLines_clicked()
{
//    Delete all the Graphics items on the screen on button click
     mouseOperations->setMode(MouseOperations::itemsEnum::otherOperations);
     mouseOperations->deleteAllGraphicsItems();

}

void Dialog::on_lineSelection_clicked()
{    
    mouseOperations->setMode(MouseOperations::itemsEnum::otherOperations);
    mouseOperations->selectLine();
}

void Dialog::on_drawLine_clicked()
{
    qDebug()<<"Dialog.cpp drawLine()...";
    QCursor val= QCursor(Qt::CrossCursor);
    setCursor(val);
    mouseOperations->setMode(MouseOperations::itemsEnum::drawLine);
}

void Dialog::on_drawRectangle_clicked()
{
    qDebug()<<"Dialog.cpp drawRectangle()...";
    mouseOperations->setMode(MouseOperations::itemsEnum::drawRectangle);
}

void Dialog::on_drawEllipse_clicked()
{
    qDebug()<<"Dialog.cpp drawEllips()...";
    mouseOperations->setMode(MouseOperations::itemsEnum::drawEllipse);
}

void Dialog::on_drawPolygon_clicked()
{
    qDebug()<<"Dialog.cpp drawPolygon()...";
    mouseOperations->setMode(MouseOperations::itemsEnum::drawPolygon);
}

void Dialog::on_brushButton_clicked()
{
    qDebug()<<"Dialog.cpp Brush()...";

    QCursor val= QCursor(Qt::ForbiddenCursor);
    setCursor(val);
    mouseOperations->setMode(MouseOperations::itemsEnum::brushTools);
}
