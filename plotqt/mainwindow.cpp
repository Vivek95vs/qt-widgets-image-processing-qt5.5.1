#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QString>
#include <QDir>
#include <QDebug>

#include "include/qtcsv/stringdata.h"
#include "include/qtcsv/reader.h"
#include "include/qtcsv/writer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QString> strList;
    strList << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(strList);
    strData.addEmptyRow();
    strData << strList << "this is the last row";

    // write to file
    const auto filePath = QDir::currentPath() + "/test.csv";
    QtCSV::Writer::write(filePath, strData);

    // read data from file
//    const auto readData = QtCSV::Reader::readToList(filePath);
//    for (auto i = 0; i < readData.size(); ++i)
//    {
//        qDebug() << readData.at(i).join(",");
//    }

//    return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
