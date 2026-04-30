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

void MainWindow::on_read_xml_clicked()
{
    QDomDocument xmlBOM;
    if(!tagList){
        tagList=new QList<TagElements>;
    }
    QFile file("D:\\MLCShaper Language Trans DB\\92959.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&file);
    file.close();
    // Read the root tag
    // Extract the root markup
    QDomElement root=xmlBOM.documentElement();
    // Read data
    QDomElement FirstNodeTag = root.firstChildElement();

    qDebug()<<"root"<<root.tagName();
    FirstNodeTag = FirstNodeTag.nextSibling().toElement();
    // Get the first child of the component
    QDomElement Component=FirstNodeTag.firstChildElement();
    TagElements *curTag=new TagElements;

    qDebug()<<"First node tag"<<FirstNodeTag.tagName()<<Component.tagName();
        // Check if the child tag name is COMPONENT
        if (Component.tagName()=="StepData"){
            curTag->Seq1=Component.attribute("seq","No seq").toStdString();
            curTag->lastTS=Component.attribute("lastTS","No lastTS").toStdString();
            qDebug()<<"group value"<<curTag->Seq1.c_str()<<curTag->lastTS.c_str();
        }

    QDomElement Component12=Component.firstChildElement();
    qDebug()<<"Component12"<<Component12.tagName();
    if (Component12.tagName()=="StepType"){
        qDebug()<<"group value--1"<<Component12.text();
    }

    QDomElement Component13=Component12.nextSibling().toElement();
    qDebug()<<"Component13"<<Component13.tagName();
    if (Component13.tagName()=="StepName"){
        qDebug()<<"group value--2"<<Component13.text();
    }

}

