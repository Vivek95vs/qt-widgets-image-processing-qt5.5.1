#ifndef WORKER_H
#define WORKER_H
#include <QObject>

class Worker: public QObject
{
    Q_OBJECT
public:
    Worker();


public slots:
    void tagprocess();

signals:
    void sendtagprocess();
};

#endif // WORKER_H
