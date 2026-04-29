#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "QString"
#include "QFileDialog"
#include "QFile"
#include "qsqlrecord.h"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlResult"
#include "QtSql/qsqlresult.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enhancer = new ImageEnhancementNew();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_Reset_clicked()
{
    cv::Mat img;
    img= cv::Mat(height,width,CV_8UC1,dispImg);
    uchar* imgOut2=new uchar [height*width];
    for(int i=0;i<height*width;i++)
    {
        imgOut2[i]=img.data[i];
    }
    QImage q_image3 = QImage(imgOut2,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image3));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
}

void MainWindow::on_Slider_Bright_valueChanged(int value)
{
    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg);

    imgbuf.convertTo(img,-1,1,value);
    uchar* imgOut3=new uchar [height*width];
    for(int i=0;i<height*width;i++)
    {
        imgOut3[i]=img.data[i];
    }
//    beta =ui->Slider_Contrast->value();
//    alpha=(value);
    QImage q_image4 = QImage(imgOut3,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image4));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    ui->Slider_Bright->setToolTip(QString::number(value));
    ui->Bright->setText(QString::number(value));
}

void MainWindow::on_Slider_Contrast_valueChanged(int value)
{
    alpha=ui->Slider_Contrast->value();
    beta=value;
    cv::Mat img;
    cv::Mat imgbuf = cv::Mat(height,width,CV_8UC1,dispImg);
    imgbuf.convertTo(img,-1,alpha/100*3.0,beta);

    uchar* imgOut4=new uchar [height*width];
    for(int i=0;i<height*width;i++)
    {
        imgOut4[i]=img.data[i];
    }
    QImage q_image5 = QImage(imgOut4,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image5));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    ui->Slider_Contrast->setToolTip(QString::number(value));
    ui->Contrast->setText(QString::number(value));
}

void MainWindow::on_Slider_WC_valueChanged(int value)
{
    double WCvalue,WWValue;
    qDebug()<<"value wc" <<value<<ui->Slider_WC->value() ;
    WCvalue = ((value*2000)/100.0f)-1000;
    qDebug()<<"WC_val" <<WCvalue;
    WWValue = ((ui->Slider_WC->value()*2000)/100.0f);
    qDebug()<<"WW_val" <<WWValue;
    cv::Mat img;
    img= cv::Mat(height,width,CV_8UC1,dispImg);

    lowerThreshold = WCvalue - WWValue / 2.0f > -1000 ? WCvalue - WWValue / 2.0f : -1000;
    upperThreshold = (WWValue/2.0f + WCvalue);
    qDebug()<<"WW_lowerThreshold" <<lowerThreshold;
    qDebug()<<"WW_upperThreshold" <<upperThreshold;

    uchar* imgOut5=new uchar [height*width];
    double imgPixelValue;
    for(int i=0;i<height*width;i++)
    {
        imgPixelValue=(((img.data[i]*2000)/255.0f)-1000);
        if(imgPixelValue <=lowerThreshold)
        {
            imgOut5[i]=0;
        }
        else if(imgPixelValue >=upperThreshold)
        {
            imgOut5[i]=255;
        }
        else
        {
            imgOut5[i]=img.data[i];
        }
    }
    QImage q_image6 = QImage(imgOut5,width,height,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image6));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
    ui->Slider_WC->setToolTip(QString::number(value));
    ui->WC->setText(QString::number(value));
}

void MainWindow::on_Slider_WW_valueChanged(int value)
{    double WCvalue,WWValue;
     qDebug()<<"value wc" <<value<<ui->Slider_WC->value() ;
     WCvalue = ((value*2000)/100.0f)-1000;;
     qDebug()<<"WC_val" <<WCvalue;
     WWValue = ((ui->Slider_WC->value()*2000)/100.0f);
     qDebug()<<"WW_val" <<WWValue;
     cv::Mat img;
     img = cv::Mat(height,width,CV_8UC1,dispImg);
     lowerThreshold = WCvalue - WWValue / 2.0f > -1000 ? WCvalue - WWValue / 2.0f : -1000;
     upperThreshold = (WWValue/2.0f + WCvalue);
     qDebug()<<"WW_lowerThreshold" <<lowerThreshold;
     qDebug()<<"WW_upperThreshold" <<upperThreshold;



     uchar* imgOut6=new uchar [height*width];
     double imgPixelValue;
     for(int i=0;i<height*width;i++)
     {
         imgPixelValue=(((img.data[i]*2000)/255.0f)-1000);
         if(imgPixelValue <=lowerThreshold)
         {
             imgOut6[i]=0;
         }
         else if(imgPixelValue >=upperThreshold)
         {
             imgOut6[i]=255;
         }
         else
         {
             imgOut6[i]=img.data[i];
         }
     }
     QImage q_image7 = QImage(imgOut6,width,height,QImage::Format_Grayscale8);
     item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image7));
     scene= new QGraphicsScene(this);
     scene->addItem(item);
 //    view = new QGraphicsView(scene);
     ui->graphicsView->setScene(scene);
     ui->graphicsView->fitInView(item);
     ui->Slider_WW->setToolTip(QString::number(value));
     ui->WW->setText(QString::number(value));
}

void MainWindow::on_Load_Raw_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Test Image","D:/couchtop/*.raw",QDir::currentPath());
    if (filename.isEmpty())
       {
           qDebug()<<"Could not open file";
       }
    FILE * Img;
    Img= fopen(filename.toStdString().c_str(),"rb");


    width=3072;
    height=3072;

     qDebug()<<"Image----";


//    width = ImgWidth;
//    height = ImgHeight;

    dispImg= new unsigned char[width*height];
    radbuf = new unsigned short[3072*3072];

    fread(radbuf,sizeof(unsigned short),3072*3072,Img);

    qDebug()<<"Image----";


    img = new unsigned short[3072*3072];
    enhancer->StartImageEnhancement(radbuf,img,width,height);

    for(int i=0;i<width*height;++i)
    {
        dispImg[i] = img/*image->GetBufferPointer()*/[i]*255.0/65535.0;
    }
    qDebug()<<"Image----"<<img[100];

    myImage = QImage(dispImg,3072,3072,QImage::Format_Grayscale8);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(myImage));
    scene= new QGraphicsScene(this);
    scene->addItem(item);
//    view = new QGraphicsView(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(item);
}


void MainWindow::on_sqlData_clicked()
{
    int checkdatasent=1;
    QString commonSeriesUID= "123.efbjbjfj";
    QString readUID= "42555.gfngngn";
    QString checklist= "56869.vgffgfgn";
    QString tabcount="464";
    int fGroup=1;
    QString FractionNumber="1";
    int BeamNumber=0;
    QString BeamName="AP-LLAT";

    QString dbName = "CCB_Treatment_4_0_0";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName("DRIVER={SQL Server};Server=(local);Database="+dbName+";Uid=sa;Pwd=panacea");

    if(db.open())
    {

//        if(checkdatasent==1)
//        {
//            QSqlQuery* Query = new QSqlQuery();
//            Query->prepare("UPDATE OfflineRnVs SET IntrafractionRADReferenceSeriesInstanceUID = IntrafractionRADReferenceSeriesInstanceUID + ',' + '"+commonSeriesUID+"' WHERE  WorkRefId='"+tabcount+"'and FractionGroup='"+QString::number(fGroup)+"' and FractionNo='"+FractionNumber+"' and BeamNumber ='"+QString::number(BeamNumber)+"' and BeamName ='"+BeamName+"'" );
//            Query->exec();
//            Query->prepare("UPDATE OfflineRnVs SET IntrafractionDRRReferenceSeriesInstanceUID = '"+readUID+"' WHERE  WorkRefId='"+tabcount+"'and FractionGroup='"+QString::number(fGroup)+"' and FractionNo='"+FractionNumber+"' and BeamNumber ='"+QString::number(BeamNumber)+"' and BeamName ='"+BeamName+"'" );
//            Query->exec();

//        }

         QSqlQuery query;
         QString selectQuery = QString("SELECT IntrafractionRADReferenceSeriesInstanceUID FROM OfflineRnVs WHERE WorkRefId='%1' AND FractionGroup='%2' AND FractionNo='%3' AND BeamNumber='%4' AND BeamName LIKE '%5%'")
                    .arg(tabcount)
                    .arg(fGroup)
                    .arg(FractionNumber)
                    .arg(BeamNumber)
                    .arg(BeamName);

                if (query.exec(selectQuery)) {
                    if (query.next()) {
                        QString existingValue = query.value(0).toString();
                        QString newValue;

                        if (!existingValue.isEmpty()) {
                            // Append with a comma
                            newValue = existingValue + "," + commonSeriesUID;
                        } else {
                            // Write value directly
                            newValue = commonSeriesUID;
                        }

                        QString updateQuery = QString("UPDATE OfflineRnVs SET IntrafractionRADReferenceSeriesInstanceUID = '%1' WHERE WorkRefId='%2' AND FractionGroup='%3' AND FractionNo='%4' AND BeamNumber='%5' AND BeamName LIKE '%6%'")
                            .arg(newValue)
                            .arg(tabcount)
                            .arg(fGroup)
                            .arg(FractionNumber)
                            .arg(BeamNumber)
                            .arg(BeamName);

                        if (!query.exec(updateQuery)) {
                            qDebug() << "Failed to update data:";
                        }
                    } else {
                        qDebug() << "No matching data found to update.";
                    }
                } else {
                    qDebug() << "Failed to execute select query:";
                }

    }
    db.close();
}

void MainWindow::on_sqldata1_clicked()
{
//    int checkdatasent=1;
    QString commonSeriesUID= "123.efbjbjfj";
    QString readUID= "42555.gfngngn";
    QString checklist= "56869.vgffgfgn";
    QString tabcount="464";
    int fGroup=1;
    QString FractionNumber="1";
    int BeamNumber=0;
    QString BeamName="Stereo";

    QString dbName = "CCB_Treatment_4_0_0";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName("DRIVER={SQL Server};Server=(local);Database="+dbName+";Uid=sa;Pwd=panacea");

    if(db.open())
    {
        QSqlQuery* Query = new QSqlQuery();
        Query->prepare(
            "UPDATE OfflineRnVs "
            "SET RADReferenceSeriesInstanceUID = :commonSeriesUID "
            "WHERE WorkRefId = :workRefId AND FractionGroup = :fractionGroup "
            "AND FractionNo = :fractionNo AND BeamNumber = :beamNumber AND BeamName LIKE :beamName");

        Query->bindValue(":commonSeriesUID", commonSeriesUID);
        Query->bindValue(":workRefId", tabcount);
        Query->bindValue(":fractionGroup", QString::number(fGroup));
        Query->bindValue(":fractionNo", FractionNumber);
        Query->bindValue(":beamNumber", QString::number(BeamNumber));
        Query->bindValue(":beamName", BeamName + "%");  // Add wildcard to match any suffix after BeamName

        if (!Query->exec()) {
            qDebug() << "Failed to execute update query:";
        }

    }

    db.close();
}

void MainWindow::on_writedatabase_clicked()
{
        QString dbName = "OnlineR&V";
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
        db.setDatabaseName("DRIVER={SQL Server};Server=(local);Database="+dbName+";Uid=sa;Pwd=panacea");

        if (!db.open()) {
            qDebug() << "Failed to open database:" ;
            return;
        }
        QSqlQuery query;
        // Query to read the entire database table
//        QSqlQuery query("SELECT * FROM CBCT_MachineParameters", db);
        if (!query.exec("SELECT * FROM CBCT_MachineParameters")) {
            qDebug() << "Failed to execute query:";
            db.close();
            return;
        }

        // Open a text file for writing
        QFile file("database_output.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for writing.";
            db.close();
            return;
        }

        QTextStream out(&file);

        // Write the column names (headers) to the file
        QStringList columnNames;
        for (int i = 0; i < query.record().count(); ++i) {
            columnNames << query.record().fieldName(i);
        }
        out << columnNames.join(", ") << "\n";

        // Write each row of the table to the file
        while (query.next()) {
            QStringList rowValues;
            for (int i = 0; i < query.record().count(); ++i) {
                rowValues << query.value(i).toString();  // Convert each field to string
            }
            out << rowValues.join(", ") << "\n";
        }

        // Close the file and database
        file.close();
        db.close();

        qDebug() << "Database content written to database_output.txt";
}
