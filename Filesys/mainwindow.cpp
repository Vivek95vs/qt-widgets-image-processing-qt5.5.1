#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QLabel>
#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString sPath=" :/";
    dirmodel=new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);
    ui->treeView->setModel(dirmodel);

    foldermodel=new QFileSystemModel(this);
    foldermodel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    //foldermodel->setRootPath(sPath);
    ui->listView1->setModel(foldermodel);

    filemodel=new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    //filemodel->setRootPath(sPath);
    ui->listView2->setModel(filemodel);

    ui->label1->setText("Displaying all Directory");
    ui->label2->setText("Displaying Folders");
    ui->label3->setText("Displaying Files");

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

    QString sPath=dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView1->setRootIndex(foldermodel->setRootPath(sPath));
    ui->listView2->setRootIndex(filemodel->setRootPath(sPath));

}
