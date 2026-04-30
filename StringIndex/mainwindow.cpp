#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "qsqldatabase.h"
#include "qsqlquery.h"
#include "QMap"
#include "QString"
#include "time.h"
clock_t start;
clock_t end;
double cpu_time;

QList<QString> listSL;
QList<QString> listPL;
QList<QString> listDefault;
QMap<QString, QString> Map11;

int LanTrans;

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

void MainWindow::on_Index_check_clicked()
{
    QString dbName = "LanguageTranslator";
    start=clock();

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName("DRIVER={SQL Server};Server=(local);Database="+dbName+";Uid=sa;Pwd=panacea");
    if(db.open())
    {
        qDebug()<<"database opened";
        QSqlQuery* Query = new QSqlQuery();

        // Query->prepare("SELECT * FROM MachineSettingsSection2 WHERE ManufacturerModelName = '"+Machinemodule1+"' AND DeviceSerialNumber = '"+DeviceSerialNo+"' COLLATE SQL_Latin1_General_CP1_CS_AS");
        Query->prepare("SELECT * FROM DefaultLanguage ");
        Query->exec();
        while(Query->next()) { // get the first record in the result,
            listDefault.append(Query->value("IsDefault").toString());

        }

        Query->prepare("SELECT * FROM Languages ");
        Query->exec();
        while(Query->next()) { // get the first record in the result,
           listPL.append(Query->value("PrimaryLanguage").toString());

           listSL.append(Query->value("SecondaryLanguage").toString());
           //Map12.insert(Query->value("PrimaryLanguage").toString(),Query->value("SecondaryLanguage").toString());
        }

//        Query->prepare("SELECT * FROM Languages ");
//        Query->exec();
//        while(Query->next()) { // get the first record in the result,
//            listSL.append(Query->value("SecondaryLanguage").toString());

//        }


    }

    else
    {
        qDebug()<<"Secondary Language Database not opened";
    }
    db.close();

    qDebug()<<"value PL"<<listPL.length()<<listDefault<<listPL;
//    qDebug()<<"value SL"<<listSL.length()<<listDefault<<listSL;
    end=clock();

    cpu_time= double(end-start);

    qDebug()<<"cpu_time used"<<cpu_time;

    for(int i=0;i<listPL.length();i++)
    {
        Map11.insert(listPL[i],listSL[i]);

    }

    qDebug()<<"Map--1"<<Map11.value("MLC Leaf Position");

    LanTrans=listDefault[0].toInt();

    if(LanTrans==1)
    {


    }




}
