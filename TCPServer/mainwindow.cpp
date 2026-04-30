#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   clsock=new QTcpSocket();
   connect(clsock,SIGNAL(connected()),this,SLOT(isConnected()));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clientclick_clicked()
{
    qDebug()<<"click";
    clsock->connectToHost("192.168.10.101",5555);
    if(clsock->waitForConnected(1000))
    {
        qDebug()<<"Connected to Server";
    }
}
void MainWindow::isConnected()
{
     qDebug()<<"connection esta";
}
