#include "dialog.h"
#include "ui_dialog.h"
#include "mysquare.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setMouseTracking(true);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::black);
    square = new mySquare;
    scene->addItem(square);
    square->mPix = QPixmap(400,400);
    square->mPix.fill(Qt::white);
    //scene->addPixmap(mPix);
    scene->addPixmap(square->mPix);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
   square->selectedTool = 1;
}
