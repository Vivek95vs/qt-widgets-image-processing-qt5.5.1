#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtWidgets"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<double> doses, volumes;

    volumes.append(60);
    volumes.append(30);
    volumes.append(20);
    volumes.append(50);
    volumes.append(5);
    volumes.append(18);
    volumes.append(7);
    volumes.append(30);
    volumes.append(65);
    volumes.append(75);
    volumes.append(85);
    volumes.append(10);
    volumes.append(20);
    volumes.append(55);
    volumes.append(75);


    doses.append(100);
    doses.append(120);
    doses.append(200);
    doses.append(50);
    doses.append(80);
    doses.append(180);
    doses.append(70);
    doses.append(300);
    doses.append(165);
    doses.append(175);
    doses.append(185);
    doses.append(150);
    doses.append(200);
    doses.append(255);
    doses.append(275);
    // Fill doses and volumes with your actual data

    // Create a new graph and set its data
   // ui->customplot->setWindowTitle("DVH Curve");
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setData(doses, volumes);

    // Set graph properties
    ui->customplot->xAxis->setLabel("Dose (Gy)");
    ui->customplot->yAxis->setLabel("Volume (%)");
    ui->customplot->xAxis->setRange(0, 300); // Set appropriate range
    ui->customplot->yAxis->setRange(0, 100); // Volume ranges from 0 to 100%

    // Replot the graph
    ui->customplot->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}
