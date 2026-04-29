#ifndef WORKER_PRODUCER_H
#define WORKER_PRODUCER_H

#include <QThread>
#include <QTime>

class Worker_Producer : public QObject
{
    Q_OBJECT
public:
    explicit Worker_Producer(QObject *parent = 0);

signals:
    void bufferFillCountChanged(int bCount);
    void producerCountChanged(int count);

public slots:
    void producer();
};

#endif // WORKER_PRODUCER_H
