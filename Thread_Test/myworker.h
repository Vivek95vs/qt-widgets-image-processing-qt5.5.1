#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>
#include <QThread>
class MyWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyWorker(QObject *parent = 0);

signals:
    void NumberChanged(int);

public slots:

    void doWork();
};

#endif // MYWORKER_H
