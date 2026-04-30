#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColor"
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
    QString hexColorCode="#008080";

    qDebug()<<"hex length"<<hexColorCode.length();

     if (hexColorCode.length() != 7) {
         qDebug() << "Invalid hexadecimal color code..";
         return;
     }

     // Convert the hexadecimal color code to QColor
     QColor color(hexColorCode);

     if (color.isValid()) {
         int red, green, blue;
         color.getRgb(&red, &green, &blue);
        qDebug() << "RGB: (" << red << ", " << green << ", " << blue << ")" ;
     } else {
         qDebug() << "Invalid hexadecimal color code." ;
     }
}
