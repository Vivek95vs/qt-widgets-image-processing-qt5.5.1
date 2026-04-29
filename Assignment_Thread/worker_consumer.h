#ifndef WORKER_CONSUMER_H
#define WORKER_CONSUMER_H

#include <QThread>
#include <QTime>

class Worker_Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Worker_Consumer(QObject *parent = 0);


signals:

    void bufferFillCountChanged(int cCount);
    void consumerCountChanged(int count);

public slots:
    void consumer();
};

#endif // WORKER_CONSUMER_H
