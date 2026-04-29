#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QLabel>
#include <QFileSystemModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label1->setText("Displaying all Directory");
    ui->label2->setText("Displaying Folders");
    ui->label3->setText("Displaying Files");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString sPath=QDir::currentPath();
    dirmodel=new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);
    ui->treeView->setModel(dirmodel);

}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

    foldermodel=new QFileSystemModel(this);
    foldermodel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    ui->listView1->setModel(foldermodel);

    QString sPath=dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView1->setRootIndex(foldermodel->setRootPath(sPath));

}


void MainWindow::on_actionText_triggered()
{
    QFile mFile=QFileDialog::getOpenFileName(this,tr("Open TextFile"), ".",tr("Text files (*.txt)"));
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Could not open for Reading";
    }
    QTextStream in(&mFile);
    QString mText= in.readAll();
    ui->textEdit->setText(mText);
    mFile.close();
}
