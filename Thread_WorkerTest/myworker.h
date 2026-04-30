#ifndef MYWORKER_H
#define MYWORKER_H
#include <QObject>
#include <QThread>

class MyWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyWorker(QObject *parent = 0);
    QThread *Thread;
    MyWorker *worker;

signals:

public slots:
};

#endif // MYWORKER_H
