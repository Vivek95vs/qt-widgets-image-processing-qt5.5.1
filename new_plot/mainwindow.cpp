#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    customplot=new QCustomPlot(this);
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

    customplot->addGraph();
    customplot->graph(0)->setData(x,y);
    customplot->xAxis->setLabel("x");
    customplot->yAxis->setLabel("y");
    customplot->xAxis->setRange(-1,1);
    customplot->yAxis->setRange(0,1);
    customplot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
