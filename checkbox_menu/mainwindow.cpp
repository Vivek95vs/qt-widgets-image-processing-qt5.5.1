#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    viewst = new QAction("&View statusbar", this);
    viewst->setCheckable(true);
    viewst->setChecked(true);

    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(viewst);

    statusBar();

    connect(viewst, &QAction::triggered, this, &MainWindow::toggleStatusbar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggleStatusbar() {

  if (viewst->isChecked()) {

      statusBar()->show();
  } else {

      statusBar()->hide();
  }
}
