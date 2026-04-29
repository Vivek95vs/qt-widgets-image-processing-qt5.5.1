#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QDir"

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

void MainWindow::on_DcmOutput_clicked()
{
        QString Referencepath= "D:\\CapturedImages\\20220506\\RT202204A00\\S8_P1\\FG1_FN2\\Beam2\\ReferenceImages";
        QDir dir(Referencepath);
        QStringList filters;
        QStringList dcmList;
        filters << "*.dcm" ;
        dir.setNameFilters(filters);
        dcmList = dir.entryList(filters);

        qDebug()<<"length"<<Referencepath<<dcmList.length();

}
