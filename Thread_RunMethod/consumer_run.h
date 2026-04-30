#ifndef CONSUMER_RUN_H
#define CONSUMER_RUN_H

#include <QThread>
#include <QTime>

class Consumer_run : public QThread
{
    Q_OBJECT
public:
    explicit Consumer_run(QObject *parent=0);
    void run();

signals:
    void bufferFillCountChanged(int cCount);
    void consumerCountChanged(int count);

public slots:

};

#endif // CONSUMER_RUN_H
