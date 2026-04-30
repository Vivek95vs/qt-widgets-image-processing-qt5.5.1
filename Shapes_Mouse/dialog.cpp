#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // create our object and add it to the scene
    item = new MyItem();
    scene->addItem(item);
}

Dialog::~Dialog()
{
    delete ui;
}
