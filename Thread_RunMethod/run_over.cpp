#include "run_over.h"
#include "ui_run_over.h"
#include "nonchangable.h"
#include <QDebug>

char buffer[BufferSize];

QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes;

Run_Over::Run_Over(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Run_Over)
{
    ui->setupUi(this);
    ui->progressBar1->setRange(0,DataSize);
    ui->progressBar2->setRange(0,DataSize);
    ui->progressBar3->setRange(0,BufferSize);

    pThread=new Producer_run(this);
    cThread=new Consumer_run(this);

    connect(cThread,SIGNAL(bufferFillCountChanged(int)),this,SLOT(onBufferValueChanged(int)));
    connect(pThread,SIGNAL(bufferFillCountChanged(int)),this,SLOT(onBufferValueChanged(int)));

    connect(cThread,SIGNAL(consumerCountChanged(int)),this,SLOT(onConsumerValueChanged(int)));
    connect(pThread,SIGNAL(producerCountChanged(int)),this,SLOT(onProducerValueChanged(int)));

}

Run_Over::~Run_Over()
{
    delete ui;
}

void Run_Over::onBufferValueChanged(int bCount)
{
    ui->progressBar3->setValue(bCount);
}

void Run_Over::onProducerValueChanged(int pCount)
{
    ui->progressBar1->setValue(pCount);
}

void Run_Over::onConsumerValueChanged(int cCount)
{
    ui->progressBar2->setValue(cCount);
}

void Run_Over::on_PB_Start_clicked()
{
    pThread->start();
    cThread->start();
}

void Run_Over::on_PB_Terminate_clicked()
{
    pThread->terminate();
    cThread->terminate();
}
