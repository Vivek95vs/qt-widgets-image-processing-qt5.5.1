#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml/QDomDocument>   // Library needed for processing XML documents
#include <QFile>      // Library needed for processing files
#include <qxmlstream.h>
#include<iostream>
#include <QFileDialog>
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

void MainWindow::on_xmlread_clicked()
{
    QDomDocument xmlBOM;

    QFile file ("D:\\MLCShaper Language Trans DB\\92959-2.xml");
    if (!file.open(QFile::ReadOnly| QFile::Text)){
        qDebug()<<"File not found";
    }
    //    Set data into the QDomDocument before processing
    xmlBOM.setContent(&file);
    file.close();
    // Read the root tag
    // Extract the root markup
    QDomElement root = xmlBOM.documentElement() ;
    // Read data
    QDomElement FirstNodeTag = root.firstChildElement();

    qDebug()<<"root"<<root.tagName();
    FirstNodeTag = FirstNodeTag.nextSibling().toElement();

    //Get the first child of the component
    QDomElement Component = FirstNodeTag.firstChildElement();
    qDebug()<<"Component"<<Component.tagName();

    std::string Seq;
    std::string lastTS;
    std::string param;
    qDebug()<<"First node tag"<<FirstNodeTag.tagName()<<Component.tagName();

    //check if the child tag name is COMPONENT

    while(!Component.isNull())
    {
        Seq = Component.attribute("seq","No seg").toStdString();
        lastTS = Component.attribute("lastTS","No lastTS").toStdString();
        qDebug()<<"Step Data : "<<Seq.c_str()<<lastTS.c_str();

        QDomElement c1 = Component.firstChildElement();
        qDebug()<<"Step Type : "<<c1.text();

        QDomElement c2 = c1.nextSibling().toElement();
        qDebug()<<"Step Name : "<<c2.text();

        QDomElement c3 = c2.nextSibling().toElement();
        qDebug()<<"step param"<<c3.text()<<c3.childNodes().count();

        for(int i=0;i<c3.childNodes().count();i++)
        {

            qDebug()<<"value"<<c3.childNodes().item(i).toElement().text();
        }

//        QDomElement c4=c3.childNodes().at(0);
//        qDebug()<<"child"<<c4.tagName();

        QDomElement Child= c3.firstChildElement();



        while (!Child.isNull())
        {
            param = Child.attribute("Name","No Name").toStdString();
            qDebug()<<"Step Parameters"<<param.data();

            Child = Child.nextSibling().toElement();


//            int childe1=Child.attribute("Name","No Name").toInt();
//            qDebug()<<"child data"<<childe1;
            //            break;
        }
        Component = Component.nextSibling().toElement();
    }

}
