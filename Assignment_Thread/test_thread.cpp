#include "test_thread.h"
#include "ui_test_thread.h"
#include "constants.h"

char buffer[BufferSize];

QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes;

Test_Thread::Test_Thread(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test_Thread)
{
    ui->setupUi(this);

    ui->progressBar1->setRange(0,DataSize);
    ui->progressBar2->setRange(0,DataSize);
    ui->progressBar3->setRange(0,BufferSize);

    pThread=new QThread();
    pWorker=new Worker_Producer();
    pWorker->moveToThread(pThread);

    cThread=new QThread();
    cWorker=new Worker_Consumer();
    cWorker->moveToThread(cThread);

    connect(cThread,SIGNAL(started()),cWorker,SLOT(consumer()));
    connect(cWorker,SIGNAL(bufferFillCountChanged(int)),this,SLOT(onBufferValueChanged(int)));

    connect(pThread,SIGNAL(started()),pWorker,SLOT(producer()));
    connect(pWorker,SIGNAL(bufferFillCountChanged(int)),this,SLOT(onBufferValueChanged(int)));

    connect(cWorker,SIGNAL(consumerCountChanged(int)),this,SLOT(onConsumerValueChanged(int)));
    connect(pWorker,SIGNAL(producerCountChanged(int)),this,SLOT(onProducerValueChanged(int)));

}

Test_Thread::~Test_Thread()
{
    delete ui;
}

void Test_Thread::onBufferValueChanged(int bCount)
{
    ui->progressBar3->setValue(bCount);
}

void Test_Thread::onProducerValueChanged(int pCount)
{
    ui->progressBar1->setValue(pCount);
}

void Test_Thread::onConsumerValueChanged(int cCount)
{
    ui->progressBar2->setValue(cCount);
}

void Test_Thread::on_PB_Start_clicked()
{
    pThread->start();
    cThread->start();
}

void Test_Thread::on_PB_Stop_clicked()
{
    pThread->terminate();
    cThread->terminate();
}
