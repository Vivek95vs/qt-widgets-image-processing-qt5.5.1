#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QString folderPath="D:\\New Build\\InsightToolkit-5.4rc01\\buildnew";
//    processFiles(folderPath);
    return a.exec();
}
