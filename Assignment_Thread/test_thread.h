#ifndef TEST_THREAD_H
#define TEST_THREAD_H

#include <QDialog>
#include "worker_consumer.h"
#include "worker_producer.h"

#include <QSemaphore>
#include <QThread>
#include <QTime>

namespace Ui {
class Test_Thread;
}

class Test_Thread : public QDialog
{
    Q_OBJECT

public:
    explicit Test_Thread(QWidget *parent = 0);
    ~Test_Thread();

    QThread *pThread;
    Worker_Producer *pWorker;

    QThread *cThread;
    Worker_Consumer *cWorker;


public slots:
    void onBufferValueChanged(int);
    void onProducerValueChanged(int);
    void onConsumerValueChanged(int);

private slots:
    void on_PB_Start_clicked();

    void on_PB_Stop_clicked();

private:
    Ui::Test_Thread *ui;

};

#endif // TEST_THREAD_H
