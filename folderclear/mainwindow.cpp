#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QDir"
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

void MainWindow::on_pushButton_clicked()
{

    QString folderPath="D:\\DICOM";
    QDir directory(folderPath);

    // Check if the folder exists
    if (!directory.exists()) {
        qDebug() << "Folder does not exist:" << folderPath;
        return;
    }

    // Retrieve a list of all files and directories in the folder
    QStringList fileList = directory.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

    // Remove all files in the folder
    foreach (const QString& fileName, fileList) {
        QString filePath = directory.filePath(fileName);
        QFile::remove(filePath);
    }
}
