#include "dialog.h"
#include "ui_dialog.h"
#include <QThread>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Thread=new QThread();
//    Thread->msleep(100);
    worker=new MyWorker();
    worker->moveToThread(Thread);

    connect(Thread,SIGNAL(started()),worker,SLOT(doWork()));
    connect(worker,SIGNAL(NumberChanged(int)),this,SLOT(onNumberChanged(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onNumberChanged(int Number)
{

    ui->label->setText(QString::number(Number));
}

void Dialog::on_PB_START_clicked()
{
    Thread->start();
}

void Dialog::on_PB_STOP_clicked()
{
    Thread->terminate();
}
