#include "paint.h"
#include "ui_paint.h"
#include <QGraphicsSceneMouseEvent>

paint::paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paint)
{
    ui->setupUi(this);
    scene = new paintscene();       // Init graphics scene
    ui->graphicsView->setScene(scene);  // Set graphics scene
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);

}

paint::~paint()
{
    delete ui;
}
