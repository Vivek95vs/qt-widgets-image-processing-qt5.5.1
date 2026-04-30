#ifndef PRODUCER_RUN_H
#define PRODUCER_RUN_H

#include <QThread>
#include <QTime>

class Producer_run : public QThread
{
    Q_OBJECT
public:
    explicit Producer_run(QObject *parent=0);
    void run();

signals:
    void bufferFillCountChanged(int bCount);
    void producerCountChanged(int count);

public slots:
};

#endif // PRODUCER_RUN_H
