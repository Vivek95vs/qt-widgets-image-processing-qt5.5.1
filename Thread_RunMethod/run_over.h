#ifndef RUN_OVER_H
#define RUN_OVER_H

#include <QDialog>
#include "producer_run.h"
#include "consumer_run.h"
#include <QSemaphore>
#include <QThread>

namespace Ui {
class Run_Over;
}

class Run_Over : public QDialog
{
    Q_OBJECT

public:
    explicit Run_Over(QWidget *parent = 0);
    ~Run_Over();

public slots:
    void onBufferValueChanged(int);
    void onProducerValueChanged(int);
    void onConsumerValueChanged(int);

private slots:
    void on_PB_Start_clicked();

    void on_PB_Terminate_clicked();

private:
    Ui::Run_Over *ui;
    Producer_run *pThread;
    Consumer_run *cThread;
};

#endif // RUN_OVER_H
