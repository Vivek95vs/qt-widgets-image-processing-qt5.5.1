#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Thread=new QThread(this);
    worker=new MainWindow();
    worker->moveToThread(Thread);

    connect(Thread,SIGNAL(started()),this,SLOT(doWork()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doWork()
{
    for(int i=0;i<100;i++)
    {
//        ui->label->setText(QString::number(i));
    }
}

void MainWindow::on_PB_Start_clicked()
{
    Thread->start();
}

void MainWindow::on_PB_Stop_clicked()
{
    Thread->terminate();
}
