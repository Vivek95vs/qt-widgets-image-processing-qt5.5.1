#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView_2->setMouseTracking(true);
    ui->graphicsView_3->setMouseTracking(true);
    ui->graphicsView_4->setMouseTracking(true);

    ui->graphicsView->setAttribute(Qt::WA_Hover);
    ui->graphicsView_2->setAttribute(Qt::WA_Hover);
    ui->graphicsView_3->setAttribute(Qt::WA_Hover);
    ui->graphicsView_4->setAttribute(Qt::WA_Hover);

}

MainWindow::~MainWindow()
{
    delete ui;
}
