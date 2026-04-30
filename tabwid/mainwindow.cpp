#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QLineEdit line;

    QString tab= "Beam";
    ph=new push();
    ui->tabWidget->addTab(ph,tr(tab.toStdString().c_str()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
