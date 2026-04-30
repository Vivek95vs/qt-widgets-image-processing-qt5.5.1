#include "myworker.h"

MyWorker::MyWorker(QObject *parent) : QObject(parent)
{

}

void MyWorker::doWork()
{
    for(int i=0;i<10000;i++)
    {
        emit NumberChanged(i);
    }
}

