#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QDebug"

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

void MainWindow::on_string_split_clicked()
{
    QString a1= "2021-12-15 10:00:00.0000000";

//    QStringList a4;

//    a4.append(a1);

//    QString a5= a4.join(" ");

    QStringList a6= a1.split(" ");
    QString a7 = a6[0];
    QString a8 = a6[1];

    qDebug()<<"val"<<a7<<a8;
}
