#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QProcess"
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
    QString dcmpath= "D:\\send";

    qDebug()<<"val"<<dcmpath;
    QString program = qApp->applicationDirPath()+"\\DicomExport"+"\\DcmExport.exe";

//    QString program = "D:\\Expo_send\\Dicom_Send\\DcmExport.exe";

    QStringList arguments;

    arguments<<"1"<<dcmpath;
    //arguments.append("0");
//    arguments.append("1");
//    arguments.append(dcmpath);

    qDebug()<<"arguments--DICOM3d"<<arguments<<program;

    QProcess* myProcess = new QProcess(this);
    qDebug()<<"ttttt--DICOM3d";
    myProcess->start(program,arguments);
    myProcess->waitForStarted();

    while(myProcess->state()==myProcess->Running)
    {
        qDebug()<<"ttttt"<<myProcess->state();
        qApp->processEvents();

    }

    myProcess->waitForFinished();

}
