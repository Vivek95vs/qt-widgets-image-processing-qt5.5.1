#include "paint.h"
#include "ui_paint.h"

Paint::Paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paint)
{
    ui->setupUi(this);

    scene = new paintScene();
    ui->graphicsView->setScene(scene);

}

Paint::~Paint()
{
    delete ui;
}
