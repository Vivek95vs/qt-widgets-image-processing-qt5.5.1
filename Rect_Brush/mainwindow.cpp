#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::paintEvent(QPaintEvent *e)
{
 QPainter painter(this);

 QRect rec(50,50,200,200);
 QPen framepen(Qt::yellow);
 framepen.setWidth(10);

 QBrush brush(Qt::darkMagenta,Qt::CrossPattern);
 //painter.fillRect(rec,brush);
 painter.setPen(framepen);
 //painter.drawRect(rec);
 painter.drawEllipse(rec);
}
