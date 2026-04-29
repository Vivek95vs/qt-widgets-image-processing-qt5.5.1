#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEventTransition>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView_2->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    //qDebug()<<"event filter called";
   // qDebug()<<"event_type"<<event->type();

    if (object == ui->graphicsView && event->type() == QEvent::MouseButtonPress)
    {
         qDebug()<<"event .............";
        QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);

        if (mEvent->button() == Qt::LeftButton)
        {
            qDebug()<<"qDebug 1: GraphicsView";

            return true;
        }
    }

    else if (object == ui->graphicsView_2 && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mEvent1 = static_cast<QMouseEvent *>(event);

        if (mEvent1->button() == Qt::LeftButton)
        {
            qDebug()<<"qDebug 2: GraphicsView_2";

            return true;
        }
    }

//    return false;


}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{

}
